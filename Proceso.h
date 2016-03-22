#ifndef Proceso_h
#define Proceso_h

#include "Accion.h"
#include "Configuracion.h"
#include "Arduino.h"


class Proceso{
  public:
    Proceso(Accion* accion,unsigned long timeInit);
    Proceso(Accion* accion);
    
    void hacerAjusteEngrape();
    void hacerEngrapar();
    void hacerAvanceDobladora();
    void hacerDoblar();
    boolean esTerminado();
    
    void setTiempoInicial( unsigned long timeInit);
    void calcularPrueba();    
    void calcular();
    void reiniciarVariables();
    
    private:
      Accion* _accion;
      int _test;
      boolean _terminado;
      unsigned long _tiempoInicio = 0UL;
      
      boolean esSalidaCorrienteDobladora = false;
      boolean esTope = false;
      boolean esAjustePapel = false;
      boolean esAjustePapelAbrir = false;
      boolean esEngrapar = false;
      boolean esAvancePapelEngrapadora = false;
      boolean esDoblar = false;
      int cantidadMitadVuelta = 0;
      unsigned long sigLecturaAjustePapel = 0UL;
};

#endif
