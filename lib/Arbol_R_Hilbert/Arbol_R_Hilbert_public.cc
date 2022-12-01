#include "../../include/Arbol_R_Hilbert.h"

int Arbol_R_Hilbert::retornar_altura(){
    int altura = 0;
    // Ubicarse en la raiz
    Nodo* N = raiz;
    // Mientras no se llegue a un nodo hoja
    while(!N->hoja){
        // Bajar por las ramas del arbol
        N = N->entradas.begin().operator*()->hijo;
        // Incrementar la altura
        altura++;
    }
    // Retornar el valor de la altura
    return altura;
}

double Arbol_R_Hilbert::obtener_sobrelapado_total(){
    // 
    double area_total=0, area_sobrelapada=0;

    set<int> seg_set_x, seg_set_y;

    queue<Nodo*> cola_nodos;
    cola_nodos.push(raiz);
    while(!cola_nodos.empty()){
        if(!cola_nodos.front()->hoja){
            for(Entrada* e: cola_nodos.front()->entradas){
                seg_set_x.insert(e->intervalos[0].menor);
                seg_set_x.insert(e->intervalos[0].mayor);
                seg_set_y.insert(e->intervalos[1].menor);
                seg_set_y.insert(e->intervalos[1].mayor);
                cola_nodos.push(e->hijo);
            }
        }
        cola_nodos.pop();
    }


    //////
    vector<int> segmento_x(seg_set_x.begin(), seg_set_x.end()), segmento_y(seg_set_y.begin(), seg_set_y.end());
    vector<vector<int>> matriz(seg_set_x.size() - 1, vector<int>(seg_set_y.size() - 1, 0));

    cola_nodos.push(raiz);
    for(int ix = 1; ix<segmento_x.size(); ix++){
        for(int iy = 1; iy<segmento_y.size(); iy++){
            
            while(!cola_nodos.empty()){
                if(!cola_nodos.front()->hoja){
                    for(Entrada* e: cola_nodos.front()->entradas){
                        if(e->dentro(segmento_x[ix-1], segmento_y[iy-1]) && e->dentro(segmento_x[ix], segmento_y[iy])){
                            matriz[ix-1][iy-1]++;
                        }
                    cola_nodos.push(e->hijo);
                    }
                }
                cola_nodos.pop();
            }
        }
    }
    //////

    for(int i = 0; i<segmento_x.size()-1; i++){
        for(int j = 0; j<segmento_y.size()-1; j++){
            if(matriz[i][j] > 1){
                area_sobrelapada += (segmento_x[i+1]-segmento_x[i])*(segmento_y[j+1]-segmento_y[j]);
            }
            area_total += (segmento_x[i+1]-segmento_x[i])*(segmento_y[j+1]-segmento_y[j]);
        }
    }

    return area_sobrelapada/area_total;
}
double Arbol_R_Hilbert::obtener_sobrelapado(int Nivel){

    double area_total=0, area_sobrelapada=0;

    priority_queue<pair<int, Nodo*>, vector<pair<int, Nodo*>>, greater<pair<int,Nodo*>>> desciende;
    desciende.push({0,raiz});
    while(desciende.top().first + 1 < Nivel){
        Nodo* N = desciende.top().second;
        int nivel_N = desciende.top().first;
        desciende.pop();
        for(Entrada* e: N->entradas){
            desciende.push({nivel_N+1, e->hijo});
        }
    }

    vector<Nodo*> nodos;
    while(!desciende.empty()){
        // cout<<desciende.top().first<<endl;
        nodos.push_back(desciende.top().second);
        desciende.pop();
    }

    // cout<<"NIVEL: "<<Nivel<<endl;
    // cout<<"NUMERO DE NODOS: "<<nodos.size()<<endl;

    set<int> seg_set_x, seg_set_y;
    for(Nodo* n: nodos){
        for(Entrada* e: n->entradas){
            seg_set_x.insert(e->intervalos[0].menor);
            seg_set_x.insert(e->intervalos[0].mayor);
            seg_set_y.insert(e->intervalos[1].menor);
            seg_set_y.insert(e->intervalos[1].mayor);
        }
    }
    vector<int> segmento_x(seg_set_x.begin(), seg_set_x.end()), segmento_y(seg_set_y.begin(), seg_set_y.end());
    vector<vector<int>> matriz(seg_set_x.size() - 1, vector<int>(seg_set_y.size() - 1, 0));

    for(int ix = 1; ix<segmento_x.size(); ix++){
        for(int iy = 1; iy<segmento_y.size(); iy++){
            for(Nodo* n :nodos){
                for(Entrada* e: n->entradas){
                    if(e->dentro(segmento_x[ix-1], segmento_y[iy-1]) && e->dentro(segmento_x[ix], segmento_y[iy])){
                        matriz[ix-1][iy-1]++;
                    }
                }
            }
        }
    }

    for(int i = 0; i<segmento_x.size()-1; i++){
        for(int j = 0; j<segmento_y.size()-1; j++){
            if(matriz[i][j] > 1){
                area_sobrelapada += (segmento_x[i+1]-segmento_x[i])*(segmento_y[j+1]-segmento_y[j]);
            }
            area_total += (segmento_x[i+1]-segmento_x[i])*(segmento_y[j+1]-segmento_y[j]);
        }
    }

    return area_sobrelapada/area_total;

}

