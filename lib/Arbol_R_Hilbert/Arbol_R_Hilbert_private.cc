#include "../../include/Arbol_R_Hilbert.h"

bool Arbol_R_Hilbert::comparar_entrada(Entrada* a, Entrada *b){
    return a->indice<b->indice;
}

void Arbol_R_Hilbert::destruir_recursivo(Nodo* N){
    if(!N->hoja){
        for(Entrada* e: N->entradas){
            destruir_recursivo(e->hijo);
            delete e;
        }
    }
    else{
        for(Entrada* e: N->entradas){
            delete e;
        }
    }
    delete N;
}