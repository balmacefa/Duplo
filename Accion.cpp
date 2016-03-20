#include "Accion.h"

//constructor
Accion::Accion(){

}

//Metos de leectura del menu
boolean Accion::menuAjusteEngrape(){
  return digitalRead(PIN_MENU_AJUSTES_ENGRAPE);
}

boolean Accion::menuEngrapar(){
  return digitalRead(PIN_MENU_ENGRAPAR);
}

boolean Accion::menuAvanceDobladora(){
  return digitalRead(PIN_MENU_AVANCE_DOBLADORA);

}
boolean Accion::menuDoblar(){
  return digitalRead(PIN_MENU_DOBLAR);
}

