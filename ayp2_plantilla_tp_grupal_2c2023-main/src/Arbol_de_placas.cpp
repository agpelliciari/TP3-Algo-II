#include "Arbol_de_placas.hpp"
#include <string>
#include <iostream>

using namespace std;

Arbol_de_placas::Arbol_de_placas() = default ;

void Arbol_de_placas::alta_placa(Placa* puntero_placa) {
    this->arbol_placas.alta(puntero_placa);
}

void Arbol_de_placas::consulta_placa(int id_placa) {

    Placa* placa_a_buscar = new Placa("vacio", "vacio", id_placa);
    bool se_encontro = this->arbol_placas.consulta(placa_a_buscar);

    if (se_encontro) {
        cout << "Esta placa ya fue recogida" << endl;
    }
    else {
        cout << "Esta placa aun no fue recogida" << endl;
    }

    delete placa_a_buscar;
}

Arbol_de_placas::~Arbol_de_placas() {
}
