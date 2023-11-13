#include "Arbol_de_placas.hpp"
#include <string>
#include <iostream>
#include "bGVjdG9y.hpp"

int main() {

    Arbol_de_placas arbol;

    // ALTA
    Placa* placa_aux = new Placa("X", "Y", 1024);
    arbol.alta_placa(placa_aux);

    // MENSAJE
    arbol.mostrar_mensaje_descifrado();
    
    // CONSULTA
    arbol.consulta_placa(1024);
    arbol.consulta_placa(-10);
    arbol.consulta_placa(661);

    // BAJA
    cout << "Placa que no se encuentra el el arbol" << endl;
    arbol.baja_placa(-10);

    cout << "Placa que se encuentra en el arbol" << endl;
    arbol.baja_placa(661);
    arbol.consulta_placa(661);

    return 0;
}