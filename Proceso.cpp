#include "Proceso.h"

Proceso::Proceso(Accion *accion, unsigned long timeInit) {
    _accion = accion;
    _tiempoInicio = timeInit;
    _terminado = false;
}

void Proceso::reiniciar(unsigned long nuevoTiempoInicio) {
    _tiempoInicio = nuevoTiempoInicio;
    _esAjustePapel = false;
    _esAjustePapelAbrir = false;
    _cantidadMitadVuelta = 0;
    _terminado = false;
    _tiempoActual = 0UL;

    _entrada_entradaTopePapelEngrapadora = false;
    _salida_entradaTopePapelEngrapadora = false;

    _estadoMitadDevuleta = false;

    _lectura = false;

    _entrada_engrapar = false;
    _salida_engrapar = false;

    _entrada_avancePapel = false;
    _salida_avancePapel = false;

    _entrada_doblar = false;
    _salida_doblar = false;

    _entrada_salidaCorrienteDobladora = false;
    _salida_salidaCorrienteDobladora = false;

}

boolean Proceso::esTerminado() {
    return _terminado;
}


void Proceso::entradaTopePapelEngrapadora() {
    if (!_entrada_entradaTopePapelEngrapadora && _tiempoActual >= TIM_ENTRADA_TOPE_ENGRAPAR) {
        _entrada_entradaTopePapelEngrapadora = true;
        _accion->topeGrapa(true);
    }
    if (!_salida_entradaTopePapelEngrapadora && _tiempoActual >= (TIM_ENTRADA_TOPE_ENGRAPAR + TIM_SIG_TOPE_ENGRAPAR)) {
        //Desactivar senal del tope de papel
        _salida_entradaTopePapelEngrapadora = true;
        _accion->topeGrapa(false);
    }
}

void Proceso::entradaAjusteHorizontalVertical() {

    entradaAjusteHorizontalVertical_PrimerAjuste();

    entradaAjusteHorizontalVertical_SegundoAjusteRelajar();

}

void Proceso::entradaAjusteHorizontalVertical_PrimerAjuste() {
    if (!_esAjustePapel && _tiempoActual >= TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL) {
        _estadoMitadDevuleta = _accion->mitadVueltasAjustePapel();
        _accion->ajustePapel(true);
        _esAjustePapel = true;
    }

    //Contar cantidad de mitad de vueltas de los motores
    if (_esAjustePapel) {
        contarMitadDeVueltasAjustePapel();
    }

    //desactivas los ajustes verticales despues de 4 mitad de vueltas
    if ((_esAjustePapel && _cantidadMitadVuelta >= MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL)) {
        _accion->ajustePapel(false);
        _cantidadMitadVuelta = 0;
    }
}

void Proceso::entradaAjusteHorizontalVertical_SegundoAjusteRelajar() {

    if ((!_esAjustePapelAbrir && _tiempoActual >= (TIM_ENTRADA_AJUSTE_HORI_VERT_PAPEL_DEJAR_PASAR))) {
        _estadoMitadDevuleta = _accion->mitadVueltasAjustePapel();
        _accion->ajustePapel(true);
        _esAjustePapelAbrir = true;
    }

    //Contar cantidad de mitad de vueltas de los motores
    if (_esAjustePapelAbrir) {
        contarMitadDeVueltasAjustePapel();
    }

    //desactivas los ajustes verticales despues de 4 mitad de vueltas
    if ((_esAjustePapelAbrir && _cantidadMitadVuelta == MITAD_VUELTAS_AJUSTE_HORI_VERT_PAPEL_DEJAR_PASAR)) {
        _accion->ajustePapel(false);
        _cantidadMitadVuelta = 0;
    }
}

void Proceso::contarMitadDeVueltasAjustePapel() {
    //frecuencia para preguntar
    _lectura = _accion->mitadVueltasAjustePapel();

    if (_lectura != _estadoMitadDevuleta) {
        _estadoMitadDevuleta = _lectura;
        //aumentar cantidad de vueltas
        _cantidadMitadVuelta++;
    }
}

void Proceso::engrapar() {
    if (!_entrada_engrapar && _tiempoActual >= TIM_ENTRADA_ENGRAPAR) {
        _entrada_engrapar = true;
        _accion->engrapar(true);
    }
    //Desactivar senal de engrapadora
    if (!_salida_engrapar && _tiempoActual >= (TIM_ENTRADA_ENGRAPAR + TIM_SIG_ENGRAPAR)) {
        _salida_engrapar = true;
        _accion->engrapar(false);
    }
}

void Proceso::avancePapel() {
    //avance del papel
    if (!_entrada_avancePapel && _tiempoActual >= TIM_ENTRADA_AVANCE_PAPEL_ENGRAPADORA) {
        _entrada_avancePapel = true;
        _accion->avancePapelEngrapadora(true);
    }
    //Desactivar senal de avance papel
    if (!_salida_avancePapel &&
        _tiempoActual >= (TIM_ENTRADA_AVANCE_PAPEL_ENGRAPADORA + TIM_SIG_AVANCE_PAPEL_ENGRAPADORA)) {
        _salida_avancePapel = true;
        _accion->avancePapelEngrapadora(false);
    }
}

void Proceso::doblar() {
    //activar la dobladora
    if (!_entrada_doblar && _tiempoActual >= (TIM_ENTRADA_DOBLADORA)) {
        _entrada_doblar = true;
        _accion->doblar(true);
    }

    //desactivar dobladora
    if (!_salida_doblar && _tiempoActual >= (TIM_ENTRADA_DOBLADORA + TIM_SIG_DOBLADORA)) {
        _salida_doblar = true;
        _accion->doblar(false);
    }
}

void Proceso::salidaCorrienteDobladora() {
    //activar salida final del papel
    if (!_entrada_salidaCorrienteDobladora && _tiempoActual >= (TIM_ENTRADA_SALIDA_CORRIENTE_DOBLADORA)) {
        _entrada_salidaCorrienteDobladora = true;
        _accion->salidaCorrienteDobladora(true);
    }

    //si ya se termino el proceso
    if (!_salida_salidaCorrienteDobladora &&
        _tiempoActual >= (TIM_ENTRADA_SALIDA_CORRIENTE_DOBLADORA + TIM_SIG_SALIDA_CORRIENTE_DOBLADORA)) {
        //Ya hemos terminado
        _salida_salidaCorrienteDobladora = true;
        finalizar();
    }
}

void Proceso::finalizar() {
//    //Desactivar la salida de corriente
//    _accion->bandaDobladora(false);
    _accion->salidaCorrienteDobladora(false);
    _terminado = true;
    Serial.println("Fin proceso");
}

void Proceso::calcular() {
    if (_terminado) { return; }

    //Calcular el offset del tiempo
    _tiempoActual = millis() - _tiempoInicio;

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
