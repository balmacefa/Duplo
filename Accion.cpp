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
void Accion::bandaEngrapadora(boolean estado){
 digitalWrite( PIN_BANDA_ENGRAPDORA, estado );
}
int Accion::contarMitadVueltasAjustePapel(){
  //Leer los sensores
  //PIN_POS_AJUSTE_HORIZONTAL_ENGRAPADORA
  //PIN_POS_AJUSTE_VERTICAL_ENGRAPADORA
  return -1;
}
void Accion::ajustePapel(boolean estado){
  digitalWrite( PIN_AJUSTE_HORIZONTAL_ENGRAPADORA , estado);
  digitalWrite( PIN_AJUSTE_VERTICAL_ENGRADORA , estado);
}
void Accion::engrapar(boolean estado){
 digitalWrite( PIN_ENGRAPAR, estado );
}
void Accion::avancePapelEngrapadora(boolean estado){
  digitalWrite( PIN_AVANCE_PAPEL_ENGRAPDORA, estado );
}

//Dobladora
void Accion::bandaDobladora(boolean estado){
 digitalWrite( PIN_BANDA_DOBLADORA, estado );
}
void Accion::topeGrapa(boolean estado){
  digitalWrite( PIN_TOPE_ENGRAPAR, estado );
}
void Accion::doblar(boolean estado){
  digitalWrite( PIN_DOBLADORA, estado );
}
void Accion::salidaCorrienteDobladora(boolean estado){
  digitalWrite( PIN_SALIDA_CORRIENTE_DOBLADORA, estado );
}

void Accion::bandas(boolean estado){
  bandaDobladora(estado);
  bandaEngrapadora(estado);
}

