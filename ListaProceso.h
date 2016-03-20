#ifndef ListaProceso_h
#define ListaProceso_h


#include "Proceso.h"
#include "Accion.h"

class ListaProceso{
  public:
    ListaProceso(Accion* accion);
    void add(Proceso* proceso);
    int legth();
    Proceso* get(int index);
    void eliminar(int index);
};

#endif
