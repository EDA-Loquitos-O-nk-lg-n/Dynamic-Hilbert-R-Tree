#ifndef ENTRADA_INTERNA_H
#define ENTRADA_INTERNA_H

#include "../DHB_R_Nodo.h"
#include "../../Figura/MBR.h"
#include "Entrada.h"

struct Entrada_Interna: public Entrada{
    MBR Info;
    DHB_R_Nodo* hijo;
    int LHV; // Largest Hilbert Value
};

#endif