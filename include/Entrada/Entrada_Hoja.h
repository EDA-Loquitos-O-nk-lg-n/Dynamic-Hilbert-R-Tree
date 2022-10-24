#ifndef ENTRADA_HOJA_H
#define ENTRADA_HOJA_H

#include "Entrada.h"
#include "Funciones_Hilbert.h"
#include "Punto.h"
#include "Constante.h"
#include<limits>
#include<vector>

using namespace std;

struct Entrada_Hoja: public Entrada{
    Entrada_Hoja();
    Entrada_Hoja(const vector<Punto> &P);
    ~Entrada_Hoja();
    vector<Punto> objeto;
};

#endif