bool Arbol_R_Hilbert::cumplir_intervalos(){
    if(raiz->hoja) return true;
    Nodo* N = raiz;
    function<bool(Entrada*)> verificar = [&verificar](Entrada* e){
        for(Entrada* ie: e->hijo->entradas){
            if(
                !e->dentro(ie->intervalos[0].menor, ie->intervalos[1].menor) ||
                !e->dentro(ie->intervalos[0].mayor, ie->intervalos[1].mayor)
            ){
                return false;
            }
        }
        for(Entrada* ie: e->hijo->entradas){
            
        }
        return true;
    };
}

bool Arbol_R_Hilbert::buscar_exacto(const vector<Punto>& Ps){
    Entrada verificadora{Ps};

    queue<Nodo*> cola;
    cola.push(raiz);
    while(!cola.empty()){
        if(cola.front()->hoja){
            for(Entrada* e: cola.front()->entradas){
                if(Ps.size() != e->objeto.size()){
                    continue;
                }

                bool iguales = true;
                for (int i_punto = 0; i_punto < Ps.size(); i_punto++){
                    if(Ps[i_punto].x != e->objeto[i_punto].x || Ps[i_punto].y != e->objeto[i_punto].y){
                        iguales = false;
                        break;
                    }
                }
                if(iguales){
                    return true;
                }                
            }
        }
        else{
            for(Entrada* e: cola.front()->entradas){
                if(!e->dentro(verificadora.intervalos[0].menor, verificadora.intervalos[1].menor) 
                    || !e->dentro(verificadora.intervalos[0].mayor, verificadora.intervalos[1].mayor)){
                        continue;
                    }
                cola.push(e->hijo);
            }
        }
        cola.pop();
    }
    return false;
}

Arbol_R_Hilbert::Distante::~Distante() = default;

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

Arbol_R_Hilbert::Arbol_R_Hilbert(): raiz(new Nodo{true, nullptr}), objetos(0) {}

Arbol_R_Hilbert::~Arbol_R_Hilbert() {
    destruir_recursivo(raiz);
}

vector<Arbol_R_Hilbert::Distante> Arbol_R_Hilbert::buscar(Punto R, int k) {
    priority_queue<Arbol_R_Hilbert::Distante, deque<Arbol_R_Hilbert::Distante>, greater<Arbol_R_Hilbert::Distante>> knn_lista;
    for(Entrada* rent: raiz->entradas){
        knn_lista.push({rent, R, raiz});
    }

    vector<Arbol_R_Hilbert::Distante> resultados;
    while(resultados.size() < k && !knn_lista.empty()){
        if(knn_lista.top().nodo->hoja){
            resultados.push_back(knn_lista.top());
            knn_lista.pop();
        }
        else{
            Entrada* ET = knn_lista.top().entrada;
            knn_lista.pop();
            for(Entrada* ent: ET->hijo->entradas){
                knn_lista.push({ent, R, ET->hijo});
            }
        }
    }
    return resultados;
}

