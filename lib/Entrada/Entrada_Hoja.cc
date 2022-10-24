#include "../../include/Entrada/Entrada_Hoja.h"

Entrada_Hoja::Entrada_Hoja() = default;

Entrada_Hoja::Entrada_Hoja(const vector<Punto> &R)
: objeto(R){
    indice = Funciones_Hilbert::xy2d(N, R[0].x, R[0].y);
    intervalos[0] = {numeric_limits<int>::max(), numeric_limits<int>::min()};
    intervalos[1] = {numeric_limits<int>::max(), numeric_limits<int>::min()};
    for(Punto i : R){
        indice = max(indice, Funciones_Hilbert::xy2d(N, i.x, i.y));
        intervalos[0].menor = min(intervalos[0].menor, i.x);
        intervalos[1].menor = min(intervalos[1].menor, i.y);
        intervalos[0].mayor = max(intervalos[0].mayor, i.x);
        intervalos[1].mayor = max(intervalos[1].mayor, i.y);
    }
}

Entrada_Hoja::~Entrada_Hoja() = default;