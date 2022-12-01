#ifndef FUNCIONES_HILBERT_H
#define FUNCIONES_HILBERT_H

namespace Funciones_Hilbert{
    // Convertidor de una coordenada al indice Hilbert
    int xy2d(int n, int x, int y);
    // Convertir Indice HIlbert a coordenada
    void d2xy(int n, int d, int *x, int *y);
    // Rotar la curva de hilbert
    void rot(int n, int *x, int *y, int rx, int ry);
};

#endif