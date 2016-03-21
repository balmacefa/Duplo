#include "Accion.h"

//constructor
Accion::Accion(){

}

//Metos de leectura del menu
boolean Accion::menuAjusteEngrape(){
  int value = digitalRead(PIN_MENU_AJUSTES_ENGRAPE);
  return false;
}

boolean Accion::menuEngrapar(){
  return digitalRead(PIN_MENU_ENGRAPAR);
}

boolean Accion::menuAvanceDobladora(){
  return digitalRead(PIN_MENU_AVANCE_DOBLADORA);

}
boolean Accion::menuDoblar(){
  return digitalRead(PIN_MENU_DOBLAR);
}

//TORRE
boolean Accion::entradaPapel(){
  //leer pin de entrada papel
  return digitalRead(PIN_TORRE_ENVIO_PAPEL);
}
boolean Accion::inicioTorre(){
  return digitalRead(PIN_TORRE_INICIA);
}

//Engrapadora
int Accion::contarMitadVueltasAjustePapel(){
  return -1;
}
void Accion::ajustePapel(boolean estado){
  digitalWrite( PIN_POS_AJUSTE_HORIZONTAL_ENGRAPADORA , estado);
  digitalWrite( PIN_POS_AJUSTE_VERTICAL_ENGRAPADORA , estado);
}
void Accion::engrapar(boolean estado){
 digitalWrite( PIN_ENGRAPAR, estado );
}


//Dobladora
void Accion::topeGrapa(boolean estado){
  digitalWrite( PIN_TOPE_ENGRAPAR, estado );
}

void Accion::salidaCorrienteDobladora(boolean estado){
  digitalWrite( PIN_SALIDA_CORRIENTE_DOBLADORA, estado );
}
void Accion::doblar(boolean estado){
  digitalWrite( PIN_DOBLADORA, estado );
}

