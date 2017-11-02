#ifndef Accion_h
#define Accion_h

#include "Pines.h"
#include "Arduino.h"

class Accion{
  public:
    Accion();
    
    //Acciones de la torre
    boolean entradaPapel();

    //Dobladora
    void salidaCorrienteDobladora(boolean estado);
    void doblar(boolean estado);
    void bandaDobladora(boolean estado);
    
    //Engrapadora
    void ajustePapelHorizontal(boolean estado);
    void ajustePapelVertical(boolean estado);

    void liberarAjusteHorizontal();
    void liberarAjusteVertical();

    void engrapar(boolean estado);
    void topeGrapa(boolean estado);

    boolean mitadVueltasAjustePapelHorizontal();
    boolean mitadVueltasAjustePapelVertical();

    void avancePapelEngrapadora(boolean estado);
    void bandaEngrapadora(boolean estado);
    
    void bandas(boolean estado);

};

#endif
