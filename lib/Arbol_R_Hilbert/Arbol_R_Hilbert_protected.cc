#include "../../include/Arbol_R_Hilbert.h"

Nodo *Arbol_R_Hilbert::escoger_hoja(Entrada *R, int h) {
    // C1
    Nodo* N{raiz};

    // C2
    while(!N->hoja){
        // C3
        std::multiset<Entrada *, cmp_Entrada>::const_iterator i_E = N->entradas.upper_bound(R);
        if(i_E == N->entradas.end()){
            --i_E;
        }
        // C4
        N = i_E.operator*()->hijo;
    }

    return N;
}

Nodo* Arbol_R_Hilbert::manejar_desborde_defecto(Nodo* N, bool &combinado){
    int cantidad_nodos = N->padre->entradas.size();
    // int cantidad_nodos = (N==raiz?1:N->padre->entradas.size());
    int nodos_defecto = 0;
    int entradas_por_nodo;
    int entradas_sobrantes;
    vector<Nodo*> nodos;
    vector<Entrada*>::iterator it_begin, it_end;

    // Obtener todos las entradas de los nodos vecinos
    vector<Entrada*> epsilon;
    for(Entrada* e: N->padre->entradas){
        nodos.push_back(e->hijo);
        epsilon.insert(epsilon.end(), e->hijo->entradas.begin(), e->hijo->entradas.end());
        // Contar cuantos nodos tendrían underflow
        if(e->hijo->entradas.size() == m)
            nodos_defecto++;
    }

    // Si todos están en el limite inferior
    if(nodos_defecto == nodos.size() - 1){
        nodos.pop_back();
        nodos.back()->padre->entradas.erase(
            --nodos.back()->padre->entradas.end()
        );
        cantidad_nodos--;
        combinado = cantidad_nodos < m;
    }

    // Distribucion de entradas a nodo y vecinos
    entradas_por_nodo = epsilon.size() / cantidad_nodos;
    entradas_sobrantes = epsilon.size() % cantidad_nodos;

    it_begin = epsilon.begin();
    // Distribucion
    for (int i = 0; i < nodos.size(); i++){
        it_end = next(it_begin, entradas_por_nodo + (entradas_sobrantes-- > 0));
        nodos[i]->entradas.clear();
        while (it_begin != it_end){
            if((*it_begin)->hijo != nullptr)
                (*it_begin)->hijo->padre = nodos[i];
            nodos[i]->entradas.insert(*it_begin);
            it_begin++;
        }
    }

    // Actualizar mbrs e indice-h de cada nodo
    for(Entrada* ep: nodos.front()->padre->entradas){
        ep->actualizar_valores();
    }

    return nodos.front()->padre;
}

Nodo* Arbol_R_Hilbert::manejar_desborde_exceso(Nodo *N, Entrada *r) {
    // Posible nodo creado apuntando a nulo
    Nodo* NN = nullptr;
    // Cantidad de nodos al nivel al nodo N (1 si es raiz)
    int cantidad_nodos = (N==raiz?1:N->padre->entradas.size());
    // Contador de nodos llenos
    int nodos_llenos = 0;
    // Cantidad de entradas que se distribuiran a cada nodo
    int cantidad_entradas;
    // Entradas sobrantes a repartir
    int residuo_entradas;
    // Nodos vecinoso
    vector<Nodo*> nodos;
    list<Entrada*>::iterator it_begin, it_end;

    // H1
    // Contenedor que almacena todas las entradas de los vecinos al nivel del nodo N
    list<Entrada*> epsilon;
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
    residuo_entradas = epsilon.size() % cantidad_nodos;
    // Inicio del iterator inicial para el primer nodo
    it_begin = epsilon.begin();
    // Iterar por todos los nodos
    for(int i = 0; i<nodos.size(); i++){
        // Iterador final
        bool hay_residuos = residuo_entradas > 0;
        it_end = next(it_begin, cantidad_entradas + hay_residuos);
        residuo_entradas--;
        // Remover todas las entradas del nodo i
        nodos[i]->entradas.clear();
        // Procesar cada entrada del intervalo hasta llegar al interador final  
        while (it_begin != it_end)
        {
            // reasignar padre
            if((*it_begin)->hijo != nullptr)
                (*it_begin)->hijo->padre = nodos[i];
            // Insertar la entrada al nodo i
            nodos[i]->entradas.insert(*it_begin);
            // Siguiente entrada
            it_begin++;
        }
    }
    
    return NN;
}

bool Arbol_R_Hilbert::ajustar_arbol(deque<Nodo*> &S, Nodo* N, Nodo* NN) {
    // Puntero a posible nuevo padre 
    Nodo* PP{nullptr};
    // Booleano que determina que no se ha llegado al nivel de la raiz
    bool no_nivel_raiz {N != raiz};

    // A1
    // Mientras los nodos no estén en el nivel de la raiz
    while(no_nivel_raiz){
        bool hubo_redistribucion = false;
        // Definir como nulo
        PP = nullptr;
        // Nodo padre de N y vecinos
        Nodo* N_p = N->padre;

        // A2
        if( NN != nullptr ){
            // Volvemos NN como una entrada
            Entrada* E_NN = new Entrada{NN};
            // Si el padre no está lleno
            if(N_p->entradas.size() < M){
                // Cambiamos el padre del nodo NN como N_p
                E_NN->hijo->padre = N_p;
                // Insertar la entrada de acuerdo al indice Hilbert
                N_p->entradas.insert(E_NN);
            }
            // Si el padre está lleno
            else{
                PP = manejar_desborde_exceso(N_p, E_NN);
                hubo_redistribucion = true;
            }
        }

        // A3
        deque<Nodo*> P;
        P.push_front(N_p);
        if(PP != nullptr)
            P.push_front(PP);
        for(Nodo* p: P){
            no_nivel_raiz = no_nivel_raiz && p != raiz;
            if(p->padre != nullptr){
                for(Entrada* e: p->padre->entradas){
                    if(hubo_redistribucion || e->hijo == p){
                        e->actualizar_valores();
                    }
                }
            }
        }
        
        // A4
        N = N_p;
        NN = PP;
        S = P;
    }

    return S.size() > 1;
}

bool operator<(const Arbol_R_Hilbert::Distante &pd1, const Arbol_R_Hilbert::Distante &pd2){
    return pd1.distancia < pd2.distancia;
}
bool operator>(const Arbol_R_Hilbert::Distante &pd1, const Arbol_R_Hilbert::Distante &pd2){
    return pd1.distancia>pd2.distancia;
}
bool operator<=(const Arbol_R_Hilbert::Distante &pd1, const Arbol_R_Hilbert::Distante &pd2){
    return pd1.distancia<=pd2.distancia;
}
bool operator>=(const Arbol_R_Hilbert::Distante &pd1, const Arbol_R_Hilbert::Distante &pd2){
    return pd1.distancia>=pd2.distancia;
}