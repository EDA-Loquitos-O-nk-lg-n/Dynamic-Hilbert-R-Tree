#ifndef ENTRADA_INTERNA_H
#define ENTRADA_INTERNA_H

#include "../Nodo.h"
#include "Entrada.h"
#include<limits>

struct Entrada_Interna: public Entrada{
    Entrada_Interna();
    Entrada_Interna(Nodo* H);
    ~Entrada_Interna();
    Nodo* hijo;
    void actualizar_valores();
};

#endif