#include "Menu_principal.hpp"

Menu_principal::Menu_principal(){}

void Menu_principal::imprimir_menu_juego(){
    cout << "--------------- MENU JUEGO ---------------------" << endl;
    cout << "1) Moverse en el tablero" << endl;
    cout << "2) Mostrar camino minimo" << endl;
    cout << "3) Usar camino minimo" << endl;
    cout << "4) Equipar/desequipar arma" << endl;
    cout << "5) Mostrar puntaje actual" << endl;
    cout << "6) Salir del juego" << endl;
}

string Menu_principal::recibir_opcion_juego(string opcion){
    cout << "ELIJA UNA OPCION: ";
    cin >> opcion;

    while((opcion != MOVERSE_EN_EL_TABLERO) && (opcion != MOSTRAR_CAMINO_MINIMO) && (opcion != USAR_CAMINO_MINIMO) && (opcion != EQUIPAR_DESEQUIPAR_ARMA) && (opcion != MOSTRAR_PUNTAJE) && (opcion != SALIR)){
        cout << "La opción es invalida, por favor ingrese otra opción: ";
        cin >> opcion;
    }
    return opcion;
}

Menu_principal::~Menu_principal() {}