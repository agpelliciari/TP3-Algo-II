#include "Arbol_de_placas.hpp"
#include <string>
#include <iostream>

using namespace std;

Arbol_de_placas::Arbol_de_placas() = default ;

void Arbol_de_placas::alta_placa(Placa* puntero_placa) {
    this->arbol_placas.alta(puntero_placa);
}

void Arbol_de_placas::consulta_placa(Placa* puntero_placa) {

    if (arbol_placas.vacio())
    {
        cout << "El arbol de placas se encuentra vacio, ingrese una para poder utilizar esta funcion." << endl;
    }
    else
    {
       bool se_encontro = this->arbol_placas.consulta(puntero_placa);
       if (se_encontro) {
        cout << "Esta placa ya fue recogida" << endl;
        }
       else {
        cout << "Esta placa aun no fue recogida" << endl;
        } 
    }
}

void Arbol_de_placas::baja_placa(Placa* puntero_placa){

    if (arbol_placas.vacio())
    {
        cout << "El arbol de placas se encuentra vacio, ingrese una para poder utilizar esta funcion." << endl;
    }
    else
    {
       arbol_placas.baja(puntero_placa);

       Placa::liberar(puntero_placa); 
    }
}

void Arbol_de_placas::mostrar_mensaje_descifrado(){
    
    bGVjdG9y clase;

    clase.Y2FyZ2Fy(arbol_placas);

    std::vector<Placa*> recorrido_vec = arbol_placas.preorder();

    for (size_t i = 0; i < recorrido_vec.size(); i++)
    {
        cout << recorrido_vec[i] << endl;
    }
}

int Arbol_de_placas::altura_arbol_placas(){
    return arbol_placas.altura_maxima();
}

Arbol_de_placas::~Arbol_de_placas(){
    if (!arbol_placas.vacio())
    {
        std::vector<Placa*> elementos_arbol = arbol_placas.ancho();
        for (size_t i = 0; i < arbol_placas.tamanio(); i++){
            Placa* puntero_placa = elementos_arbol[i];
            Placa::liberar(puntero_placa);
        }
    }
}
