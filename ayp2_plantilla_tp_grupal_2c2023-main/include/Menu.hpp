#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <string>
#include "Arbol_de_placas.hpp"


class Menu {
public:
    //Pre: -
    //Post: MODIFICA la cadena convirtiendo todas sus letras en mayuscula.
    static void convertir_cadena_a_mayuscula(std::string & cadena);

    //Pre: -
    //Post: MODIFICA la cadena convirtiendo todas sus letras en minuscula.
    static void convertir_cadena_a_minuscula(std::string & cadena);

    //Pre: Debe instanciarse Inventario de forma dinamica para luego pasarlo por "parametro".
    //Post: Muestra por pantalla y maneja el menu de inicio.
    static void usar(Arbol_de_placas* puntero_arbol_placas);

};


#endif