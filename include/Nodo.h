#ifndef NODO_H
#define NODO_H

#include<vector>
#include"../Entrada/Entrada.h"

using namespace std;

struct Nodo{
    bool hoja;
    Nodo* padre;
    vector<Entrada*> entradas;
};

#endif