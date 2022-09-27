#ifndef DYNAMIC_HILBERT_R_NODO_HIJO_H
#define DYNAMIC_HILBERT_R_NODO_HIJO_H

#include "DHB_R_Nodo.h"
#include "../Figura/Punto.h"
#include <vector>
#include <cstddef>

using namespace std;

class DHB_R_Nodo_Hijo: public DHB_R_Nodo
{
public:
    DHB_R_Nodo_Hijo();

protected:

    struct Entrada{
        Punto Info;
        nullptr_t id; // NO UTILIZADO
    };

private:
    friend class DHB_R_Tree;
    vector<Entrada> entradas;

};

#endif