void Arbol_R_Hilbert::eliminar(Punto R) {
    if(raiz->entradas.size() == 0){
        return;
    }
    // D1
    Distante cerca = buscar(R, 1)[0];
    Entrada* E = cerca.entrada;
    Nodo* L = cerca.nodo;

    // D2
    multiset<Entrada *>::iterator it_borrado = find(L->entradas.begin(), L->entradas.end(), E);
    delete *it_borrado;
    L->entradas.erase(it_borrado);

    // D3
    bool defecto_superior = false;
    if(L->entradas.size() < m && L->padre != nullptr){
        defecto_superior =  L->entradas.size() < m;
        L = manejar_desborde_defecto(L, defecto_superior);
    }

    // D4
    while(defecto_superior && L->padre != nullptr){
        L = manejar_desborde_defecto(L, defecto_superior);
    }
    while(L->padre != nullptr){
        for(Entrada* e: L->padre->entradas){
            if(e->hijo == L){
                e->actualizar_valores();
                break;
            }
        }
        L = L->padre;
    }

    // si la raiz tiene un solo hijo, volver el hijo la raiz
    if(raiz->entradas.size() == 1 && !raiz->hoja){
        Nodo* del_raiz = raiz;
        raiz = raiz->entradas.begin().operator*()->hijo;
        raiz->padre = nullptr;
        delete del_raiz->entradas.begin().operator*();
        delete del_raiz;
    }
}

void Arbol_R_Hilbert::insertar(const vector<Punto> &R, int D) {
    Nodo* NL = nullptr;
    bool hubo_redistribucion = false;
    // I1
    // Creamos una entrada utilizando el objeto R ingresado
    Entrada* r = new Entrada{R, D};
    Nodo* L = escoger_hoja(r, r->indice);

    // I2
    // Si el nodo no esta lleno
    if(L->entradas.size() < M){
        // Insertar el nuevo objeto en orden de acuerdo al indice Hilbert
        L->entradas.insert(r);
        // L->entradas.insert(lower_bound(L->entradas.begin(),L->entradas.end(),r,comparar_entrada), r);
    }
    // Si está lleno
    else{
        NL = manejar_desborde_exceso(L, r);
        hubo_redistribucion = true;
    }
    
    // I3
    deque<Nodo*> S;
    if(L == raiz)
        S.push_back(L);
    else {
        for(Entrada* e: L->padre->entradas){ // Ver si reorganizamos por entrada interna
            if(hubo_redistribucion || e->hijo == L ){
                e->actualizar_valores();
            }
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
        // raiz->entradas.insert(lower_bound(raiz->entradas.begin(),raiz->entradas.end(), RC1 ,comparar_entrada), RC1);
        raiz->entradas.insert(RC1);
        // raiz->entradas.insert(lower_bound(raiz->entradas.begin(),raiz->entradas.end(), RC2 ,comparar_entrada), RC2);
        raiz->entradas.insert(RC2);
    }

    // imprimir_nodo_indice_h(raiz);
    // std::cout<<endl;
    objetos++;

}
void Arbol_R_Hilbert::imprimir_nodo_indice_h(Nodo* n){
    if(n == raiz)
    cout<<"ARBOL:"<<endl;
    if(!n->hoja){
        std::cout<<'/';
        for(Entrada* e: n->entradas){
            // std::cout<<e->indice<<' ';
            printf("x E [%d, %d], y E [%d, %d]\n", 
                e->intervalos[0].menor, e->intervalos[0].mayor,
                e->intervalos[1].menor, e->intervalos[1].mayor
            );
            imprimir_nodo_indice_h(e->hijo);
        }
        // std::cout<<'/';
    }
    else{
        for(Entrada* e: n->entradas){
            printf("x E [%d, %d], y E [%d, %d] ////// \n", 
                e->intervalos[0].menor, e->intervalos[0].mayor,
                e->intervalos[1].menor, e->intervalos[1].mayor
            );
            
        // std::cout<<'/';
            // imprimir_nodo_indice_h(e->hijo);
        // std::cout<<'/';
        }
    }
}