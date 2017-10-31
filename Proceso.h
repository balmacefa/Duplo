#ifndef Proceso_h
#define Proceso_h

#include "Accion.h"
#include "Configuracion.h"
#include "Arduino.h"


class Proceso {
public:
    Proceso(Accion *accion, unsigned long timeInit);

    boolean esTerminado();

    void calcular();

    void reiniciar(unsigned long nuevoTiempoInicio);

private:
    Accion *_accion;

    boolean _terminado;
    unsigned long _tiempoInicio = 0UL;

    boolean _esAjustePapel = false;
    boolean _esAjustePapelAbrir = false;
    int _cantidadMitadVuelta = 0;

    unsigned long _tiempoActual = 0UL;


    //utils
    bool _entrada_entradaTopePapelEngrapadora = false;
    bool _salida_entradaTopePapelEngrapadora = false;

    bool _estadoMitadDevuleta = false;

    bool _lectura = false;

    bool _entrada_engrapar = false;
    bool _salida_engrapar = false;

    bool _entrada_avancePapel = false;
    bool _salida_avancePapel = false;

    bool _entrada_doblar = false;
    bool _salida_doblar = false;

    bool _entrada_salidaCorrienteDobladora = false;
    bool _salida_salidaCorrienteDobladora = false;



//    metodos
    void entradaTopePapelEngrapadora();

    void entradaAjusteHorizontalVertical();

    void entradaAjusteHorizontalVertical_PrimerAjuste();
    void entradaAjusteHorizontalVertical_SegundoAjusteRelajar();

    void contarMitadDeVueltasAjustePapel();

    void engrapar();
    void avancePapel();
    void bandasDobladora();

    void doblar();
    void salidaCorrienteDobladora();
    void finalizar();
};

#endif
