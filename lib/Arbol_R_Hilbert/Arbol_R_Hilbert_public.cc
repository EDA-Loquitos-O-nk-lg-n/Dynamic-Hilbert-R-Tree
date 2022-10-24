#include "../../include/Arbol_R_Hilbert.h"

Arbol_R_Hilbert::Arbol_R_Hilbert(): raiz(new Nodo{true, nullptr}) {}

Arbol_R_Hilbert::~Arbol_R_Hilbert() {
    delete raiz;
}

vector<Arbol_R_Hilbert::Distante> Arbol_R_Hilbert::buscar(Punto R, int k) {
    return vector<Distante>();
}

void Arbol_R_Hilbert::eliminar(Punto R) {
    // D1
    Distante cerca = buscar(R, 1)[0];
    Entrada* E = cerca.entrada;
    Nodo* L = cerca.nodo;

    // D2
    for(int i = 0; i<L->entradas.size(); i++){
        if(L->entradas[i] == E){
            delete *next(L->entradas.begin(), i);
            L->entradas.erase(next(L->entradas.begin(), i));
            break;
        }
    }

    // D3
    if(L->entradas.size() < m){
        
    }


    // D4

}

void Arbol_R_Hilbert::insertar(const vector<Punto> &R) {
    Nodo* partido = nullptr;

    // I1
    Entrada_Hoja* r = new Entrada_Hoja{R};
    Nodo* L = escoger_hoja(r, r->indice);

    // I2
    if(L->entradas.size() < M){
        L->entradas.insert(lower_bound(L->entradas.begin(),L->entradas.end(),r,comparar_entrada), r);
        L->entradas.push_back(r);
    }
    else{
        partido = manejar_desborde(L, r);
    }

    
    // I3
    unordered_set<Nodo*> S;
    if(L != raiz){
        for(Entrada* entrada : L->padre->entradas){
            S.insert(dynamic_cast<Entrada_Interna*>(entrada)->hijo);
        }
    }
    else{
        S.insert(L);
    }
    if(partido != nullptr)
        S.insert(partido);

    ajustar_arbol(S);

    // I4
    if(*S.begin() == raiz && S.size() > 1){
        raiz = new Nodo{false, nullptr};
        raiz->entradas.push_back(new Entrada_Interna{*S.begin()});
        raiz->entradas.push_back(new Entrada_Interna{*next(S.begin())});
    }

}