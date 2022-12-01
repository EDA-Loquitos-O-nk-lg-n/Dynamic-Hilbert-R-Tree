#ifndef ENTRADA_H
#define ENTRADA_H

#include "Intervalo.h"
#include "Funciones_Hilbert.h"
#include "Punto.h"
#include "Constante.h"
#include "Nodo.h"
#include<limits>
#include<vector>

// Estrctura que contiene información de las entradas de un nodo
struct Entrada{
    // Constructor
    Entrada();
    // Intervalos que definen la región de minima delimitación
    Intervalo intervalos[2];
    // Máximo valor de indice Hilbert
    int indice; 
    
    // Constructor de una entrada nodo interno
    Entrada(Nodo* H);
    // Actualizar los intervalos e indice mayor hilbert de la entrada
    void actualizar_valores();
    // Puntero hacia un nodo hijo
    Nodo* hijo;

    // Constructor de una entrada nodo hoja
    Entrada(const vector<Punto> &P, int D=8);
    // Tamaño 1: Punto, Tamaño >1: Polígono
    vector<Punto> objeto;

    // Verificar si un punto está dentro de la región de expansión mínima
    bool dentro(int x, int y);

    // Destrcutor 
    ~Entrada();
};


#endif