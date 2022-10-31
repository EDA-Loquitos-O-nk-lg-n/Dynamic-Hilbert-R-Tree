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
    Nodo* NL = nullptr;

    // I1
    // Creamos una entrada utilizando el objeto R ingresado
    Entrada* r = new Entrada{R};
    Nodo* L = escoger_hoja(r, r->indice);

    // I2
    // Si el nodo no esta lleno
    if(L->entradas.size() < M){
        // Insertar el nuevo objeto en orden de acuerdo al indice Hilbert
        L->entradas.insert(lower_bound(L->entradas.begin(),L->entradas.end(),r,comparar_entrada), r);
    }
    // Si está lleno
    else{
        NL = manejar_desborde(L, r);
    }
    
    // I3
    deque<Nodo*> S;
    if(L == raiz)
        S.push_back(L);
    else {
        for(Entrada* e: L->padre->entradas){ // Ver si reorganizamos por entrada interna
            // if(e->hijo == L){
                e->actualizar_valores();
            // }
            S.push_back(e->hijo);
        }
    }
    // Agregar nueva hoja en caso sea hoja
    if(NL != nullptr)
        S.push_front(NL);
    
    bool RS = ajustar_arbol(S, L, NL);

    // I4 
    if(RS){
        raiz = new Nodo{false, nullptr};
        S[0]->padre = raiz;
        S[1]->padre = raiz;
        Entrada *RC1 = new Entrada{S[0]}, *RC2 = new Entrada{S[1]};
        raiz->entradas.insert(lower_bound(raiz->entradas.begin(),raiz->entradas.end(), RC1 ,comparar_entrada), RC1);
        raiz->entradas.insert(lower_bound(raiz->entradas.begin(),raiz->entradas.end(), RC2 ,comparar_entrada), RC2);
    }

    imprimir_nodo_indice_h(raiz);
    std::cout<<endl;

}
void Arbol_R_Hilbert::imprimir_nodo_indice_h(Nodo* n){
    if(n->hoja){
        std::cout<<'/';
        for(Entrada* e: n->entradas){
            std::cout<<e->indice<<' ';
        }
        std::cout<<'/';
    }
    else{
        for(Entrada* e: n->entradas){
        std::cout<<'/';
            imprimir_nodo_indice_h(e->hijo);
        std::cout<<'/';
        }
    }
}