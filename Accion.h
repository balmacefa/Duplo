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
    void topeDobladora(boolean estado);
    
    //Engrapadora
    void ajustePapel(boolean estado);
    void engrapar(boolean estado);
    void topeGrapa(boolean estado);

//    quizas no haga falta
    boolean mitadVueltasAjustePapel();

    void avancePapelEngrapadora(boolean estado);
    void bandaEngrapadora(boolean estado);
    
    void bandas(boolean estado);

private:
    bool _topeGrapa = false;
    bool _ajustePapel = false;
    bool _engrapar = false;
    bool  _avancePapelEngrapadora = false;
    bool _bandaDobladora = false;
    bool  _doblar = false;
    bool _salidaCorrienteDobladora = false;
    bool  _topeDobladora = false;
};

#endif
