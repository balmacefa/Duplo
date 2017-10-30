#include <Arduino.h>

#include "Accion.h"
#include "Proceso.h"

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

//Indica si la maquina esta haciendo un proceso
boolean enProceso = false;

unsigned long siguienteVerificacionDeEntradaDePapel;

//Almacena los procesos
std::vector<Proceso *> procesos;

//Realiza acciones, se utiliza para encender y apagar las bandas, y leer botones
Accion *accion;


void setup() {
    accion = new Accion();

    siguienteVerificacionDeEntradaDePapel = 0UL;

//    procesos.push_back(new Proceso(accion, millis()));
//
//        //colocar la maquina como trabajando
//        enProceso = true;
    accion->bandas(true);
    Serial.begin(9600);
    Serial.println("DUPLO");
    
}

void loop() {
    doModoProcesoCompleto();
}

void doModoProcesoCompleto() {
    //veficar la entrada del papel
    verificarEntradaPapel();

    //calcular todos los procesos
    ejecutarProcesos();

    //verificar si ya no existen procesos
    terminarProcesos();
}

bool entradaPapel(){
    return Serial.available() > 0;

//    accion->entradaPapel()
}

void verificarEntradaPapel(){
    if ( millis() >= siguienteVerificacionDeEntradaDePapel && entradaPapel() == true) {
      siguienteVerificacionDeEntradaDePapel = millis() + TIM_FRECUENCIA_REVISAR_ENTRADA_PAPEL_TORRE;
      
      Serial.println("entrada de papel");
        //crear un nuevo proceso y agregar el tiempo en que ocurrio
        procesos.push_back(new Proceso(accion, millis()));

        //colocar la maquina como trabajando
        enProceso = true;
    }
}

void ejecutarProcesos(){
    //si la maquina esta trabajando
    if (enProceso == true) {
        //calcular los procesos
        //Del mas antiguo al reciente
        for (int i = procesos.size() - 1; i >= 0; i--) {
            Proceso *pActual = procesos.at(i);
            pActual->calcular();
            //buscar si un proceso fue terminado
            if (pActual->esTerminado()) {
                //eliminar de la lista
                procesos.erase(procesos.begin() + i - 1);
                delete pActual;
            }
        }
    }
}

void terminarProcesos(){
    //si los elementos de la lista son 0 se termina el equipo
    if (procesos.size() == 0) {
        enProceso == false;
    }
}
