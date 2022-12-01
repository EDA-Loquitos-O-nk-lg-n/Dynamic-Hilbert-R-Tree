#include"../include/Arbol_R_Hilbert.h"
#include"../include/Interfaz.h"
#include<random>
#include<fstream>
#include<chrono>

using namespace std;
using namespace std::chrono;

int x = N, y = N;
random_device rd;

vector<Punto> generar_poligono(){
    int l_lado = (x*(rd()%64 + 21))/10000.f;
    int n_lados = rd()%3 + 3;

    Punto trasladar{rd()%(N-100) + 50, rd()%(N-100) + 50};

    vector<Punto> P;
    if(n_lados == 3){
        P = {{0,0}, {l_lado, 0}, {static_cast<int>(round(l_lado/2.f)), static_cast<int>(round(l_lado*sqrt(3)/2.f))}};
    }
    else if(n_lados == 4){
        P = {{0,0},{0,l_lado},{l_lado, l_lado},{l_lado, 0}};
    }
    else{
        P = {{0,0},{0,l_lado},{l_lado, l_lado},{l_lado, 0}};
    }

    for(int i = 0; i<P.size(); i++){
        P[i].x += trasladar.x;
        P[i].y += trasladar.y;
    }

    return P;
}

void sobrelapamiento(){
    for(int D = 128; D<=128; D*=2){
        ofstream of("Solapamiento_"+to_string(D)+".csv", ofstream::out);
        of<<"Total,Hoja\n";
        // for(int t = 0; t<1; t++){
        for(int t = 0; t<100; t++){
            Arbol_R_Hilbert* a = new Arbol_R_Hilbert;

            for(int b = 0; b<5000; b++){
                a->insertar(generar_poligono(), D);
            }

            of<<fixed<<a->obtener_sobrelapado_total()<<',';

            int H = a->retornar_altura();
            for(int h =H; h>=1; h--){
                of<<fixed<<a->obtener_sobrelapado(h);
                if(h >1 )
                    of<<',';
            }


            of<<'\n';

            cout<<D<<": "<<t+1<<'\n';

            delete a;
        }
        of.close();
    }
}

static void T_I(){
    ofstream of("T_I.csv", ofstream::out);
    for(int i = 0; i<500; i++){
        of<<i+1;
        if(i == 499)
            of<<'\n';
        else
            of<<',';
    }
        
    for(int t = 0; t<100; t++){
        Arbol_R_Hilbert* a = new Arbol_R_Hilbert;
        for(int b = 0; b<500; b++){
            auto start = high_resolution_clock::now();
            for(int i = 0; i<10; i++){
                a->insertar(generar_poligono());
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start);

            if(b != 499)
                of<<duration.count()<<',';
            else
                of<<duration.count()<<'\n';
        }
        cout<<t+1<<'\n';
        delete a;
    }
    of.close();
}

static void T_B(){
    int n_figuras_por_batch = 1000;
    // int n_figuras_por_batch = 10;
    ofstream of("T_B.csv", ofstream::out);
    vector<Punto> polis[n_figuras_por_batch];
    for (int i = 1; i <= 5; i++)
    {
        of<<i;
        if(i != 5)
            of<<',';
    }
    of<<'\n';

    for(int t = 0; t<100; t++){
        Arbol_R_Hilbert* a = new Arbol_R_Hilbert;
        for(int b = 0; b<5; b++){
            for(int n_p = 0; n_p<n_figuras_por_batch; n_p++){
                polis[n_p] = generar_poligono();
                a->insertar(polis[n_p]);
            }
            auto start = high_resolution_clock::now();
            for(int n_p = 0; n_p<n_figuras_por_batch; n_p++){
                bool hallado = a->buscar_exacto(polis[n_p]);
                
                if(!hallado){
                    cout<<"No hallado";
                    delete a;
                    return;
                }
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start);
            if(b != 4)
                of<<duration.count()<<',';
            else
                of<<duration.count()<<'\n';
        }
        // cout<<a->cumplir_intervalos()<<endl;
        // Interfaz i;
        // i.setArbol(a);
        // i.ejecutar();
        delete a;
        cout<<t<<'\n';
    }
    of<<'\n';
    of.close();    
}

static void T_D(){
    ofstream of("T_D.csv", ofstream::out);

    for(int i = 0; i<5; i++){
        of<<i+1;
        if(i == 4)
            of<<'\n';
        else
            of<<',';
    }

    for(int t = 0; t<100; t++){
        Arbol_R_Hilbert* a = new Arbol_R_Hilbert;
        

        for(int p =0; p<5000; p++){
            a->insertar(generar_poligono());
        }

        for(int b = 0; b<5; b++){
            auto start = high_resolution_clock::now();
            for(int p = 0; p<1000; p++){
                Punto ubicacion{rd()%N, rd()%N};
                a->eliminar(ubicacion);
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start);
            if(b != 4)
                of<<duration.count()<<',';
            else
                of<<duration.count()<<'\n';
        }
        cout<<t+1<<'\n';

        // nodo_entradas(a);
            
        
        delete a;
    }
    of.close();
}

static void T_K(){
    ofstream of("T_K.csv", ofstream::out);
    for(int i = 1; i<=5; i++){
        of<<"T"<<i<<"K=1"<<',';
        of<<"T"<<i<<"K=5"<<',';
        of<<"T"<<i<<"K=20";
        if(i != 5)
            of<<',';
    }
    of<<'\n';

    int ks[3]{1,5,20};

    for(int t = 0; t<100; t++){
        Arbol_R_Hilbert* a = new Arbol_R_Hilbert;
        for(int b =0; b<5; b++){
            for(int p = 0; p<1000; p++){
                a->insertar(generar_poligono());
            }
            for(int k = 0; k<3; k++){
                auto start = high_resolution_clock::now();
                Punto ubicacion{rd()%N, rd()%N};
                a->buscar(ubicacion, ks[k]);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                if(k == 2 && b==4)
                    of<<duration.count()<<'\n';
                else
                    of<<duration.count()<<',';

            }


            // nodo_entradas(a);
            
        }
        cout<<t+1<<endl;
        delete a;
    }

    of.close();
}

int main(){
    T_D();
    T_B();
}