#ifndef NODO_H
#define NODO_H

#include<set>
#include"Entrada.h"

using namespace std;

struct Entrada;
struct cmp_Entrada{
    bool operator()(Entrada* a, Entrada* b);
};
struct Nodo{
    bool hoja;
    Nodo* padre;
    multiset<Entrada*, cmp_Entrada> entradas;
};

#endif