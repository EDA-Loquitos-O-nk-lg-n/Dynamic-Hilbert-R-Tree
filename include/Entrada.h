#ifndef ENTRADA_H
#define ENTRADA_H

#include "Intervalo.h"
#include "Funciones_Hilbert.h"
#include "Punto.h"
#include "Constante.h"
#include "Nodo.h"
#include<limits>
#include<vector>

struct Entrada{
    Entrada();
    Intervalo intervalos[2];
    int indice; // maximo valor hilbert
    
    // Entrada nodo interno
    Entrada(Nodo* H);
    void actualizar_valores();
    Nodo* hijo;


    // Entrada nodo hoja
    Entrada(const vector<Punto> &P);
    vector<Punto> objeto;


    ~Entrada();
};


#endif