#include "Menu.hpp"
#include "Placa.hpp"
#include "Arbol_de_placas.hpp"
#include <iostream>


using namespace std;


void Menu::convertir_cadena_a_mayuscula(string & cadena) {
    for(size_t i = 0 ; i < cadena.size() ; i++) {
        cadena[i] = (char)toupper(cadena[i]);
    }
}

void Menu::convertir_cadena_a_minuscula(string & cadena) {

    for(size_t i = 0 ; i < cadena.size() ; i++) {
        cadena[i] = (char)tolower(cadena[i]);
    }

} 


void Menu::usar(Arbol_de_placas* puntero_arbol_placas) {

    string nombre_placa;
    string leyenda_placa;
    string id_placa;
    string accion_del_usuario;

    while (accion_del_usuario != "salir") {

        cout << "\nAcciones posibles sobre el Arbol de Placas : " << endl;
        cout << ACCION_ALTA << endl;
        cout << ACCION_BAJA << endl;
        cout << ACCION_CONSULTA << endl;
        cout << "Escriba la accion que desea realizar : ";
        getline(cin, accion_del_usuario);
        convertir_cadena_a_minuscula(accion_del_usuario);   //  El metodo usar() es static por ende para usar el metodo "convertir_cadena_a_minuscula" tambien debemos declararlo static.

        if (accion_del_usuario != "salir") {
            
            if (accion_del_usuario == ACCION_ALTA) {

                cout << "\nNombre de la Placa : ";
                getline(cin, nombre_placa);
                cout << "Leyenda de la Placa : ";
                getline(cin, leyenda_placa);
                cout << "ID de la Placa : ";
                getline(cin, id_placa);

                Placa* puntero_placa = new Placa(nombre_placa, leyenda_placa, stoi(id_placa));  // Previo al uso del stoi debo verificar que la conversion es posible.
                puntero_arbol_placas->alta_placa(puntero_placa);      

            } else if (accion_del_usuario == ACCION_BAJA) {

                cout << "\nIngrese el ID de la Placa a eliminar : ";
                getline(cin, id_placa);
                // usar metodo baja de la clase Arbol_de_placas.

            } else if (accion_del_usuario == ACCION_CONSULTA) {
                
                cout << "\nIngrese el ID de la Placa a consultar : ";
                getline(cin, id_placa);
                Placa* placa_a_buscar = new Placa("vacio", "vacio", stoi(id_placa));
                puntero_arbol_placas->consulta_placa(placa_a_buscar);
                delete placa_a_buscar;

            } else {
                cout << "Lo siento el Arbol de Placas no realiza la accion ingresada"<< endl;
            }
        }
  
    }


}