#include "../../include/Arbol_R_Hilbert.h"

Arbol_R_Hilbert::Distante::~Distante(){}

Arbol_R_Hilbert::Distante::Distante(Entrada* E, Punto P, Nodo *N): entrada(E), nodo(N){
    if(!N->hoja){
        if(P.x >= E->intervalos[0].menor && P.x <= E->intervalos[0].mayor && P.y >= E->intervalos[1].menor && P.y <= E->intervalos[1].mayor)
            distancia = 0;
        else if(P.x >= E->intervalos[0].menor && P.x <= E->intervalos[0].mayor)
            distancia = min(abs(P.y-E->intervalos[1].menor), abs(P.y-E->intervalos[1].mayor));
        else if(P.y >= E->intervalos[1].menor && P.y <= E->intervalos[1].mayor)
            distancia = min(abs(P.x-E->intervalos[0].menor), abs(P.x-E->intervalos[0].mayor));
        else{
            distancia = min(
                sqrt(pow(P.y-E->intervalos[1].menor,2)+pow(P.x-E->intervalos[0].menor,2)), 
                min(
                    sqrt(pow(P.y-E->intervalos[1].mayor,2)+pow(P.x-E->intervalos[0].menor,2)), 
                    min(
                        sqrt(pow(P.y-E->intervalos[1].menor,2)+pow(P.x-E->intervalos[0].mayor,2)), 
                        sqrt(pow(P.y-E->intervalos[1].mayor,2)+pow(P.x-E->intervalos[0].mayor,2))))
                );
        }
    }
    else{
        if(E->objeto.size() == 1){
            distancia = sqrt(pow(P.x-E->objeto[0].x,2)+pow(P.y-E->objeto[0].y,2));
        }
        else{
            double pm_x=0, pm_y=0;
            for(auto p: E->objeto){
                pm_x+=p.x;
                pm_y+=p.y;
            }
            pm_x/=E->objeto.size();
            pm_y/=E->objeto.size();
            distancia = sqrt(pow(P.x-pm_x,2)+pow(P.y-pm_y,2));
        }
    }
}

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
    Entrada* r = new Entrada{R};
    Nodo* L = escoger_hoja(r, r->indice);

    // I2
    if(L->entradas.size() < M){
        L->entradas.insert(lower_bound(L->entradas.begin(),L->entradas.end(),r,comparar_entrada), r);
    }
    else{
        partido = manejar_desborde(L, r);
    }

    
    // I3
    unordered_set<Nodo*> S;
    if(L != raiz){
        for(Entrada* entrada : L->padre->entradas){
            S.insert(entrada->hijo);
        }
    }
    else{
        S.insert(L);
    }
    if(partido != nullptr)
        S.insert(partido);

    ajustar_arbol(S);

    // I4
    if(*next(S.begin(), S.size() - 1) == raiz && S.size() > 1){
        raiz = new Nodo{false, nullptr};
        raiz->entradas.push_back(new Entrada{*next(S.begin(), S.size() - 1)});
        raiz->entradas.push_back(new Entrada{*next(S.begin(), S.size() - 2)});
    }

}