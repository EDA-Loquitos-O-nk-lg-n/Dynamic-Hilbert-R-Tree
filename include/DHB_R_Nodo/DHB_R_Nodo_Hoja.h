#ifndef DYNAMIC_HILBERT_R_NODO_HOJA_H
#define DYNAMIC_HILBERT_R_NODO_HOJA_H

#include "DHB_R_Nodo.h"
#include "Entrada/Entrada_Hoja.h"
#include <deque>

using namespace std;

class DHB_R_Nodo_Hoja: public DHB_R_Nodo
{
public:
    DHB_R_Nodo_Hoja();

private:
    friend class DHB_R_Tree;
    deque<Entrada_Hoja> entradas;

};

#endif