#include "../include/Funciones_Hilbert.h"

int Funciones_Hilbert::xy2d(int n, int x, int y){
    int rx, ry, s, d=0;
    for (s=n/2; s>0; s/=2) {
        // Aplicar mascara
        rx = (x & s) > 0;
        // Aplicar mascara
        ry = (y & s) > 0;
        d += s * s * ((3 * rx) ^ ry);
        // rotar para la siguiente cuadricula
        rot(n, &x, &y, rx, ry);
    }
    return d;
}

void Funciones_Hilbert::rot(int n, int *x, int *y, int rx, int ry){
    if (ry == 0) {
        if (rx == 1) {
            // Pasar a la siguiente cuadricula
            *x = n-1 - *x;
            *y = n-1 - *y;
        }

        //Cambiar el valor de x e y
        int t  = *x;
        *x = *y;
        *y = t;
    }
}