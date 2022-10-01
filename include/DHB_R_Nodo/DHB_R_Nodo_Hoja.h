#ifndef DYNAMIC_HILBERT_R_NODO_HOJA_H
#define DYNAMIC_HILBERT_R_NODO_HOJA_H

#include "DHB_R_Nodo.h"
#include "Entrada/Entrada_Hoja.h"
#include <list>

using namespace std;

struct DHB_R_Nodo_Hoja: public DHB_R_Nodo
{
    DHB_R_Nodo_Hoja();
    list<Entrada_Hoja> entradas;
};

#endif