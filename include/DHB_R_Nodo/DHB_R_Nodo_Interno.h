#ifndef DYNAMIC_HILBERT_R_NODO_INTERNO_H
#define DYNAMIC_HILBERT_R_NODO_INTERNO_H

#include "DHB_R_Nodo.h"
#include "Entrada/Entrada_Interna.h"

#include <list>

using namespace std;

struct DHB_R_Nodo_Interno: public DHB_R_Nodo
{
    DHB_R_Nodo_Interno();
    list<Entrada_Interna> entradas;
};

#endif