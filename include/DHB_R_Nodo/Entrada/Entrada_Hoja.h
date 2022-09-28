#ifndef ENTRADA_HOJA_H
#define ENTRADA_HOJA_H

#include "../DHB_R_Nodo.h"
#include "../../Figura/Punto.h"
#include "Entrada.h"
#include <cstddef>

struct Entrada_Hoja: public Entrada{
    Punto Info;
    nullptr_t id; // NO UTILIZADO
};

#endif