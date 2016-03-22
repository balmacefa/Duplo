#include "Accion.h"
#include "Proceso.h"

#include <StandardCplusplus.h>
#include <vector>
#include <iterator>

//Indicar si se encuantra en el modo de prueba
boolean modoPrueba = true;

//Indica si la maquina esta haciendo un proceso
boolean enProceso = false;

//Indica si la maquina esta haciendo un Test
boolean enTest = false;

//Indica si las bandas estan encendidas
boolean esBandas = false;

//Almacena los procesos
std::vector<Proceso*> procesos;

//Realiza acciones, se utiliza para encender y apagar las bandas, y leer botones
Accion* accion;

//Para el modo de prueba
Proceso* procesoModoPrueba;

void setup() {
  accion = new Accion();
  procesoModoPrueba = new Proceso(accion);
}

void loop() {
  if( !enProceso && accion->inicioTorre() == true){
    modoPrueba = false;
  }
  if(modoPrueba == true){
    doModoPrueba();
  }
  else{
    if(!esBandas){
      //Mandar se;al de las bandas solo una vez
      //Encender las bandas
      accion->bandas(true);
    }
    
    doModoProcesoCompleto();
  }
}

void doModoPrueba(){
  if(enTest == false){
    //buscar entrada se senal
    if(accion->menuAjusteEngrape() == true){
      enTest = true;
      procesoModoPrueba->hacerAjusteEngrape();
      procesoModoPrueba->setTiempoInicial( millis() );
    }else if(accion->menuEngrapar() == true){
      enTest = true;
      procesoModoPrueba->hacerEngrapar();
      procesoModoPrueba->setTiempoInicial( millis() );
    }else if(accion->menuAvanceDobladora() == true){
      enTest = true;
      procesoModoPrueba->hacerAvanceDobladora();
      procesoModoPrueba->setTiempoInicial( millis() );
    }else if(accion->menuDoblar() == true){
      enTest = true;
      procesoModoPrueba->hacerDoblar();
      procesoModoPrueba->setTiempoInicial( millis() );
    }
  }else{
    procesoModoPrueba->calcularPrueba();
  }
  if(procesoModoPrueba->esTerminado() == true){
    enTest = false;
    procesoModoPrueba->reiniciarVariables();
    procesoModoPrueba->setTiempoInicial( 0UL );
  }
  
}

void doModoProcesoCompleto(){
  //veficar la entrada del papel  
  if(accion->entradaPapel() == true){
    //crear un nuevo proceso y agregar el tiempo en que ocurrio
    procesos.push_back( new Proceso(accion, millis()) );

    //colocar la maquina como trabajando
    enProceso = true;
  }
  //si la maquina esta trabajando
  if( enProceso == true ){
    //calcular los procesos
    //Del mas antiguo al reciente
    for(int i = procesos.size() - 1; i >= 0; i-- ){
      Proceso* pActual = procesos.at(i);
      pActual->calcular();  
      //buscar si un proceso fue terminado
      if(pActual->esTerminado()){
        //eliminar de la lista
        procesos.erase(procesos.begin()+i-1);
        delete pActual;
      }
    }
    //si los elementos de la lista son 0 se termina el equipo
    if(procesos.size() == 0){
      enProceso == false;
      //colocar en modo de prueba
      modoPrueba = true;
      
      //Apagar las bandas
      accion->bandas(false);
      esBandas = false;
    }
  }
}
