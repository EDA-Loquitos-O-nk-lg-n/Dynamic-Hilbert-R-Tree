#ifndef ARBOL_R_HILBERT_H
#define ARBOL_R_HILBERT_H

#include<algorithm>
#include<unordered_set>
#include<vector>
#include"Punto.h"
#include"Entrada.h"
#include"Entrada_Hoja.h"
#include"Entrada_Interna.h"
#include"Nodo.h"

using namespace std;

class Arbol_R_Hilbert{
public:
    Arbol_R_Hilbert();
    ~Arbol_R_Hilbert();
    void insertar(const vector<Punto> &R);
    void eliminar(Punto R);
    struct Distante{
        Distante(Entrada* E, Punto P, Nodo *N);
        ~Distante();
        Entrada* entrada;
        double distancia;
        Nodo* nodo;
    };
    vector<Distante> buscar(Punto R, int k);
protected:
    Nodo* escoger_hoja(Entrada_Hoja* R, int h);
    Nodo* manejar_desborde(Nodo* N, Entrada* r);
    void ajustar_arbol(unordered_set<Nodo*> &S);
private:
    static bool comparar_entrada(Entrada* a, Entrada *b);
    Nodo* raiz;
};

#endif