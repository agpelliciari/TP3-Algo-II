#ifndef ARBOL_DE_PLACAS_HPP
#define ARBOL_DE_PLACAS_HPP

#include "ABBv2.hpp"
#include "Placa.hpp"
#include "bGVjdG9y.hpp"

const std::string ACCION_ALTA = "alta";
const std::string ACCION_BAJA = "baja";
const std::string ACCION_CONSULTA = "consulta";

const int RANGO_MAXIMO = 567;
const int RANGO_MINIMO = 100;

class Arbol_de_placas {
private:
    ABB<Placa*, Placa::menor, Placa::igual> arbol_placas;

public:
    // Constructor.
    Arbol_de_placas();

    // Pre: -
    // Post: Agrega la placa y la organiza acorde a la función de comparación del árbol por ID.
    void alta_placa(Placa* puntero_placa);

    // Pre: El arbol no puede estar vacio.
    // Post: Se elimina la placa del arbol, si se encuentra.
    void baja_placa(Placa* puntero_placa);

    // Pre: El arbol no puede estar vacio.
    // Post: Imprime un mensaje por pantalla si se encuentra la placa buscada o no.
    void consulta_placa(Placa* puntero_placa);
    
    // Pre: - .
    // Post: Devuelve la altura del arbol.
    int altura_arbol_placas();
    
    // Pre: -.
    // Post: Imprime por pantalla el orden del mensaje cargado en el arbol.
    void mostrar_mensaje_descifrado();
    
    //Pre:-
    //Post: Agrega una placa aleatoria al arbol.
    void agregar_placa_aleatoria();

    // Destructor.
    ~Arbol_de_placas();
};


#endif //ARBOL_DE_PLACAS_HPP
