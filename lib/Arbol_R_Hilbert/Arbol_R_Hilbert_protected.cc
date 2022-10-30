#include "../../include/Arbol_R_Hilbert.h"

Nodo *Arbol_R_Hilbert::escoger_hoja(Entrada *R, int h) {
    // C1
    Nodo* N{raiz};

    // C2
    while(!N->hoja){
        // C3
        int indice_mayor{};
        const Entrada* E{N->entradas[indice_mayor]};
        while(indice_mayor < N->entradas.size()-1 && E->indice <= h){
            indice_mayor++;
            E = N->entradas[indice_mayor];
        }
        // C4
        N = E->hijo;
    }

    return N;
}

Nodo* Arbol_R_Hilbert::manejar_desborde(Nodo *N, Entrada *r) {
    // Posible nodo creado apuntando a nulo
    Nodo* NN = nullptr;
    // Cantidad de nodos al nivel al nodo N (1 si es raiz)
    int cantidad_nodos = (N==raiz?1:N->padre->entradas.size());
    // Contador de nodos llenos
    int nodos_llenos = 0;
    // Cantidad de entradas que se distribuiran a cada nodo
    int cantidad_entradas;
    // Nodos vecinoso
    vector<Nodo*> nodos;
    vector<Entrada*>::iterator it_begin, it_end;

    // H1
    // Contenedor que almacena todas las entradas de los vecinos al nivel del nodo N
    vector<Entrada*> epsilon;
    // Si el nodo N no es la raiz
    if(N!=raiz){
        // Iterar por todos los hijos del padre de N
        for(Entrada* e: N->padre->entradas){
            // Agregamos el nodo al contenedor de nodos vecinos
            nodos.push_back(e->hijo);
            // Insertamos las entradas de un nodo al contenedor epsilon 
            epsilon.insert(epsilon.end(), e->hijo->entradas.begin(), e->hijo->entradas.end());
            // Si el nodo iterado está lleno, aumentos el contador de llenos
            if(e->hijo->entradas.size() >= M)
                nodos_llenos++;
        }
    }
    // Si  el nodo N es raiz
    else{
        // INsertamos solo la raiz al contenedor de nodos
        nodos.push_back(N);
        // insertamos todas las entradas de la raiz a epsilon
        epsilon.insert(epsilon.end(), N->entradas.begin(), N->entradas.end());
        // Si la raiz está llena, aumentamos el contador
        if(N->entradas.size() == M)
            nodos_llenos++;
    }

    // H2
    // Ingresamos la entrada a insertar en epsilon de manera ordenada de acuerdo al indice hilbert
    epsilon.insert(lower_bound(epsilon.begin(),epsilon.end(),r,comparar_entrada), r);

    // H3
    // Si existen nodos que no están llenos, no hacer nuevas modificaciones
    
    // H4
    // Si todos los nodos están llenos
    if(nodos_llenos >= cantidad_nodos){
        // Creamos un nodo con la condicional de si es nodo interno u hoja
        NN = new Nodo{N->hoja};
        // Agregamos NN al contenedor de nodos
        nodos.push_back(NN);
        // Incrementamos la cantidad de nodos
        cantidad_nodos++;
    }

    // Distribuir entre todos los nodos
    // Calcular cuantas entradas tendrá cada nodo
    cantidad_entradas = epsilon.size() / cantidad_nodos;
    // Agregar la cantidad de entradas a los vecinos, en orden
    for(int i = 0; i<nodos.size()-1; i++){
        // Limpiar entradas del nodo i
        nodos[i]->entradas.clear();
        it_begin = next(epsilon.begin(), i*cantidad_entradas);
        it_end = next(epsilon.begin(), (i+1)*cantidad_entradas);
        while (it_begin != it_end)
        {
            // reasignar padre
            if((*it_begin)->hijo != nullptr){
                (*it_begin)->hijo->padre = nodos[i];
            }
            // Insertar la entrada al nodo i
            nodos[i]->entradas.push_back(*it_begin);
            // Siguiente entrada
            it_begin++;
        }
    }
    // Asignar las entradas que sobran al último nodo
    it_begin = next(epsilon.begin(),(nodos.size()-1)*cantidad_entradas);
    it_end = epsilon.end();
    // Limpiar entradas del ultimo nodo
    nodos[nodos.size()-1]->entradas.clear();
    while (it_begin != it_end)
    {
        // reasignar padre
        if((*it_begin)->hijo != nullptr){
            (*it_begin)->hijo->padre = nodos[nodos.size()-1];
        }
        // Insertar la entrada al nodo i
        nodos[nodos.size()-1]->entradas.push_back(*it_begin);
        // Siguiente entrada
        it_begin++;
    }
    
    return NN;
}

bool Arbol_R_Hilbert::ajustar_arbol(deque<Nodo *> &S) {
    // Puntero a posible nuevo padre 
    Nodo* PP;
    bool no_nivel_raiz = S.back() != raiz;

    // A1
    // Mientras los nodos no estén en el nivel de la raizs
    while(no_nivel_raiz){
        // Definir como nulo
        PP = nullptr;
        // Nodo padre de N y vecinos
        Nodo* N_p = (*next(S.begin(), S.size() - 1))->padre;

        // A2
        // Si el nodo N fue partido, habrán más nodos en S que entradas en el padre N_p
        if(N_p->entradas.size() < S.size()){
            // NN es el nuevo nodo partido, unordered_set::insert manda los nuevos elementos al comienzo
            Nodo* NN = S.front();
            // Volvemos NN como una entrada
            Entrada* E_NN = new Entrada{NN};
            // Si el padre no está lleno
            if(N_p->entradas.size() < M){
                // Cambiamos el padre del nodo NN como N_p
                E_NN->hijo->padre = N_p;
                // Insertar la entrada de acuerdo al indice Hilbert
                N_p->entradas.insert(lower_bound(N_p->entradas.begin(), N_p->entradas.end(), E_NN, comparar_entrada), E_NN);
            }
            // Si el padre está lleno
            else{
                PP = manejar_desborde(N_p, E_NN);
            }
        }

        // A3
        unordered_set<Nodo*> P_uset;
        deque<Nodo*> P;
        int P_uset_capacidad = P_uset.size();
        
        for(Nodo* n: S){
            if(n->padre == raiz)
                no_nivel_raiz = false;
            P_uset.insert(n->padre);
            if(P_uset_capacidad < P_uset.size()){
                P.push_front(n->padre);
                P_uset_capacidad++;
            }
        }

        // if(*next(P.begin(), P.size() - 1) != raiz){
        if(S.back() != raiz){
            for(Nodo* p: P){
                // if(p->padre == nullptr)
                //     continue;
                // for(Entrada* pe: p->padre->entradas){
                for(Entrada* pe: p->entradas){
                    // if(pe->hijo == p){
                        pe->actualizar_valores();
                        // break;
                    // }
                }
            }
        }
        
        // A4
        if(PP != nullptr){
            no_nivel_raiz = (PP==raiz?false:no_nivel_raiz);
            P.push_front(PP);
        }
        S = P;
    }

    return S.size() > 1;
}