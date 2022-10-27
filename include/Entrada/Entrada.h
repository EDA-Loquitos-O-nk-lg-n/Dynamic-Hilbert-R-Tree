#ifndef ENTRADA_H
#define ENTRADA_H

#include "../Intervalo.h"

struct Entrada{
    Entrada();
    Intervalo intervalos[2];
    int indice; // maximo valor hilbert
    virtual ~Entrada();
};


#endif