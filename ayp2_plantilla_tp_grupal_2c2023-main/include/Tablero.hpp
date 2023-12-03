#ifndef TABLERO_HPP
#define TABLERO_HPP

#include <string>
#include "Grafo.hpp"

const size_t TAMANIO_TABLERO = 4;
const size_t CANT_CASILLEROS=81;
const size_t ENTRADA=0;
const size_t SALIDA=80;
const int PESO_BASE=10;

class Tablero {

private:
    Grafo* layout;
    size_t ENTRADA;
    size_t SALIDA;
    size_t pos_jugador;
    std::vector<int> pos_pyramid;
    std::vector<size_t> paredes;

//pre:-
//pos: Desconecta la casilla del layout seteando las aristas a vertices adyacentes a infinito.
void aislar_casilla(size_t posicion);

//pre:-
//pos: Conecta la casilla del layout seteando las aristas a vertices adyacentes a su peso base.
void conectar_casilla(size_t casilla);

//pre:-
//pos: Aisla las casillas "pared" en base a la altura del nivel del arbol de placas.
void set_layout(int altura);

//pre:-
//pos: Crea a lo sumo 2 pyramid heads y los ubica en vertices validos del layout.
void crear_pyramid();

//pre:-
//pos: Quita a pyramid del tablero, restituyendo la casilla y seteando las aristas a vertices adyacentes a valor base.
void eliminar_pyramid();

//pre:-
//pos: Inicia el grafo conectando los vertices adyacentes a traves de aristas de peso base.
void pre_tablero();

bool es_posicion_pared(int posicion);

public:
    //constructor
    Tablero();

    void iniciar_tablero();
    
    size_t actualizar_posicion();

    void modificar_tablero(bool arma);

    std::pair<std::vector<size_t>,int> camino_automatico();

};

#endif