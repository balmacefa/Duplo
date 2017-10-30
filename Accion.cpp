#include "Accion.h"

//constructor
Accion::Accion() {
//configurar pines

pinMode(PIN_BANDA_ENGRAPDORA, OUTPUT);
pinMode(PIN_AJUSTE_HORIZONTAL_VERTICAL_ENGRAPADORA, OUTPUT);
pinMode(PIN_AVANCE_PAPEL_ENGRAPDORA, OUTPUT);
pinMode(PIN_ENGRAPAR, OUTPUT);
pinMode(PIN_TOPE_ENGRAPAR, OUTPUT);
pinMode(PIN_BANDA_DOBLADORA, OUTPUT);
pinMode(PIN_DOBLADORA, OUTPUT);
pinMode(PIN_SALIDA_CORRIENTE_DOBLADORA, OUTPUT);
pinMode(PIN_TORRE_ENVIO_PAPEL, INPUT_PULLUP);

}

//TORRE
boolean Accion::entradaPapel() {
    //leer pin de entrada papel
    return !digitalRead(PIN_TORRE_ENVIO_PAPEL);
}

//Engrapadora
void Accion::bandaEngrapadora(boolean estado) {
//  if (_bandaEngrapadora == estado) { return; }
//    _bandaEngrapadora = estado;

   Serial.println("bandaEngrapadora: "+ estado);
    
   digitalWrite(PIN_BANDA_ENGRAPDORA, estado);
}

boolean Accion::mitadVueltasAjustePapel() {
    return digitalRead(PIN_LECTURA_AJUSTE_HORIZONTAL_VERTICAL_ENGRAPADORA);
}

void Accion::ajustePapel(boolean estado) {

//    if (_ajustePapel == estado) { return; }
//    _ajustePapel = estado;

    Serial.println("ajustePapel: "+ estado);
    digitalWrite(PIN_AJUSTE_HORIZONTAL_VERTICAL_ENGRAPADORA, estado);
}

void Accion::engrapar(boolean estado) {

//    if (_engrapar == estado) { return; }
//    _engrapar = estado;

    Serial.println("engrapar: "+ estado);
    digitalWrite(PIN_ENGRAPAR, estado);
}

void Accion::avancePapelEngrapadora(boolean estado) {

//    if (_avancePapelEngrapadora == estado) { return; }
//    _avancePapelEngrapadora = estado;

    Serial.println("avancePapelEngrapadora: "+ estado);
    digitalWrite(PIN_AVANCE_PAPEL_ENGRAPDORA, estado);
}

void Accion::bandaDobladora(boolean estado) {
//    if (_bandaDobladora == estado) { return; }
//    _bandaDobladora = estado;

    Serial.println("bandaDobladora: "+ estado);
    digitalWrite(PIN_BANDA_DOBLADORA, estado);
}

void Accion::topeGrapa(boolean estado) {

//    if (_topeGrapa == estado) { return; }
//    _topeGrapa = estado;

    Serial.println("topeGrapa: ");
    digitalWrite(PIN_TOPE_ENGRAPAR, estado);
}

void Accion::doblar(boolean estado) {

//    if (_doblar == estado) { return; }
//    _doblar = estado;

    Serial.println("doblar: "+ estado);
    digitalWrite(PIN_DOBLADORA, estado);
}

void Accion::salidaCorrienteDobladora(boolean estado) {

//    if (_salidaCorrienteDobladora == estado) { return; }
//    _salidaCorrienteDobladora = estado;

    Serial.println("salidaCorrienteDobladora: "+ estado);
    digitalWrite(PIN_SALIDA_CORRIENTE_DOBLADORA, estado);
}

void Accion::bandas(boolean estado) {
    bandaDobladora(estado);
    bandaEngrapadora(estado);
}

