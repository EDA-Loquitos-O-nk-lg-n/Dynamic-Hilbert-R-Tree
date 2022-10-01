#include "../../include/DHB_R_Tree/DHB_R_Tree.h"

DHB_R_Tree::DHB_R_Tree(const int& orden): curva(orden){
    raiz = new DHB_R_Nodo_Hoja;
}

void DHB_R_Tree::insercion(const Punto& punto){
    DHB_R_Nodo_Hoja* L = escoger_hoja(punto, curva.h_indice(punto));

    if(L->entradas.size() == M){
        
    }
    else{
        
    }
}

void DHB_R_Tree::eliminacion(const Punto& punto){

}

vector<Punto> DHB_R_Tree::busqueda_knn(const Punto& punto, const int& k){
    
}