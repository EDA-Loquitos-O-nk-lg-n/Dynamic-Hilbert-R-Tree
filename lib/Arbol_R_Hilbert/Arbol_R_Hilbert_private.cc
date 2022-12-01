#include "../../include/Arbol_R_Hilbert.h"


bool Arbol_R_Hilbert::comparar_entrada(Entrada* a, Entrada *b){
    // Emplea el atributo indice (HIlbert)
    return a->indice<b->indice;
}

void Arbol_R_Hilbert::destruir_recursivo(Nodo* N){
    // Si es hoja
    if(!N->hoja){
        // Itera por cada entrada
        for(Entrada* e: N->entradas){
            // llamar a la función con nodo hijo de la entrada
            destruir_recursivo(e->hijo);
            // Destruir entrada
            delete e;
        }
    }
    else{
        for(Entrada* e: N->entradas){
            // Destruir entrada
            delete e;
        }
    }
    // Destruir nodo
    delete N;
}