#include "Accion.h"

//Indicar si se encuantra en el modo de prueba
boolean modoPrueba;

//Indica si la maquina esta haciendo un proceso
boolean enProceso;

//Indica si la maquina esta haciendo un Test
boolean enTest;

//Almacena los procesos
Proceso[] procesos;

//Realiza acciones, se utiliza para encender y apagar las bandas, y leer botones
Accion accion;

//Para el modo de prueba
Proceso procesoModoPueba;


void setup() {

}

void loop() {
  if( !enProceso && accion.inicioTorre() == true){
    modoPrueba = false;
  }
  if(modoPrueba == true){
    doModoPrueba();
  }
  else{
    doModoProcesoCompleto();
  }
}

void doModoPrueba(){
  if(enTest == false){
    //buscar entrada se senal
    if(accion.menuAjusteEngrape() == true){
      enTest = true;
      procesoModoPrueba.hacerAjusteEngrape();
      
    }else if(accion.menuEngrapar() == true){
      enTest = true;
      procesoModoPrueba.hacerEngrapar();
      
    }else if(accion.menuAvanceDobladora() == true){
      enTest = true;
      procesoModoPrueba.hacerAvanceDobladora();
      
    }else if(accion.menuDoblar() == true){
      enTest = true;
      procesoModoPrueba.hacerDoblar();
    }
    
  }
  if(procesoModoPrueba.esTerminado() == true){
    enTest = false;
  }
}

void doModoProcesoCompleto(){
  //veficar la entrada del papel  
  if(accion.entradaPapel() == true){
    //crear un nuevo proceso y agregar el tiempo en que ocurrio
    procesos.add( new Proceso(millis()) );

    //colocar la maquina como trabajando
    enProceso = true;
  }
  //si la maquina esta trabajando
  if( enProceso == true ){
    //calcular los procesos
    //Del mas antiguo al reciente
    for(int i = procesos.legth() - 1; i >= 0; i-- ){
      Proceso pActual = procesos.get(i);
      pActual.calcular();  
      //buscar si un proceso fue terminado
      if(pActual.esTerminado()){
        //eliminar de la lista
        processos.eliminar(i);
      }
    }
    //si los elementos de la lista son 0 se termina el equipo
    if(procesos.legth() == 0){
      enProceso == false;
      //colocar en modo de prueba
      modoPrueba = true;
    }
  }
}
