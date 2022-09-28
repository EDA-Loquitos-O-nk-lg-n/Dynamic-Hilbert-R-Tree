#include "../../include/DHB_R_Tree/DHB_R_Tree.h"

DHB_R_Nodo_Hoja *DHB_R_Tree::escoger_hoja(const Punto &punto, const int &h)
{
    DHB_R_Nodo *N = raiz;

    while (!N->hoja)
    {
        DHB_R_Nodo_Interno *N_i = dynamic_cast<DHB_R_Nodo_Interno *>(N);
        int indice_LHV_minimo_mayor = -1;
        for (int i = 0; i < N_i->entradas.size(); i++)
        {
            if (indice_LHV_minimo_mayor == -1)
            {
                if (N_i->entradas[i].LHV > h)
                    indice_LHV_minimo_mayor = i;
            }
            else if (N_i->entradas[i].LHV > h && N_i->entradas[i].LHV < N_i->entradas[indice_LHV_minimo_mayor].LHV)
            {
                indice_LHV_minimo_mayor = i;
            }
        }

        N = N_i->entradas[indice_LHV_minimo_mayor].hijo;
    }

    return dynamic_cast<DHB_R_Nodo_Hoja *>(N);
}

DHB_R_Nodo* DHB_R_Tree::manejar_desborde(DHB_R_Nodo*& N, const Punto& punto){
    if(N->hoja){
        DHB_R_Nodo_Hoja* N_h = dynamic_cast<DHB_R_Nodo_Hoja*>(N);
        deque<Entrada_Hoja> entradas(N_h->entradas.begin(),  N_h->entradas.end());
    }
    else{

    }
}