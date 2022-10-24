#ifndef FUNCIONES_HILBERT_H
#define FUNCIONES_HILBERT_H

namespace Funciones_Hilbert{
    int xy2d(int n, int x, int y);
    void d2xy(int n, int d, int *x, int *y);
    void rot(int n, int *x, int *y, int rx, int ry);
};

#endif