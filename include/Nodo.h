#ifndef NODO_H
#define NODO_H

#include<set>
#include"Entrada.h"

using namespace std;

struct Entrada;

// Objeto Función´para comparar punteros hacia entradas
struct cmp_Entrada{
    bool operator()(Entrada* a, Entrada* b);
};

// Estructura de un nodo
struct Nodo{
    // Determina si es hijo
    bool hoja;
    // Define al padre (nullptr si es la raiz)
    Nodo* padre;

    // Almacenador de entradas
    multiset<Entrada*, cmp_Entrada> entradas;
};

#endif