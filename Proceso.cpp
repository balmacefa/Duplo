#include "Proceso.h"

Proceso::Proceso(Accion* accion, unsigned long timeInit){
  _accion = accion;
  _modoTest = false;
  //_estado = INICIO;
  _tiempoInicio = timeInit;
  _terminado = false;
}
Proceso::Proceso(Accion* accion){
  _accion = accion;
  _modoTest = false;
  //_estado = INICIO;
  _terminado = false;
}

void Proceso::hacerAjusteEngrape(){

}

void Proceso::hacerEngrapar(){

}

void Proceso::hacerAvanceDobladora(){

}

void Proceso::hacerDoblar(){

}

boolean Proceso::esTerminado(){
  return _terminado;
}

void Proceso::setModoTest(boolean habilitar){
  _modoTest = habilitar;
}


boolean esSalidaCorrienteDobladora = false;

boolean esTope = false;
boolean esAjustePapel = false;
boolean esAjustePapelAbrir = false;
boolean esEngrapar = false;
boolean esAvancePapelEngrapadora = false;
boolean esDoblar = false;
int cantidadMitadVuelta = 0;

void Proceso::calcular( ){
  if(!_modoTest){
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
    if( !esAjustePapel && tiempoActual >= ( TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL ) ){
      _accion->ajustePapel(true);
      esAjustePapel = true;
    }
    //Contar cantidad de mitad de vueltas de los motores
    if( esAjustePapel ){
      _accion->contarMitadVueltasAjustePapel();
    }
    //desactivas los ajustes verticales despues de 4 mitad de vueltas
    if(cantidadMitadVuelta >= MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL){
      _accion->ajustePapel(false);
      cantidadMitadVuelta = 0;
    }
    
    //abrir los ajuste verticales para que pueda entrar nuevo papel, Dar solamente una media vuelta
    //activar los ajuste de papel
    if( !esAjustePapelAbrir && tiempoActual >= ( TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL_DEJAR_PASAR ) ){
      _accion->ajustePapel(true);
      esAjustePapelAbrir = true;
    }
    //Contar cantidad de mitad de vueltas de los motores
    if( esAjustePapelAbrir ){
      _accion->contarMitadVueltasAjustePapel();
    }
    //desactivas los ajustes verticales despues de 1 mitad de vueltas
    if(cantidadMitadVuelta == MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL_DEJAR_PASAR){
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
}
