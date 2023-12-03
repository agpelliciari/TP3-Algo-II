#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#include "Constantes.hpp"

class Menu_principal {
private:
    
public:
    
    // Constructor.
    Menu_principal();

    // Pre: Recibe la opcion elegida por el usuario.
    // Post: Valida la opcion elegida y la devuelve.
    string recibir_opcion_juego(string opcion);

    // Pre: Recibe la opcion elegida por el usuario.
    // Post: Valida la opcion elegida y la devuelve.
    string recibir_opcion(string opcion);

    // Pre: -
    // Post: Muestra por pantalla el menu de opciones.
    void imprimir_menu_principal();

    // Pre: -
    // Post: Muestra por pantalla el menu de opciones de la partida.
    void imprimir_menu_juego();

    // Destructor
    ~Menu_principal();
};

#endif