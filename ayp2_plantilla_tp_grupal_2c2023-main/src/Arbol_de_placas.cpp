#include "Arbol_de_placas.hpp"
#include <string>
#include <iostream>

using namespace std;

Arbol_de_placas::Arbol_de_placas() = default ;

void Arbol_de_placas::alta_placa(Placa* puntero_placa) {
    this->arbol_placas.alta(puntero_placa);
}

void Arbol_de_placas::consulta_placa(Placa* puntero_placa) {

    bool se_encontro = this->arbol_placas.consulta(puntero_placa);

    if (se_encontro) {
        cout << "Esta placa ya fue recogida" << endl;
    }
    else {
        cout << "Esta placa aun no fue recogida" << endl;
    }

    Placa::liberar(placa_a_buscar);
}

void Arbol_de_placas::baja_placa(int id_placa){

    Placa* placa_a_eliminar = new Placa("vacio", "vacio", id_placa);

    arbol_placas.baja(placa_a_eliminar);

    Placa::liberar(placa_a_eliminar);

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

Arbol_de_placas::~Arbol_de_placas() {
}
