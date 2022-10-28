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
    // Posible nodo creado apuntando a nulo
    Nodo* NN = nullptr;
    // Cantidad de nodos al nivel al nodo N (1 si es raiz)
    int cantidad_nodos = (N==raiz?1:N->padre->entradas.size());
    // Contador de nodos llenos
    int nodos_llenos = 0;
    // Nodos vecinoso
    vector<Nodo*> nodos;

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
            if(e->hijo->entradas.size() == M)
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
    // Si existen nodos que no están llenos
    if(nodos_llenos < cantidad_nodos){
        // Calcular cuantas entradas tendrá cada nodo
        int cantidad_entradas = epsilon.size() / cantidad_nodos;
        vector<Entrada*>::iterator it_begin, it_end;
        // Agregar la cantidad de entradas a los vecinos, en orden
        for(int i = 0; i<nodos.size()-1; i++){
            // Limpiar entradas del nodo i
            nodos[i]->entradas.clear();
            it_begin = next(epsilon.begin(), i*cantidad_entradas);
            it_end = next(epsilon.begin(), (i+1)*cantidad_entradas);
            while (it_begin != it_end)
            {
                // Actualizar el puntero contenedor al nodo al que iróan
                (*it_begin)->contenedor = nodos[i];
                // Insertar la entrada al nodo i
                nodos[i]->entradas.push_back(*it_begin);
                // Siguiente entrada
                it_begin++;
            }
        }

        // Asignar las entradas que sobran al último nodo
        it_begin = next(epsilon.begin(),(nodos.size()-1)*cantidad_entradas);
        it_end = epsilon.end();
        nodos[nodos.size()-1]->entradas.clear();
        while (it_begin != it_end)
        {
            // Actualizar el puntero contenedor al nodo al que iróan
            (*it_begin)->contenedor = nodos[nodos.size()-1];
            // Insertar la entrada al nodo i
            nodos[nodos.size()-1]->entradas.push_back(*it_begin);
            // Siguiente entrada
            it_begin++;
        }

    }

    // H4
    // Si todos los nodos están llenos
    else{
        // Creamos un nodo con la condicional de si es nodo interno u hoja
        NN = new Nodo{N->hoja};
        // Agregamos NN al contenedor de nodos
        nodos.push_back(NN);
        // Incrementamos la cantidad de nodos
        cantidad_nodos++;
        // Calculamos cuantas entradas le toca a cada nodo
        int cantidad_entradas = epsilon.size() / cantidad_nodos;
        vector<Entrada*>::iterator it_begin, it_end;

        // Agregar la cantidad de entradas a los vecinos, en orden
        for(int i = 0; i<nodos.size()-1; i++){
            // Limpiar entradas del nodo i
            nodos[i]->entradas.clear();
            it_begin = next(epsilon.begin(), i*cantidad_entradas);
            it_end = next(epsilon.begin(), (i+1)*cantidad_entradas);
            while (it_begin != it_end)
            {
                // Actualizar el puntero contenedor al nodo al que iróan
                (*it_begin)->contenedor = nodos[i];
                // Insertar la entrada al nodo i
                nodos[i]->entradas.push_back(*it_begin);
                // Siguiente entrada
                it_begin++;
            }
        }

        // Asignar las entradas que sobran al último nodo
        it_begin = next(epsilon.begin(),(nodos.size()-1)*cantidad_entradas);
        it_end = epsilon.end();
        nodos[nodos.size()-1]->entradas.clear();
        while (it_begin != it_end)
        {
            // Actualizar el puntero contenedor al nodo al que iróan
            (*it_begin)->contenedor = nodos[nodos.size()-1];
            // Insertar la entrada al nodo i
            nodos[nodos.size()-1]->entradas.push_back(*it_begin);
            // Siguiente entrada
            it_begin++;
        }
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