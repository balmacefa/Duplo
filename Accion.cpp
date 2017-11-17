#include "Accion.h"

//constructor
Accion::Accion() {
//configurar pines

    pinMode(PIN_BANDA_ENGRAPDORA, OUTPUT);
    pinMode(PIN_AJUSTE_HORIZONTAL_ENGRAPADORA, OUTPUT);
    pinMode(PIN_AJUSTE_VERTICAL_ENGRAPADORA, OUTPUT);
    pinMode(PIN_AVANCE_PAPEL_ENGRAPDORA, OUTPUT);
    pinMode(PIN_ENGRAPAR, OUTPUT);
    pinMode(PIN_TOPE_ENGRAPAR, OUTPUT);
    pinMode(PIN_BANDA_DOBLADORA, OUTPUT);
    pinMode(PIN_DOBLADORA, OUTPUT);
    pinMode(PIN_SALIDA_CORRIENTE_DOBLADORA, OUTPUT);

    //inputs
    pinMode(PIN_TORRE_ENVIO_PAPEL, INPUT);
    pinMode(PIN_LECTURA_AJUSTE_HORIZONTAL_ENGRAPADORA, INPUT);
    pinMode(PIN_LECTURA_AJUSTE_VERTICAL_ENGRAPADORA, INPUT);

}

//TORRE
boolean Accion::entradaPapel() {
    //leer pin de entrada papel
    return !digitalRead(PIN_TORRE_ENVIO_PAPEL);
}

//Engrapadora
void Accion::bandaEngrapadora(boolean estado) {
    digitalWrite(PIN_BANDA_ENGRAPDORA, estado);
}

boolean Accion::mitadVueltasAjustePapelHorizontal() {
    return digitalRead(PIN_LECTURA_AJUSTE_HORIZONTAL_ENGRAPADORA);
}

boolean Accion::mitadVueltasAjustePapelVertical() {
    //inverse logic
    return !digitalRead(PIN_LECTURA_AJUSTE_VERTICAL_ENGRAPADORA);
}

void Accion::ajustePapelHorizontal(boolean estado) {
    digitalWrite(PIN_AJUSTE_HORIZONTAL_ENGRAPADORA, estado);
}

void Accion::ajustePapelVertical(boolean estado) {
    //!estado por el rele
    digitalWrite(PIN_AJUSTE_VERTICAL_ENGRAPADORA, !estado);
}

void Accion::liberarAjusteHorizontal() {
    while (!mitadVueltasAjustePapelHorizontal()) {
        ajustePapelHorizontal(true);
    }
    ajustePapelHorizontal(false);
}

void Accion::liberarAjusteVertical() {
    while (!mitadVueltasAjustePapelVertical()) {
        ajustePapelVertical(true);
    }
    ajustePapelVertical(false);
}

void Accion::engrapar(boolean estado) {
    digitalWrite(PIN_ENGRAPAR, estado);
}

void Accion::avancePapelEngrapadora(boolean estado) {
    digitalWrite(PIN_AVANCE_PAPEL_ENGRAPDORA, estado);
}

void Accion::bandaDobladora(boolean estado) {
    digitalWrite(PIN_BANDA_DOBLADORA, estado);
}

void Accion::topeGrapa(boolean estado) {
    digitalWrite(PIN_TOPE_ENGRAPAR, estado);
}

void Accion::doblar(boolean estado) {
    digitalWrite(PIN_DOBLADORA, estado);
}

void Accion::salidaCorrienteDobladora(boolean estado) {
    digitalWrite(PIN_SALIDA_CORRIENTE_DOBLADORA, estado);
}

void Accion::bandas(boolean estado) {
    bandaDobladora(estado);
    bandaEngrapadora(estado);
}

