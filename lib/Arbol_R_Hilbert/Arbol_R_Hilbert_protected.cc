#include "../../include/Arbol_R_Hilbert.h"

Nodo *Arbol_R_Hilbert::escoger_hoja(Entrada *R, int h) {
    // C1
    Nodo* N{raiz};

    // C2
    while(!N->hoja){
        // C3
        int indice_mayor{};
        Entrada* E{raiz->entradas[indice_mayor]};
        while(indice_mayor < raiz->entradas.size()-1 && E->indice <= h){
            indice_mayor++;
            E = raiz->entradas[indice_mayor];
        }
        // C4
        N = E->hijo;
    }

    return N;
}

Nodo* Arbol_R_Hilbert::manejar_desborde(Nodo *N, Entrada *r) {
    Nodo* NN = nullptr;
    int cantidad_nodos = (N==raiz?1:N->padre->entradas.size());
    int nodos_llenos = 0;
    vector<Nodo*> nodos;

    // H1
    vector<Entrada*> epsilon;
    if(N!=raiz){
        for(Entrada* e: N->padre->entradas){
            nodos.push_back(e->hijo);
            epsilon.insert(epsilon.end(), e->hijo->entradas.begin(), e->hijo->entradas.end());
            if(e->hijo->entradas.size() == M)
                nodos_llenos++;
        }
    }
    else{
        nodos.push_back(N);
        epsilon.insert(epsilon.end(), N->entradas.begin(), N->entradas.end());
        if(N->entradas.size() == M)
            nodos_llenos++;
    }

    // H2
    epsilon.insert(lower_bound(epsilon.begin(),epsilon.end(),r,comparar_entrada), r);

    // H3
    if(nodos_llenos < cantidad_nodos){
        int cantidad_entradas = epsilon.size() / cantidad_nodos;
        for(int i = 0; i<nodos.size()-1; i++){
            nodos[i]->entradas = vector<Entrada*>(
                next(epsilon.begin(), i*cantidad_entradas),
                next(epsilon.begin(), (i+1)*cantidad_entradas)
            );
        }
        nodos[nodos.size()-1]->entradas = vector<Entrada*>(
                next(epsilon.begin(),(nodos.size()-1)*cantidad_entradas),
                epsilon.end()
        );
    }

    // H4
    else{
        NN = new Nodo{N->hoja};
        nodos.push_back(NN);
        cantidad_nodos++;
        int cantidad_entradas = epsilon.size() / cantidad_nodos;
        for(int i = 0; i<nodos.size()-1; i++){
            nodos[i]->entradas = vector<Entrada*>(
                next(epsilon.begin(), i*cantidad_entradas),
                next(epsilon.begin(), (i+1)*cantidad_entradas)
            );
        }
        nodos[nodos.size()-1]->entradas = vector<Entrada*>(
            next(epsilon.begin(),(nodos.size()-1)*cantidad_entradas),
            epsilon.end()
        );
    }


    return NN;
}

void Arbol_R_Hilbert::ajustar_arbol(unordered_set<Nodo *> &S) {
    Nodo* PP;

    // A1
    while(*next(S.begin(), S.size() - 1) != raiz){
        PP = nullptr;
        Nodo* N_p = (*next(S.begin(), S.size() - 1))->padre;

        // A2
        if(N_p->entradas.size() < S.size()){
            Nodo* NN = *S.begin();
            Entrada* E_NN = new Entrada{NN};
            if(N_p->entradas.size() < M){
                N_p->entradas.insert(lower_bound(N_p->entradas.begin(), N_p->entradas.end(), E_NN, comparar_entrada), E_NN);
                E_NN->hijo->padre = N_p;
            }
            else{
                PP = manejar_desborde(N_p, E_NN);
            }
        }

        // A3
        unordered_set<Nodo*> P;
        
        for(Nodo* n: S)
            P.insert(n->padre);

        if(*next(S.begin(), S.size() - 1) != raiz){
            for(Nodo* p: P){
                for(Entrada* pe: p->padre->entradas){
                    if(pe->hijo == p){
                        pe->actualizar_valores();
                        break;
                    }
                }
            }
        }
        
        // A4
        if(PP != nullptr)
            P.insert(PP);
        S = P;
    }
}