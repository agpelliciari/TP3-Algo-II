#include "Arbol_de_placas.hpp"
#include <string>

using namespace std;

Arbol_de_placas::Arbol_de_placas() = default ;

void Arbol_de_placas::alta_placa(Placa* puntero_placa) {
    arbol_placas.alta(puntero_placa);
}

bool Arbol_de_placas::consulta_placa(int id_placa) {

    Placa* placa_a_buscar = new Placa("nada", "nada", id_placa);
    vector<Placa*> vector_de_placas;
    vector_de_placas = arbol_placas.inorder();
    size_t tamanio_vector_de_placas = vector_de_placas.size();
    size_t contador = 0 ;
    bool se_encontro = false ;

    while ((contador < tamanio_vector_de_placas) && (!se_encontro)) {

        if ((vector_de_placas[contador]) == placa_a_buscar) {
            se_encontro = true;
        }
        contador ++;
    }
}

Arbol_de_placas::~Arbol_de_placas() {
}
