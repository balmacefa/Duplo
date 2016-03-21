#ifndef Proceso_h
#define Proceso_h

#include "Arduino.h"
#include "Accion.h"
#include "Configuracion.h"


class Proceso{
  public:
    Proceso(Accion* accion,unsigned long timeInit);
    Proceso(Accion* accion);
    
    void hacerAjusteEngrape();
    void hacerEngrapar();
    void hacerAvanceDobladora();
    void hacerDoblar();
    boolean esTerminado();
    
    void setModoTest(boolean habilitar);
    
    void calcular();
    
    private:
      Accion* _accion;
      boolean _modoTest;
      boolean _terminado;
      unsigned long _tiempoInicio;
};

#endif
