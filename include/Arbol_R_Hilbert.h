#ifndef ARBOL_R_HILBERT_H
#define ARBOL_R_HILBERT_H

#include<algorithm>
#include<unordered_set>
#include<vector>
#include<deque>
#include<queue>
#include<list>
#include<functional>
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
    bool buscar_exacto(const vector<Punto>& Ps);
    void imprimir_nodo_indice_h(Nodo* n);
    bool cumplir_intervalos();
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
    void destruir_recursivo(Nodo* N);
    static bool comparar_entrada(Entrada* a, Entrada *b);
    Nodo* raiz;
    int objetos;

    friend class Interfaz;
};

#endif