#include "Proceso.h"

Proceso::Proceso(Accion* accion, unsigned long timeInit){
  _accion = accion;
  _tiempoInicio = timeInit;
  _terminado = false;
}
Proceso::Proceso(Accion* accion){
  _accion = accion;
  _terminado = false;
}

void Proceso::setTiempoInicial( unsigned long timeInit){
  _tiempoInicio = timeInit;
}
void Proceso::reiniciarVariables(){
  esSalidaCorrienteDobladora = false;
  esTope = false;
  esAjustePapel = false;
  esAjustePapelAbrir = false;
  esEngrapar = false;
  esAvancePapelEngrapadora = false;
  esDoblar = false;
  cantidadMitadVuelta = 0;
  sigLecturaAjustePapel = 0UL;
}

#define TEST_AJUSTE 0
#define TEST_ENGRAPAR 1
#define TEST_AVANCE_DOBLAR 2
#define TEST_DOBLAR 3
void Proceso::hacerAjusteEngrape(){
  _test = TEST_AJUSTE;
}

void Proceso::hacerEngrapar(){
  _test = TEST_ENGRAPAR;
}

void Proceso::hacerAvanceDobladora(){
  _test = TEST_AVANCE_DOBLAR;
}

void Proceso::hacerDoblar(){
  _test = TEST_DOBLAR;
}

void Proceso::calcularPrueba(){
  unsigned long tiempoActual = millis();
  switch (_test){
    case TEST_AJUSTE:
      //levantar Tope
      if( !esTope ){
        accion.topeGrapa(true);
        esTope = true;
      }
      //mover los motores
      //activar los ajuste de papel
      if( !esAjustePapel ){
        _accion->ajustePapel(true);
        esAjustePapel = true;
        sigLecturaAjustePapel = tiempoActual + FRECUENCIA_LECTURA_AJUSTE_PAPEL;
      }
      
      //Contar cantidad de mitad de vueltas de los motores
      if( esAjustePapel || esAjustePapelAbrir ){
        //frecuencia para preguntar
        if(tiempoActual >= sigLecturaAjustePapel && _accion->mitadVueltasAjustePapel() ){
          //aumentar cantidad de vueltas
          cantidadMitadVuelta++;
          //Ajustar el nuevo tiempo para preguntar
          sigLecturaAjustePapel = tiempoActual + FRECUENCIA_LECTURA_AJUSTE_PAPEL;
        }
      }
      
    break;
    
    case TEST_ENGRAPAR:
    break;
    
    case TEST_AVANCE_DOBLAR:
    break;
    
    case TEST_DOBLAR:
    break;
  }
}

boolean Proceso::esTerminado(){
  return _terminado;
}

void Proceso::calcular( ){
  unsigned long tiempoActual = millis();
  
  //Calcular el offset del tiempo
  tiempoActual = tiempoActual - _tiempoInicio;
  
  //Entrada del tope de papel
  if( !esTope && tiempoActual >= TIM_ENTRADA_TOPE_ENGRAPAR ){
    _accion->topeGrapa(true);
    esTope = true;
  }
  //Desactivar senal del tope de papel
  if( esTope && tiempoActual >= ( TIM_ENTRADA_TOPE_ENGRAPAR + TIM_SIG_TOPE_ENGRAPAR ) ){
    _accion->topeGrapa(false);
  }
  
  //activar los ajuste de papel
  if( (!esAjustePapel && tiempoActual >= ( TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL ))
  |( !esAjustePapelAbrir && tiempoActual >= ( TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL_DEJAR_PASAR ) )){
    _accion->ajustePapel(true);
    esAjustePapel = true;
    sigLecturaAjustePapel = tiempoActual + FRECUENCIA_LECTURA_AJUSTE_PAPEL;
  }
  
  //Contar cantidad de mitad de vueltas de los motores
  if( esAjustePapel || esAjustePapelAbrir ){
    //frecuencia para preguntar
    if(tiempoActual >= sigLecturaAjustePapel && _accion->mitadVueltasAjustePapel() ){
      //aumentar cantidad de vueltas
      cantidadMitadVuelta++;
      //Ajustar el nuevo tiempo para preguntar
      sigLecturaAjustePapel = tiempoActual + FRECUENCIA_LECTURA_AJUSTE_PAPEL;
    }
  }
  
  //desactivas los ajustes verticales despues de 4 mitad de vueltas
  if( (esAjustePapel && cantidadMitadVuelta >= MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL)
  | (esAjustePapelAbrir && cantidadMitadVuelta == MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL_DEJAR_PASAR) ){
    _accion->ajustePapel(false);
    cantidadMitadVuelta = 0;
  }
  
  //Engrapar
  //Entrada de la engrapadora
  if( !esEngrapar && tiempoActual >= TIM_ENTRADA_ENGRAPAR ){
    _accion->engrapar(true);
    esEngrapar = true;
  }
  //Desactivar senal de engrapadora
  if( esEngrapar && tiempoActual >= ( TIM_ENTRADA_ENGRAPAR + TIM_SIG_ENGRAPAR ) ){
    _accion->engrapar(false);
  }
  
  //avance del papel
  if( !esAvancePapelEngrapadora && tiempoActual >= TIM_ENTRADA_AVANCE_PAPEL_ENGRAPADORA ){
    _accion->avancePapelEngrapadora(true);
    esAvancePapelEngrapadora = true;
  }
  //Desactivar senal de avance papel
  if( esAvancePapelEngrapadora && tiempoActual >= ( TIM_ENTRADA_AVANCE_PAPEL_ENGRAPADORA + TIM_SIG_AVANCE_PAPEL_ENGRAPADORA ) ){
    _accion->avancePapelEngrapadora(false);
  }
  
  //activar la dobladora
  if( !esDoblar && tiempoActual >= ( TIM_ENTRADA_DOBLADORA ) ){
    _accion->doblar(true);
    esDoblar = true;
  }
  
  //desactivar dobladora
  if(esDoblar && tiempoActual >= ( _tiempoInicio + TIM_ENTRADA_DOBLADORA + TIM_SIG_DOBLADORA ) ){
    _accion->doblar(false);
  }
     
  //activar salida final del papel
  if( !esSalidaCorrienteDobladora && tiempoActual >= ( TIM_ENTRADA_SALIDA_CORRIENTE_DOBLADORA ) ){
    esSalidaCorrienteDobladora = true;
    _accion->salidaCorrienteDobladora(true);
  }
  
  //si ya se termino el proceso
  if(tiempoActual >= ( TIM_ENTRADA_SALIDA_CORRIENTE_DOBLADORA + TIM_SIG_DOBLADORA ) ){
    //Ya hemos terminado
    //Desactivar la salida de corriente
    _accion->salidaCorrienteDobladora(false);
    _terminado = true;
  }
}
