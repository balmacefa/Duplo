#include "Pines.h"
#include "Arduino.h"

class Accion{
  public:
    Accion();
    boolean menuAjusteEngrape();  
    boolean menuEngrapar();
    boolean menuAvanceDobladora();
    boolean menuDoblar();
    
    //Acciones de la torre
    boolean entradaPapel();
    boolean inicioTorre();
};
