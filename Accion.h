#ifndef Accion_h
#define Accion_h

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
    
    //Dobladora
    void topeGrapa(boolean estado);
    void salidaCorrienteDobladora(boolean estado);
    void doblar(boolean estado);
    void bandaDobladora(boolean estado);
    
    //Engrapadora
    void ajustePapel(boolean estado);
    void engrapar(boolean estado);
    boolean mitadVueltasAjustePapel();
    void avancePapelEngrapadora(boolean estado);
    void bandaEngrapadora(boolean estado);
    
    void bandas(boolean estado);
    
    
};

#endif
