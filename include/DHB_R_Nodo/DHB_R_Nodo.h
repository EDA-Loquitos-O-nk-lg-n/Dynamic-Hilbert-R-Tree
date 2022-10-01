#ifndef DYNAMIC_HILBERT_R_NODO_H
#define DYNAMIC_HILBERT_R_NODO_H

#include "../Constante/Constante.h"

struct DHB_R_Nodo
{
    DHB_R_Nodo();
    DHB_R_Nodo(const bool& _hoja);
    virtual ~DHB_R_Nodo();
    DHB_R_Nodo* padre;
    bool hoja;
};

#endif