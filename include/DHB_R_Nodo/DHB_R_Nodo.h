#ifndef DYNAMIC_HILBERT_R_NODO_H
#define DYNAMIC_HILBERT_R_NODO_H

#include "../Constante/Constante.h"

class DHB_R_Nodo
{
public:
    DHB_R_Nodo();
    DHB_R_Nodo(const bool& _hoja);
    virtual ~DHB_R_Nodo();
protected:
    DHB_R_Nodo* padre;
    bool hoja;
private:
    friend class DHB_R_Tree;
};

#endif