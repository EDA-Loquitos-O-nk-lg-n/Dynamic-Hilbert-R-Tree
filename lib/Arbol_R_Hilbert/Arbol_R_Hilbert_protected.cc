#include "../../include/Arbol_R_Hilbert.h"

Nodo *Arbol_R_Hilbert::escoger_hoja(Entrada_Hoja *R, int h) {
    // C1
    Nodo* N{raiz};

    // C2
    while(!N){
        // C3
        int indice_mayor{};
        Entrada_Interna* E{dynamic_cast<Entrada_Interna*>(raiz->entradas[indice_mayor])};
        while(indice_mayor < raiz->entradas.size()-1 && E->indice <= h){
            indice_mayor++;
            E = dynamic_cast<Entrada_Interna*>(raiz->entradas[indice_mayor]);
        }
        // C4
        N = E->hijo;
    }

    return N;
}

Nodo* Arbol_R_Hilbert::manejar_desborde(Nodo *N, Entrada *r) {
    Nodo* NN = nullptr;
    int cantidad_nodos = N->padre->entradas.size();
    int nodos_llenos = 0;
    vector<Nodo*> nodos;

    // H1
    vector<Entrada*> epsilon;
    for(Entrada* e: N->padre->entradas){
        Entrada_Interna* eh = dynamic_cast<Entrada_Interna*>(e);
        nodos.push_back(eh->hijo);
        epsilon.insert(epsilon.end(), eh->hijo->entradas.begin(), eh->hijo->entradas.end());
        if(eh->hijo->entradas.size() == M)
            nodos_llenos++;
    }

    // H2
    epsilon.push_back(r);

    // H3
    if(nodos_llenos < cantidad_nodos){
        int cantidad_entradas = epsilon.size() / cantidad_nodos;
        for(int i = 0; i<nodos.size()-1; i++){
            nodos[i]->entradas = vector<Entrada*>(
                next(epsilon.begin(), i*cantidad_entradas),
                next(epsilon.begin(), i*cantidad_entradas)
            );
        }
        nodos[nodos.size()-1]->entradas = vector<Entrada*>(
                next(epsilon.begin(),(epsilon.size()-1)*cantidad_entradas),
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
                    next(epsilon.begin(), i*cantidad_entradas)
            );
        }
        nodos[nodos.size()-1]->entradas = vector<Entrada*>(
                next(epsilon.begin(),(epsilon.size()-1)*cantidad_entradas),
                epsilon.end()
        );
    }


    return NN;
}

void Arbol_R_Hilbert::ajustar_arbol(unordered_set<Nodo *> &S) {
    Nodo* PP;

    // A1
    while(*S.begin() != raiz){
        PP = nullptr;
        Nodo* N_p = (*S.begin())->padre;

        // A2
        if(N_p->entradas.size() < S.size()){
            Nodo* NN = *prev(S.end());
            Entrada_Interna* E_NN = new Entrada_Interna{NN};
            if(N_p->entradas.size() < M){
                N_p->entradas.insert(lower_bound(N_p->entradas.begin(), N_p->entradas.end(), E_NN, comparar_entrada), E_NN);
            }
            else{
                PP = manejar_desborde(N_p, E_NN);
            }
        }

        // A3
        unordered_set<Nodo*> P;
        
        for(Nodo* n: S)
            P.insert(n->padre);

        if((*P.begin()) != raiz){
            for(Nodo* p: P){
                for(Entrada* pe: p->padre->entradas){
                    Entrada_Interna* pei = dynamic_cast<Entrada_Interna*>(pe);
                    if(pei->hijo == p){
                        pei->actualizar_valores();
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