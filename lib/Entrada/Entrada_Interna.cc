#include "../../include/Entrada/Entrada_Interna.h"

Entrada_Interna::Entrada_Interna() = default;

Entrada_Interna::Entrada_Interna(Nodo* H): hijo(H){
    actualizar_valores();
}

Entrada_Interna::~Entrada_Interna() = default;

void Entrada_Interna::actualizar_valores(){
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