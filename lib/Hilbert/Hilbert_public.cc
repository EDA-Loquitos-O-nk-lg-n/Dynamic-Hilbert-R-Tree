#include "../../include/Hilbert/Hilbert.h"

Hilbert::Hilbert(const int &_orden) : orden(_orden), lado(2<<(_orden-1)) {}

int Hilbert::h_indice(const Punto &punto)
{
    return h_indice(lado, punto);
}

Punto Hilbert::coordenada(const int &h)
{
    Punto coord;

    coordenada(lado, h, coord);

    return coord;
}