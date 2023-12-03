#include "Menu_principal.hpp"

Menu_principal::Menu_principal(){}

// MENU PRINCIPAL

void Menu_principal::imprimir_menu_principal(){
    cout << "--------------- MENU PRINCIPAL -----------------" << endl;
    cout << "1) Nueva partida" << endl;
    cout << "2) Continuar Partida" << endl;
    cout << "3) Salir" << endl;
}

string Menu_principal::recibir_opcion(string opcion){
    cout << "ELIJA UNA OPCION: ";
    cin >> opcion;

    while((opcion != NUEVA_PARTIDA) && (opcion != CONTINUAR_PARTIDA) && (opcion != SALIR)){
        cout << "La opción es invalida, por favor ingrese otra opción: ";
        cin >> opcion;
    }
    return opcion;
}

// MENU JUEGO

void Menu_principal::imprimir_menu_juego(){
    cout << "--------------- MENU JUEGO ---------------------" << endl;
    cout << "1) Moverse en el tablero" << endl;
    cout << "2) Mostrar camino minimo" << endl;
    cout << "3) Usar camino minimo" << endl;
    cout << "4) Equipar/desequipar arma" << endl;
    cout << "5) Mostrar puntaje actual" << endl;
    cout << "6) Ir al menu principal" << endl;
}

string Menu_principal::recibir_opcion_juego(string opcion){
    cout << "ELIJA UNA OPCION: ";
    cin >> opcion;

    while((opcion != MOVERSE_EN_EL_TABLERO) && (opcion != MOSTRAR_CAMINO_MINIMO) && (opcion != USAR_CAMINO_MINIMO) && (opcion != EQUIPAR_DESEQUIPAR_ARMA) && (opcion != MOSTRAR_PUNTAJE) && (opcion != VOLVER_MENU_PRINCIPAL)){
        cout << "La opción es invalida, por favor ingrese otra opción: ";
        cin >> opcion;
    }
    return opcion;
}

Menu_principal::~Menu_principal() {}