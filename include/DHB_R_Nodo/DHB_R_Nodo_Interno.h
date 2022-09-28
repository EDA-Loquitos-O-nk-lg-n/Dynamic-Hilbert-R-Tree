#ifndef DYNAMIC_HILBERT_R_NODO_INTERNO_H
#define DYNAMIC_HILBERT_R_NODO_INTERNO_H

#include "DHB_R_Nodo.h"
#include "Entrada/Entrada_Interna.h"

#include <deque>

using namespace std;

class DHB_R_Nodo_Interno: public DHB_R_Nodo
{
public:
    DHB_R_Nodo_Interno();

private:
    friend class DHB_R_Tree;
    deque<Entrada_Interna> entradas;
};

#endif