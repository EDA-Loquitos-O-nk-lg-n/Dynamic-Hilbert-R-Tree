#include "../../include/DHB_R_Tree/DHB_R_Tree.h"

DHB_R_Tree::DHB_R_Tree(const int& orden): curva(orden){
    raiz = new DHB_R_Nodo_Hoja;
}

void DHB_R_Tree::insercion(const Punto& punto){
    // I1
    DHB_R_Nodo* L = escoger_hoja(punto, curva.h_indice(punto));

    // I2
    DHB_R_Nodo_Hoja *nueva_hoja = nullptr;
    if(dynamic_cast<DHB_R_Nodo_Hoja*>(L)->entradas.size() == M){
        list<Entrada_Hoja>& entradas = dynamic_cast<DHB_R_Nodo_Hoja*>(L)->entradas;
        auto i_entrada = entradas.begin();
        auto i_end = entradas.end();
        while((i_entrada != i_end) && (curva.h_indice(i_entrada->Info) < curva.h_indice(punto))){
            i_entrada++;
        }
        entradas.insert(i_entrada, {punto});
    }
    else{
        nueva_hoja = dynamic_cast<DHB_R_Nodo_Hoja*>(manejar_desborde(L, punto));
    }

    // I3
    list<DHB_R_Nodo*> S;
    S.push_back(L);
    for(auto ent: dynamic_cast<DHB_R_Nodo_Interno*>(L->padre)->entradas){
        if(L != ent.hijo)
            S.push_back(ent.hijo);
    }
    if(nueva_hoja)
        S.push_back(nueva_hoja);

    ajustar_arbol(S);
}

void DHB_R_Tree::eliminacion(const Punto& punto){

}

vector<Punto> DHB_R_Tree::busqueda_knn(const Punto& punto, const int& k){
    
}