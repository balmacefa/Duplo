#ifndef Proceso_h
#define Proceso_h

#include "Arduino.h"

class Proceso{
  public:
    Proceso(unsigned long timeInit);
    void hacerAjusteEngrape();
    void hacerEngrapar();
    void hacerAvanceDobladora();
    void hacerDoblar();
    boolean esTerminado();
    
    void calcular();
};

#endif
