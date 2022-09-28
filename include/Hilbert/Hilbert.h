#ifndef HILBERT_H
#define HILBERT_H

#include "../Figura/Punto.h"
#include <algorithm>
#include <utility>

using namespace std;

class Hilbert
{
public:
    Hilbert(const int &orden);
    int h_indice(const Punto& punto);
    Punto coordenada(const int &h);

protected:
    int h_indice(const int& _lado, Punto punto);
    void coordenada(const int& _lado, const int &h, Punto& punto);

    void rotar(const int& _lado, Punto& punto, const Punto& rpunto);

private:
    int lado;
    int orden;
};

#endif