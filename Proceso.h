#ifndef Proceso_h
#define Proceso_h

#include "Arduino.h"
#include "Accion.h"

class Proceso{
  public:
    Proceso(Accion* accion,unsigned long timeInit);
    Proceso(Accion* accion);
    
    void hacerAjusteEngrape();
    void hacerEngrapar();
    void hacerAvanceDobladora();
    void hacerDoblar();
    boolean esTerminado();
    
    void calcular();
    
    private:
      Accion* _accion;
};

#endif
