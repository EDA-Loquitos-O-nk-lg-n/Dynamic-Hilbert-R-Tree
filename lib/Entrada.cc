#include "../include/Entrada.h"

Entrada::Entrada() = default;
Entrada::~Entrada() = default;

Entrada::Entrada(Nodo* H): hijo(H){
    actualizar_valores();
}

bool Entrada::dentro(int x, int y){
    bool en_x = intervalos[0].menor <= x && x <= intervalos[0].mayor;
    bool en_y = intervalos[1].menor <= y && y <= intervalos[1].mayor;
    return en_x && en_y;
}

Entrada::Entrada(const vector<Punto> &R)
: objeto(R), hijo(nullptr){
    indice = Funciones_Hilbert::xy2d(N, R[0].x / D, R[0].y / D);
    intervalos[0] = {numeric_limits<int>::max(), numeric_limits<int>::min()};
    intervalos[1] = {numeric_limits<int>::max(), numeric_limits<int>::min()};
    for(Punto i : R){
        indice = max(indice, Funciones_Hilbert::xy2d(N, i.x / D, i.y / D));
        intervalos[0].menor = min(intervalos[0].menor, i.x);
        intervalos[1].menor = min(intervalos[1].menor, i.y);
        intervalos[0].mayor = max(intervalos[0].mayor, i.x);
        intervalos[1].mayor = max(intervalos[1].mayor, i.y);
    }
}

void Entrada::actualizar_valores(){
    indice = numeric_limits<int>::min();
    intervalos[0] = {numeric_limits<int>::max(), numeric_limits<int>::min()};
    intervalos[1] = {numeric_limits<int>::max(), numeric_limits<int>::min()};
    for(Entrada* e: hijo->entradas){
        indice = max(e->indice, indice);
        intervalos[0].menor = min(intervalos[0].menor, e->intervalos[0].menor);
        intervalos[0].mayor = max(intervalos[0].mayor, e->intervalos[0].mayor);
        intervalos[1].menor = min(intervalos[1].menor, e->intervalos[1].menor);;
        intervalos[1].mayor = max(intervalos[1].mayor, e->intervalos[1].mayor);
    }
}