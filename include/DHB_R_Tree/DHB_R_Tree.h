#ifndef DYNAMIC_HILBERT_R_TREE_H
#define DYNAMIC_HILBERT_R_TREE_H

#include<vector>
#include<deque>
#include"../Figura/Punto.h"
#include "../DHB_R_Nodo/DHB_R_Nodo.h"
#include "../DHB_R_Nodo/DHB_R_Nodo_Hoja.h"
#include "../DHB_R_Nodo/DHB_R_Nodo_Interno.h"
#include "../Hilbert/Hilbert.h"
#include<limits>

using namespace std;

class DHB_R_Tree
{
public:
    DHB_R_Tree(const int& orden);
    void insercion(const Punto& punto);
    void eliminacion(const Punto& punto);
    vector<Punto> busqueda_knn(const Punto& punto, const int& k);

    friend class Interfaz;

protected:
    DHB_R_Nodo_Hoja* escoger_hoja(const Punto& punto, const int& h);
    DHB_R_Nodo* manejar_desborde(DHB_R_Nodo*& N, const Punto& punto);

private:
    DHB_R_Nodo *raiz;
    Hilbert curva;
};

#endif