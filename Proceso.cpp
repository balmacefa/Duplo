#include "Proceso.h"

Proceso::Proceso(Accion *accion, unsigned long timeInit) {
    _accion = accion;
    _tiempoInicio = timeInit;
    _terminado = false;
}

void Proceso::reiniciarVariables() {
    esAjustePapel = false;
    esAjustePapelAbrir = false;
    cantidadMitadVuelta = 0;
    tiempoActual = 0UL;
}

boolean Proceso::esTerminado() {
    return _terminado;
}

bool entrada_entradaTopePapelEngrapadora;
bool salida_entradaTopePapelEngrapadora;

void Proceso::entradaTopePapelEngrapadora() {
    if ( !entrada_entradaTopePapelEngrapadora && tiempoActual >= TIM_ENTRADA_TOPE_ENGRAPAR) {
        entrada_entradaTopePapelEngrapadora = true;
        _accion->topeGrapa(true);
    }
    if (!salida_entradaTopePapelEngrapadora && tiempoActual >= (TIM_ENTRADA_TOPE_ENGRAPAR + TIM_SIG_TOPE_ENGRAPAR)) {
        //Desactivar senal del tope de papel
        salida_entradaTopePapelEngrapadora = true;
        _accion->topeGrapa(false);
    }
}

void Proceso::entradaAjusteHorizontalVertical() {

    entradaAjusteHorizontalVertical_PrimerAjuste();

    entradaAjusteHorizontalVertical_SegundoAjusteRelajar();

}

bool estadoMitadDevuleta;
void Proceso::entradaAjusteHorizontalVertical_PrimerAjuste(){
    if (!esAjustePapel && tiempoActual >= TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL) {
        estadoMitadDevuleta = _accion->mitadVueltasAjustePapel();
        _accion->ajustePapel(true);
        esAjustePapel = true;
    }

    //Contar cantidad de mitad de vueltas de los motores
    if (esAjustePapel) {
        contarMitadDeVueltasAjustePapel();
    }

    //desactivas los ajustes verticales despues de 4 mitad de vueltas
    if ((esAjustePapel && cantidadMitadVuelta >= MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL)){
        _accion->ajustePapel(false);
        cantidadMitadVuelta = 0;
    }
}

void Proceso::entradaAjusteHorizontalVertical_SegundoAjusteRelajar(){

    if ((!esAjustePapelAbrir && tiempoActual >= (TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL_DEJAR_PASAR))) {
        estadoMitadDevuleta = _accion->mitadVueltasAjustePapel();
        _accion->ajustePapel(true);
        esAjustePapelAbrir = true;
    }

    //Contar cantidad de mitad de vueltas de los motores
    if (esAjustePapelAbrir) {
        contarMitadDeVueltasAjustePapel();
    }

    //desactivas los ajustes verticales despues de 4 mitad de vueltas
    if ((esAjustePapelAbrir && cantidadMitadVuelta == MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL_DEJAR_PASAR)) {
        _accion->ajustePapel(false);
        cantidadMitadVuelta = 0;
    }
}

void Proceso::contarMitadDeVueltasAjustePapel(){
    //frecuencia para preguntar
    bool lectura = _accion->mitadVueltasAjustePapel();

    if (lectura != estadoMitadDevuleta) {
        estadoMitadDevuleta = lectura;
        //aumentar cantidad de vueltas
        cantidadMitadVuelta++;
    }
}

bool entrada_engrapar;
bool salida_engrapar;
void Proceso::engrapar(){
    if (!entrada_engrapar && tiempoActual >= TIM_ENTRADA_ENGRAPAR) {
        entrada_engrapar = true;
        _accion->engrapar(true);
    }
    //Desactivar senal de engrapadora
    if (!salida_engrapar && tiempoActual >= (TIM_ENTRADA_ENGRAPAR + TIM_SIG_ENGRAPAR)) {
        salida_engrapar = true;
        _accion->engrapar(false);
    }
}

bool entrada_avancePapel;
bool salida_avancePapel;
void Proceso::avancePapel() {
    //avance del papel
    if (!entrada_avancePapel && tiempoActual >= TIM_ENTRADA_AVANCE_PAPEL_ENGRAPADORA) {
        entrada_avancePapel = true;
        _accion->avancePapelEngrapadora(true);
    }
    //Desactivar senal de avance papel
    if (!salida_avancePapel && tiempoActual >= (TIM_ENTRADA_AVANCE_PAPEL_ENGRAPADORA + TIM_SIG_AVANCE_PAPEL_ENGRAPADORA)) {
        salida_avancePapel = true;
        _accion->avancePapelEngrapadora(false);
    }
}

bool entrada_doblar;
bool salida_doblar;
void Proceso::doblar() {
    //activar la dobladora
    if (!entrada_doblar && tiempoActual >= (TIM_ENTRADA_DOBLADORA)) {
        entrada_doblar = true;
        _accion->doblar(true);
    }

    //desactivar dobladora
    if (!salida_doblar && tiempoActual >= (TIM_ENTRADA_DOBLADORA + TIM_SIG_DOBLADORA)) {
        salida_doblar = true;
        _accion->doblar(false);
    }
}

bool entrada_salidaCorrienteDobladora;
bool salida_salidaCorrienteDobladora;
void Proceso::salidaCorrienteDobladora() {
    //activar salida final del papel
    if (!entrada_salidaCorrienteDobladora && tiempoActual >= (TIM_ENTRADA_SALIDA_CORRIENTE_DOBLADORA)) {
        entrada_salidaCorrienteDobladora = true;
        _accion->salidaCorrienteDobladora(true);
    }

    //si ya se termino el proceso
    if (!salida_salidaCorrienteDobladora && tiempoActual >= (TIM_ENTRADA_SALIDA_CORRIENTE_DOBLADORA + TIM_SIG_SALIDA_CORRIENTE_DOBLADORA)) {
        //Ya hemos terminado
        salida_salidaCorrienteDobladora = true;
        finalizar();
    }
}

void Proceso::finalizar(){
//    //Desactivar la salida de corriente
//    _accion->bandaDobladora(false);
    _accion->salidaCorrienteDobladora(false);
    _terminado = true;
    Serial.println("Fin proceso");
}

void Proceso::calcular() {
    if(_terminado){return;}
    
    //Calcular el offset del tiempo
    tiempoActual = millis() - _tiempoInicio;

    //Entrada del tope de papel
    entradaTopePapelEngrapadora();

    //activar los ajuste de papel
    entradaAjusteHorizontalVertical();

    //Engrapar
    //Entrada de la engrapadora
    engrapar();

    avancePapel();

    //Dobladora

    doblar();

    salidaCorrienteDobladora();
}
