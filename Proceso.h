#ifndef Proceso_h
#define Proceso_h

#include "Accion.h"
#include "Configuracion.h"
#include "Arduino.h"


class Proceso {
public:
    Proceso(Accion *accion, unsigned long timeInit);

    Proceso(Accion *accion);

    boolean esTerminado();

    void calcular();

    void reiniciarVariables();

private:
    Accion *_accion;
    int _test;
    boolean _terminado;
    unsigned long _tiempoInicio = 0UL;

    boolean esAjustePapel = false;
    boolean esAjustePapelAbrir = false;
    int cantidadMitadVuelta = 0;
    unsigned long sigLecturaAjustePapel = 0UL;

    unsigned long tiempoActual = 0UL;

//    metodos
    void entradaTopePapelEngrapadora();

    void entradaAjusteHorizontalVertical();

    void entradaAjusteHorizontalVertical_PrimerAjuste();
    void entradaAjusteHorizontalVertical_SegundoAjusteRelajar();

    void contarMitadDeVueltasAjustePapel();

    void engrapar();
    void avancePapel();
    void bandasDobladora();

    void entradaTopePapelDobladora();

    void doblar();
    void salidaCorrienteDobladora();
    void finalizar();
};

#endif
