#include "../../include/Hilbert/Hilbert.h"

int Hilbert::h_indice(const int& _lado, Punto punto){
    Punto rpunto;
    int h{0};
    for(int i = _lado/2; i>0; i/=2){
        rpunto.x = (punto.x & i) > 0;
        rpunto.y = (punto.y & i) > 0;
        h += i*i*((3*rpunto.x) ^ rpunto.y);
        rotar(_lado, punto, rpunto);
    }
    return h;
}

void Hilbert::coordenada(const int& _lado, const int &h, Punto& punto){
    Punto rpunto{0,0};
    for(int s=1, t=h; s<_lado; s*=2, t/=4){
        rpunto.x = 1 & (t/2);
        rpunto.y = 1 & (t ^ rpunto.x);
        rotar(s, punto, rpunto);
        punto.x += s*rpunto.x;
        punto.y += s*rpunto.y;
    }
}

void Hilbert::rotar(const int& _lado, Punto& punto, const Punto& rpunto)
{
    if(rpunto.y == 0){
        if(rpunto.x == 1){
            punto.x = _lado-1 - punto.x;
            punto.y = _lado-1 - punto.y;   
        }

        swap(punto.x, punto.y);
    }
}