#ifndef ARBOL_DE_PLACAS_HPP
#define ARBOL_DE_PLACAS_HPP

#include "ABBv2.hpp"
#include "Placa.hpp"

const std::string ACCION_ALTA = "alta";
const std::string ACCION_BAJA = "baja";
const std::string ACCION_CONSULTA = "consulta";

class Arbol_de_placas {
private:
    ABB<Placa*, Placa::menor, Placa::igual> arbol_placas;

public:
    // Constructor.
    Arbol_de_placas();

    // Pre: -
    // Post: Agrega la placa y la organiza acorde a la función de comparación del árbol por ID.
    void alta_placa(Placa* puntero_placa);

    // Pre: 
    // Post:
    void baja_placa(std::string nombre_placa);   // no se si el parametro debe ser el nombre, la leyenda o el id de la placa.

    // Pre: arbol_placas no puede estar vacio.
    // Post: Devuelve true si se encuentra la placa segun el id indicado.
    void consulta_placa(Placa* puntero_placa);

    // Destructor.
    ~Arbol_de_placas();
};


#endif //ARBOL_DE_PLACAS_HPP
