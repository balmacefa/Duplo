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
