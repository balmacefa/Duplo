#include "Proceso.h"

Proceso::Proceso(Accion *accion, unsigned long timeInit) {
    _accion = accion;
    _tiempoInicio = timeInit;
    _terminado = false;
}

Proceso::Proceso(Accion *accion) {
    _accion = accion;
    _terminado = false;
}

void Proceso::reiniciarVariables() {
    esAjustePapel = false;
    esAjustePapelAbrir = false;
    cantidadMitadVuelta = 0;
    sigLecturaAjustePapel = 0UL;
    tiempoActual = 0UL;
}

boolean Proceso::esTerminado() {
    return _terminado;
}

void Proceso::entradaTopePapelEngrapadora() {
    if (tiempoActual >= TIM_ENTRADA_TOPE_ENGRAPAR) {
        _accion->topeGrapa(true);

    } else if (tiempoActual >= (TIM_ENTRADA_TOPE_ENGRAPAR + TIM_SIG_TOPE_ENGRAPAR)) {
        //Desactivar senal del tope de papel
        _accion->topeGrapa(false);
    }
}

void Proceso::entradaAjusteHorizontalVertical() {

    entradaAjusteHorizontalVertical_PrimerAjuste();

    entradaAjusteHorizontalVertical_SegundoAjusteRelajar();

}

void Proceso::entradaAjusteHorizontalVertical_PrimerAjuste(){
    if (!esAjustePapel && tiempoActual >= TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL) {
        _accion->ajustePapel(true);
        esAjustePapel = true;
        sigLecturaAjustePapel = tiempoActual;
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
        _accion->ajustePapel(true);
        esAjustePapelAbrir = true;
        sigLecturaAjustePapel = tiempoActual;
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
    if (tiempoActual >= sigLecturaAjustePapel && _accion->mitadVueltasAjustePapel()) {
        //aumentar cantidad de vueltas
        cantidadMitadVuelta++;
        //Ajustar el nuevo tiempo para preguntar
        sigLecturaAjustePapel = tiempoActual + FRECUENCIA_LECTURA_AJUSTE_PAPEL;
    }
}

void Proceso::engrapar(){
    if (tiempoActual >= TIM_ENTRADA_ENGRAPAR) {
        _accion->engrapar(true);
    }
    //Desactivar senal de engrapadora
    if (tiempoActual >= (TIM_ENTRADA_ENGRAPAR + TIM_SIG_ENGRAPAR)) {
        _accion->engrapar(false);
    }
}

void Proceso::avancePapel() {
    //avance del papel
    if (tiempoActual >= TIM_ENTRADA_AVANCE_PAPEL_ENGRAPADORA) {
        _accion->avancePapelEngrapadora(true);
    }
    //Desactivar senal de avance papel
    if (tiempoActual >= (TIM_ENTRADA_AVANCE_PAPEL_ENGRAPADORA + TIM_SIG_AVANCE_PAPEL_ENGRAPADORA)) {
        _accion->avancePapelEngrapadora(false);
    }
}

void Proceso::bandasDobladora() {
    //activar las bandas de la dobladora
    if (tiempoActual >= (TIM_ENTRADA_BANDAS_DOBLADORA)) {
        _accion->bandaDobladora(true);
    }
}

void Proceso::entradaTopePapelDobladora() {
    if (tiempoActual >= TIM_ENTRADA_TOPE_DOBLADORA) {
        _accion->topeDobladora(true);

    } else if (tiempoActual >= (TIM_ENTRADA_TOPE_DOBLADORA + TIM_SIG_TOPE_DOBLADORA)) {
        //Desactivar senal del tope de papel
        _accion->topeDobladora(false);
    }
}

void Proceso::doblar() {
    //activar la dobladora
    if (tiempoActual >= (TIM_ENTRADA_DOBLADORA)) {
        _accion->doblar(true);
    }

    //desactivar dobladora
    if (tiempoActual >= (TIM_ENTRADA_DOBLADORA + TIM_SIG_DOBLADORA)) {
        _accion->doblar(false);
    }
}

void Proceso::salidaCorrienteDobladora() {
    //activar salida final del papel
    if (tiempoActual >= (TIM_ENTRADA_SALIDA_CORRIENTE_DOBLADORA)) {
        _accion->salidaCorrienteDobladora(true);
    }

    //si ya se termino el proceso
    if (tiempoActual >= (TIM_ENTRADA_SALIDA_CORRIENTE_DOBLADORA + TIM_SIG_SALIDA_CORRIENTE_DOBLADORA)) {
        //Ya hemos terminado
        finalizar();
    }
}

void Proceso::finalizar(){
    //Desactivar la salida de corriente
    _accion->bandaDobladora(false);
    _accion->salidaCorrienteDobladora(false);
    _terminado = true;
}

void Proceso::calcular() {

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
    bandasDobladora();
    entradaTopePapelDobladora();

    doblar();

    salidaCorrienteDobladora();
}
