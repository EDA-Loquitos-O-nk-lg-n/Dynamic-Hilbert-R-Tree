#include "../../include/Arbol_R_Hilbert.h"

bool Arbol_R_Hilbert::comparar_entrada(Entrada* a, Entrada *b){
    return a->indice<b->indice;
}