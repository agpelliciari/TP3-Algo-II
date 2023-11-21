#include "Inventario_de_Armas.hpp"
#include "Arma.hpp"
#include <iostream>
#include <string>
using namespace std;

Inventario_de_Armas::Inventario_de_Armas(){
    this->ahorro_municion=false;
    this->arma_actual=ARMA_DEFAULT;
}

void Inventario_de_Armas::consulta(){
    if (armas_rapidas.vacio()){
        cout << "No hay mas armas! Solo te queda defenderte con tus propios puños."<<endl;
    }
    else{
        Arma arma_rapida;
        arma_rapida=armas_rapidas.primero();
        cout << "Deseas equipar el " << arma_rapida <<"? (s/n)"<<endl;
        std::string respuesta;
        getline (cin,respuesta);
        if (respuesta=="s" || respuesta=="S")
            cambiar_arma();
    } 
}

void Inventario_de_Armas::cambiar_arma(){
    Arma guardada=arma_actual;
    arma_actual=armas_rapidas.baja();
    if (!(guardada==ARMA_DEFAULT))  //Aca lo que chequeo es q no este guardando los puños en el inventario.
        armas_rapidas.alta(guardada);
}

void Inventario_de_Armas::alta(){
    std::string nombre; 
    size_t potencia;

    cout <<"Que arma deseas guardar?"<<endl;
    getline(cin,nombre);
    cin.ignore();
    cout <<"Tu conocimiento de armas te permite estimar su pontencia..."<<endl;
    cin>>potencia;  // ojo, todavia no hay validacion de la potencia como size_t.
    Arma nueva_arma(nombre,potencia);
    armas_rapidas.alta(nueva_arma);
    cout << "Has recogido la: " << nueva_arma <<endl;

    if (ahorro_municion){
        armas_rapidas.heapsort();  
        //Si tengo el ahorro de municion activado, el nuevo alta rompe el vector ordenado.
        //Asique lo vuelvo a ordenar de menor a mayor.
    }  
}

void Inventario_de_Armas::baja(){
    if (armas_rapidas.vacio()){
        cout <<"No quedan mas armas que descartar!!"<<endl;
    }
    else{
        Arma arma_descartada=armas_rapidas.baja();
        cout <<"Has descartado el:"<<arma_descartada;
        if (ahorro_municion){
            armas_rapidas.heapsort();
        }
    }
}
void Inventario_de_Armas::activar_modo_ahorro(){
    if (!armas_rapidas.vacio()){
        if (!ahorro_municion){
            ahorro_municion=true;
            armas_rapidas.heapsort(); //aca reordeno de menor a mayor, para q ahora seleccione el peor arma primero.
            cout <<"Ahorro de municion activado, equiparas las armas menos potentes primero."<<endl;
        }
        else
            cout << "El ahorro de municion ya esta activado.";
    }
    else
        cout <<"No hay armas que gestionar!!";
}
void Inventario_de_Armas::desactivar_modo_ahorro(){
    if (!armas_rapidas.vacio()){
        if (ahorro_municion){
            ahorro_municion=false;
            for (size_t i = (armas_rapidas.tamanio() / 2) - 1; i != SIZE_MAX; i--){
                armas_rapidas.rearmar_heap(armas_rapidas.tamanio(),i);
            }
            cout<<"Ahorro de municion desactivado, hora de la artilleria pesada."<<endl;
        }
        else
            cout<<"El modo ahorro no esta activo!."<<endl;
    }
    else{
        cout <<"No hay armas que gestionar!!";
    }
}