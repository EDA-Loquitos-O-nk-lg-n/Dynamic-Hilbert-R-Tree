#include "../include/Hilbert/Hilbert.h"

#include<iostream>
int main(){

    int n= 2, lad = 2<<(n-1);
    Hilbert h(n);
    for(int i = 0; i<lad; i++){
        for (int j = 0; j < lad; j++)
        {
            cout<<h.h_indice({j, i})<<endl;
        }
        
    }

}