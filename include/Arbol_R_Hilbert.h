#ifndef ARBOL_R_HILBERT_H
#define ARBOL_R_HILBERT_H

#include<algorithm>
#include<unordered_set>
#include<vector>
#include<deque>
#include<queue>
#include<cmath>
#include"Punto.h"
#include"Entrada.h"
#include"Nodo.h"
#include"Interfaz.h"

using namespace std;

class Interfaz;

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
    void imprimir_nodo_indice_h(Nodo* n);
protected:
    friend bool operator<(const Distante &pd1, const Distante &pd2);
    friend bool operator>(const Distante &pd1, const Distante &pd2);
    friend bool operator<=(const Distante &pd1, const Distante &pd2);
    friend bool operator>=(const Distante &pd1, const Distante &pd2);
    Nodo* escoger_hoja(Entrada* R, int h);
    Nodo* manejar_desborde_exceso(Nodo* N, Entrada* r);
    Nodo* manejar_desborde_defecto(Nodo* N, bool &combinado);
    bool ajustar_arbol(deque<Nodo*> &S, Nodo* N, Nodo* NN);
private:
    static bool comparar_entrada(Entrada* a, Entrada *b);
    Nodo* raiz;

    friend class Interfaz;
};

#endif