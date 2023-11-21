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
        cout << "No hay armas! Solo te queda defenderte con tus propios puños.";
    }
    else{
        Arma arma_rapida;
        arma_rapida=armas_rapidas.primero();
        cout << "Deseas equipar el " << arma_rapida <<"? (s/n)";
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





