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

void Proceso::topeGrapa(boolean estado){
  digitalWrite( PIN_TOPE_ENGRAPAR, estado );
}

void Proceso::salidaCorrienteDobladora(boolean estado){
  digitalWrite( PIN_SALIDA_CORRIENTE_DOBLADORA, estado );
}
void Proceso::doblar(boolean estado){
  digitalWrite( PIN_SALIDA_CORRIENTE_DOBLADORA, estado );
}
void Proceso::ajustePapel(boolean estado){
  digitalWrite( PIN_POS_AJUSTE_HORIZONTAL_ENGRAPADORA , estado);
  digitalWrite( PIN_POS_AJUSTE_VERTICAL_ENGRAPADORA , estado);
}

boolean esSalidaCorrienteDobladora = false;

boolean esTope = false;
boolean ajustePapel = false;

int cantidadMitadVuelta = 0;

void Proceso::calcular(){
  if(!_modoTest){
    unsigned long tiempoActual = millis();
    
    //Entrada del tope de papel
    if( !esTope && tiempoActual >= ( _tiempoInicio + TIM_ENTRADA_TOPE_ENGRAPAR ) ){
      topeGrapa(true);
      esTope = true;
    }
    //Desactivar senal del tope de papel
    if( esTope && tiempoActual >= ( _tiempoInicio + TIM_ENTRADA_TOPE_ENGRAPAR + TIM_SIG_TOPE_ENGRAPAR ) ){
      topeGrapa(false);
    }
    
    //activar los ajuste de papel
    if( !ajustePapel && tiempoActual >= ( _tiempoInicio + TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL ) ){
      ajustePapel(true);
      ajustePapel = true;
    }
    //Contar cantidad de mitad de vueltas de los motores
    if( ajustePapel ){
      contarMidadVueltas();
    }
    //desactivas los ajustes verticales despues de 4 mitad de vueltas
    if(cantidadMitadVuelta >= MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL){
      ajustePapel(false);
      cantidadMitadVuelta = 0;
    }
    
    //abrir los ajuste verticales
    //activar los ajuste de papel
    if( !ajustePapel && tiempoActual >= ( _tiempoInicio + TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL ) ){
      ajustePapel(true);
      ajustePapel = true;
    }
    //Contar cantidad de mitad de vueltas de los motores
    if( ajustePapel ){
      contarMidadVueltas();
    }
    //desactivas los ajustes verticales despues de 4 mitad de vueltas
    if(cantidadMitadVuelta >= MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL){
      ajustePapel(false);
      cantidadMitadVuelta = 0;
    }
    
    
    //si ya se termino el proceso
    if(tiempoActual >= ( _tiempoInicio + TIM_ENTRADA_SALIDA_CORRIENTE_DOBLADORA + TIM_SIG_DOBLADORA ) ){
      //Ya hemos terminado
      //Desactivar la salida de corriente
      salidaCorrienteDobladora(false);
      _terminado = true;
      return;
    }
    //activar salida final del papel
    if( !esSalidaCorrienteDobladora && tiempoActual >= ( _tiempoInicio + TIM_ENTRADA_SALIDA_CORRIENTE_DOBLADORA ) ){
      esSalidaCorrienteDobladora = true;
      salidaCorrienteDobladora(true);
      return;
    }
    
    //desactivar dobladora
    if(tiempoActual >= ( _tiempoInicio + TIM_ENTRADA_DOBLADORA + TIM_SIG_DOBLADORA ) ){
      doblar(false);
      return;
    }
    
    //activar la dobladora
    if(tiempoActual >= ( _tiempoInicio + TIM_ENTRADA_DOBLADORA ) ){
      doblar(true);
      return;
    }
       
  }
}
