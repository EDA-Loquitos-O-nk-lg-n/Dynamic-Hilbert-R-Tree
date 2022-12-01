#include "../include/Entrada.h"

Entrada::Entrada() = default;
Entrada::~Entrada() = default;

Entrada::Entrada(Nodo* H): hijo(H){
    // Definir los intervalos y el maximo valor de hilbert para un nodo interno
    actualizar_valores();
}

bool cmp_Entrada::operator()(Entrada* a, Entrada* b){
    // Compara los indices de HIlbert
    return a->indice < b->indice;
}

bool Entrada::dentro(int x, int y){
    // Determinar si el valor x se encuentra en el intervalo en el eje x
    bool en_x = intervalos[0].menor <= x && x <= intervalos[0].mayor;
    // Determinar si el valor y se encuentra en el intervalo en el eje y
    bool en_y = intervalos[1].menor <= y && y <= intervalos[1].mayor;

    // Retorna si ambos se cumplen
    return en_x && en_y;
}

Entrada::Entrada(const vector<Punto> &R, int D)
: objeto(R), hijo(nullptr){
    // EMplea el conversor de coordenada a indice de Hilbert
    indice = Funciones_Hilbert::xy2d(N / D, R[0].x / D, R[0].y / D);

    // Valor inicial en x para la compoaración
    intervalos[0] = {numeric_limits<int>::max(), numeric_limits<int>::min()};
    // Valor inicial en y para la compoaración
    intervalos[1] = {numeric_limits<int>::max(), numeric_limits<int>::min()};

    // Iterar por los puntos del poligono/punto para obtener los valores apropiadas
    for(Punto i : R){
        indice = max(indice, Funciones_Hilbert::xy2d(N/D, i.x / D, i.y / D));
        intervalos[0].menor = min(intervalos[0].menor, i.x);
        intervalos[1].menor = min(intervalos[1].menor, i.y);
        intervalos[0].mayor = max(intervalos[0].mayor, i.x);
        intervalos[1].mayor = max(intervalos[1].mayor, i.y);
    }
}

void Entrada::actualizar_valores(){
    // Valor inicial de indice hIlbert para la comparación
    indice = numeric_limits<int>::min();
    
    // Valor inicial de intervalo x para la comparación
    intervalos[0] = {numeric_limits<int>::max(), numeric_limits<int>::min()};
    // Valor inicial de intervalo y para la comparación
    intervalos[1] = {numeric_limits<int>::max(), numeric_limits<int>::min()};

    // Iterar por las entradas para obtener los valores apropiadaos
    for(Entrada* e: hijo->entradas){
        indice = max(e->indice, indice);
        intervalos[0].menor = min(intervalos[0].menor, e->intervalos[0].menor);
        intervalos[0].mayor = max(intervalos[0].mayor, e->intervalos[0].mayor);
        intervalos[1].menor = min(intervalos[1].menor, e->intervalos[1].menor);;
        intervalos[1].mayor = max(intervalos[1].mayor, e->intervalos[1].mayor);
    }
}