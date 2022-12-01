#ifndef ARBOL_R_HILBERT_H
#define ARBOL_R_HILBERT_H

#include<algorithm>
#include<unordered_set>
#include<vector>
#include<deque>
#include<queue>
#include<list>
#include<functional>
#include<cmath>
#include"Punto.h"
#include"Entrada.h"
#include"Nodo.h"
#include"Interfaz.h"

using namespace std;

class Interfaz;

class Arbol_R_Hilbert{
public:
    // Constructor
    Arbol_R_Hilbert();
    // Destrctor
    ~Arbol_R_Hilbert();
    // Busqueda
    void insertar(const vector<Punto> &R, int D=8);
    // Eliminacion
    void eliminar(Punto R);
    // Objeto Knn
    struct Distante{
        // Constructor
        Distante(Entrada* E, Punto P, Nodo *N);
        // Destructror
        ~Distante();
        // Entrada que referencia
        Entrada* entrada;
        // Distancia del punto al MBR
        double distancia;
        // Nodo que referencia
        Nodo* nodo;
    };
    //  Búsqeuda KNN
    vector<Distante> buscar(Punto R, int k);
    // Búqueda exacta
    bool buscar_exacto(const vector<Punto>& Ps);
    // Función para ver indices Hilbert (DEBUG)
    void imprimir_nodo_indice_h(Nodo* n);
    // Función para ver el cumplimiento de MBR (DEBUG)
    bool cumplir_intervalos();
    // Obtener la altura del arbol
    int retornar_altura();
    // Obtener el sobrelapado de un nivel del arbol
    double obtener_sobrelapado(int Nivel);
    // Obtener el sobrelapado total
    double obtener_sobrelapado_total();
protected:
    // Comparar con respecto al atributo de distancia
    friend bool operator<(const Distante &pd1, const Distante &pd2);
    friend bool operator>(const Distante &pd1, const Distante &pd2);
    friend bool operator<=(const Distante &pd1, const Distante &pd2);
    friend bool operator>=(const Distante &pd1, const Distante &pd2);
    // Escager hoja apropiada para la Entrada
    Nodo* escoger_hoja(Entrada* R, int h);
    // Manejor los nodos que sobrapasen la cantidad de entradas
    Nodo* manejar_desborde_exceso(Nodo* N, Entrada* r);
    // Manejor los nodos que tengan defecto  de la cantidad de entradas
    Nodo* manejar_desborde_defecto(Nodo* N, bool &combinado);
    // Evaluar nodos superiores
    bool ajustar_arbol(deque<Nodo*> &S, Nodo* N, Nodo* NN);
private:
    // Liberar memoria dinamica de entradas y nodos recursivamente
    void destruir_recursivo(Nodo* N);
    // COmpoarar el indice Hilbert de dos entradas
    static bool comparar_entrada(Entrada* a, Entrada *b);
    // Raiz del arbol
    Nodo* raiz;
    // Contador de objetos insertados
    int objetos;

    friend class Interfaz;
};

#endif