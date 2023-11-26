#ifndef INVENTARIO_DE_ARMAS_HPP
#define INVENTARIO_DE_ARMAS_HPP

#include  "Arma.hpp"
#include "Heap.hpp"

const Arma ARMA_DEFAULT("Puños",0);

class Inventario_de_Armas
{
private:
    Heap<Arma,Arma::mayor> armas_rapidas;
    Arma arma_actual;
    bool ahorro_municion; //el flag indica si el inv. opera con la mayor/menor potencia de armas.

    //Pre:-
    //Post: Intercambia el arma actual por la de mayor/menor potencia del inventario, regresando el arma
    //actual al inventario (en caso de no ser el arma default).
    void cambiar_arma();

public:
    //constructor
    Inventario_de_Armas();
    
    //Pre:-
    //Post: Muestra el arma actual equipada.
    void consulta();

    // Pre:-
    //Post: Elimina el arma del inventario.
    void baja();

    //Pre:-
    //Post: Agrega objeto arma al inventario de armas rapidas.
    void alta();
    
    //Pre:-
    //Post: Activa el ahorro de municion para q el inventario use el arma mas debil primero. ()
    void activar_modo_ahorro();

    //Pre:-
    //Post: Desctiva el ahorro de municion para q el inventario use el arma mas fuerte primero.
    void desactivar_modo_ahorro();

};

#endif