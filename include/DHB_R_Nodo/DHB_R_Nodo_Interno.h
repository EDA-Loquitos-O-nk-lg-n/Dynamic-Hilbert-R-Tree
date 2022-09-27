#ifndef DYNAMIC_HILBERT_R_NODO_INTERNO_H
#define DYNAMIC_HILBERT_R_NODO_INTERNO_H

#include "DHB_R_Nodo.h"
#include "../Figura/MBR.h"

#include <vector>

using namespace std;

class DHB_R_Nodo_Interno: public DHB_R_Nodo
{
public:
    DHB_R_Nodo_Interno();

protected:

    struct Entrada{
        MBR Info;
        DHB_R_Nodo* hijo;
        int LHV; // Largest Hilbert Value
    };

private:
    friend class DHB_R_Tree;
    vector<Entrada> entradas;

};

#endif