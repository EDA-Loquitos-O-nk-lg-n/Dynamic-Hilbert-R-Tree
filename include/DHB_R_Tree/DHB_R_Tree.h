#ifndef DYNAMIC_HILBERT_R_TREE_H
#define DYNAMIC_HILBERT_R_TREE_H

#include<vector>
#include"../Figura/Punto.h"
#include "../DHB_R_Nodo/DHB_R_Nodo.h"

using namespace std;

class DHB_R_Tree
{
public:
    DHB_R_Tree();
    void insercion(const Punto& punto);
    void eliminacion(const Punto& punto);
    vector<Punto> busqueda_knn(const Punto& punto, const int& k);

    friend class Interfaz;

private:
    DHB_R_Nodo *raiz;
};

#endif