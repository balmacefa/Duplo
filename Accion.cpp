#include "Accion.h"

//constructor
Accion::Accion() {

}

//TORRE
boolean Accion::entradaPapel() {
    //leer pin de entrada papel
    return digitalRead(PIN_TORRE_ENVIO_PAPEL);
}

//Engrapadora
void Accion::bandaEngrapadora(boolean estado) {
    digitalWrite(PIN_BANDA_ENGRAPDORA, estado);
}

boolean Accion::mitadVueltasAjustePapel() {
    return digitalRead(PIN_LECTURA_AJUSTE_HORIZONTAL_VERTICAL_ENGRAPADORA);
}

void Accion::ajustePapel(boolean estado) {

    if (_ajustePapel == estado) { return; }
    _ajustePapel = estado;

    digitalWrite(PIN_AJUSTE_HORIZONTAL_VERTICAL_ENGRAPADORA, estado);
}

void Accion::engrapar(boolean estado) {

    if (_engrapar == estado) { return; }
    _engrapar = estado;

    digitalWrite(PIN_ENGRAPAR, estado);
}

void Accion::avancePapelEngrapadora(boolean estado) {

    if (_avancePapelEngrapadora == estado) { return; }
    _avancePapelEngrapadora = estado;

    digitalWrite(PIN_AVANCE_PAPEL_ENGRAPDORA, estado);
}

void Accion::topeDobladora(boolean estado) {
    if (_topeDobladora == estado) { return; }
    _topeDobladora = estado;

    digitalWrite(PIN_TOPE_DOBLAR, estado);
}

void Accion::bandaDobladora(boolean estado) {
    if (_bandaDobladora == estado) { return; }
    _bandaDobladora = estado;

    digitalWrite(PIN_BANDA_DOBLADORA, estado);
}

void Accion::topeGrapa(boolean estado) {

    if (_topeGrapa == estado) { return; }
    _topeGrapa = estado;

    digitalWrite(PIN_TOPE_ENGRAPAR, estado);

}

void Accion::doblar(boolean estado) {

    if (_doblar == estado) { return; }
    _doblar = estado;

    digitalWrite(PIN_DOBLADORA, estado);
}

void Accion::salidaCorrienteDobladora(boolean estado) {

    if (_salidaCorrienteDobladora == estado) { return; }
    _salidaCorrienteDobladora = estado;

    digitalWrite(PIN_SALIDA_CORRIENTE_DOBLADORA, estado);
}

void Accion::bandas(boolean estado) {
    bandaDobladora(estado);
    bandaEngrapadora(estado);
}

