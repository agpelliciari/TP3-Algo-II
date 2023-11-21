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
        if (respuesta=="s")
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
    cout <<"Tu conocimiento de armas te permite estimar su pontencia..."<<endl;
    cin.clear();
    cin>>potencia;  // ojo, todavia no hay validacion de la potencia como size_t.
    Arma nueva_arma(nombre,potencia);
    cout << "Has recogido la " << nueva_arma <<endl;
}

void Inventario_de_Armas::baja(){
    if (armas_rapidas.vacio()){
        cout <<"No quedan mas armas que descartar!!"<<endl;
    }
    else{
        Arma arma_descartada=armas_rapidas.baja();
        cout <<"Has descartado el:"<<arma_descartada;
    }
}