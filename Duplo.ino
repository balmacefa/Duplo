#include <Arduino.h>

#include "Accion.h"
#include "Proceso.h"

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

//Almacena los procesos
std::vector<Proceso *> procesos;

//Realiza acciones, se utiliza para encender y apagar las bandas, y leer botones
Accion *accion;

//Indicar si la entrada de papel es la misma, para no enviar la se;al varias veces
bool mismoPapel;

void setup() {
    accion = new Accion();

    accion->liberarAjusteHorizontal();
    accion->liberarAjusteVertical();

    accion->bandas(true);
}

void loop() {
    doModoProcesoCompleto();
}

void doModoProcesoCompleto() {
    //veficar la entrada del papel
    verificarEntradaPapel();

    //calcular todos los procesos
    ejecutarProcesos();
}

bool entradaPapel() {
    if(!accion->entradaPapel()){
        mismoPapel = false;
        return false;
    }
    if( !mismoPapel && accion->entradaPapel() ) {
        mismoPapel = true;
        return true;
    }
    return false;
}

void verificarEntradaPapel() {
    if (entradaPapel()) {
        nuevoProceso();
    }
}

void nuevoProceso() {
    if (procesos.size() > 0) {
        //buscar algun proceso terminado y reiniciar
        for (int i = 0; i < procesos.size(); ++i) {
            if (procesos[i]->esTerminado()) {
                //reiniciar las variables y setear el tiempo
                procesos[i]->reiniciar(millis());
                return;
            }
        }
    }
    //Se necesitan mas procesos
    //crear un nuevo proceso y agregar el tiempo en que ocurrio
    procesos.push_back(new Proceso(accion, millis()));
}

void ejecutarProcesos() {
    //si la maquina esta trabajando
    if (procesos.size() > 0) {
        //calcular los procesos
        for (int i = 0; i < procesos.size(); ++i) {
            if (!procesos[i]->esTerminado()) {
                procesos[i]->calcular();
            }
        }
    }
}
