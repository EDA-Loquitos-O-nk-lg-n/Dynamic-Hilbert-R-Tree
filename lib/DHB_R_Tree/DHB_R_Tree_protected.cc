#include "../../include/DHB_R_Tree/DHB_R_Tree.h"

DHB_R_Nodo_Hoja *DHB_R_Tree::escoger_hoja(const Punto &punto, const int &h)
{
    DHB_R_Nodo *N = raiz;

    while (!N->hoja)
    {
        DHB_R_Nodo_Interno *N_i = dynamic_cast<DHB_R_Nodo_Interno *>(N);
        bool existe = 0;
        list<Entrada_Interna>::iterator iterador_LHV_minimo_mayor;
        for(auto i = N_i->entradas.begin(); i!= N_i->entradas.end(); i++){
            if(!existe){
                if(i->LHV > h){
                    existe = 1;
                    iterador_LHV_minimo_mayor = i;
                }
            }
            else if(i->LHV > h && i->LHV < iterador_LHV_minimo_mayor->LHV){
                iterador_LHV_minimo_mayor = i;
            }
        }

        N = iterador_LHV_minimo_mayor->hijo;
    }

    return dynamic_cast<DHB_R_Nodo_Hoja *>(N);
}

DHB_R_Nodo* DHB_R_Tree::manejar_desborde(DHB_R_Nodo*& N, const Punto& punto){

    DHB_R_Nodo* NN = nullptr;

    if(N->hoja){

        // H1
        list<Entrada_Hoja> entradas;
        DHB_R_Nodo_Interno* padre_N = dynamic_cast<DHB_R_Nodo_Interno*>(N->padre);

        for (auto i = padre_N->entradas.begin(); i != padre_N->entradas.end(); i++)
        {
            DHB_R_Nodo_Hoja* hijo_hoja = dynamic_cast<DHB_R_Nodo_Hoja*>(i->hijo);
            for(auto j = hijo_hoja->entradas.begin(); j != hijo_hoja->entradas.end(); j++){
                entradas.push_back(*j);
            }
            hijo_hoja->entradas.clear();
        }
        
        // H2
        auto i_entrada = entradas.begin();
        while((i_entrada != entradas.end()) && (curva.h_indice(i_entrada->Info) < curva.h_indice(punto))){
            i_entrada++;
        }
        entradas.insert(i_entrada, {punto});

        // H3
        if(padre_N->entradas.size()*M > entradas.size()){
            int subentrada_size{entradas.size() / padre_N->entradas.size()};
            int resto{entradas.size() % padre_N->entradas.size()};

            bool hay_resto = resto != 0;
            int iteraciones = padre_N->entradas.size();
            iteraciones -= hay_resto;

            auto iterador_entradas = entradas.begin();
            auto iterador_entradas_padre = padre_N->entradas.begin();
            
            for(int i = 0; i<iteraciones; i++, iterador_entradas_padre++){
                dynamic_cast<DHB_R_Nodo_Hoja*>(iterador_entradas_padre->hijo)->entradas = list<Entrada_Hoja>(iterador_entradas, next(iterador_entradas, subentrada_size));
                iterador_entradas = next(iterador_entradas, subentrada_size);
            }

            if(hay_resto){
                dynamic_cast<DHB_R_Nodo_Hoja*>(iterador_entradas_padre->hijo)->entradas = list<Entrada_Hoja>(iterador_entradas, entradas.end());
            }
        }
        // H4
        else{
            int subentrada_size{entradas.size() / padre_N->entradas.size()};
            int resto{entradas.size() % padre_N->entradas.size()};

            NN = new DHB_R_Nodo_Hoja;
            
            auto iterador_entradas = entradas.begin();
            auto iterador_entradas_padre = padre_N->entradas.begin();
            for(int i = 0; i<padre_N->entradas.size(); i++, iterador_entradas_padre++){
                dynamic_cast<DHB_R_Nodo_Hoja*>(iterador_entradas_padre->hijo)->entradas = list<Entrada_Hoja>(iterador_entradas, next(iterador_entradas, subentrada_size));
                iterador_entradas = next(iterador_entradas, subentrada_size);
            }            

           dynamic_cast<DHB_R_Nodo_Hoja*>(NN)->entradas = list<Entrada_Hoja>(iterador_entradas, entradas.end());
        }
    }
    else{
        
    }
    return NN;
}