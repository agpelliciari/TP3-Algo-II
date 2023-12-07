#ifndef TABLERO_HPP
#define TABLERO_HPP

#define LADRILLO_EMOJI "\U0001f9f1"
#define CASILLEROS_EMOJI "\U0001f7e9"
#define SALIDA_EMOJI "\U0001f384"
#define PYRAMID_EMOJI "\U0001f479"
#define JUGADOR_EMOJI "\U0001f385"

#include <string>
#include "Grafo.hpp"

const size_t TAMANIO_TABLERO = 9;
const size_t CANT_CASILLEROS=81;
const size_t ENTRADA=0;
const size_t SALIDA=80;
const int PESO_BASE=10;
const int FACTOR_RIESGO=5;


class Tablero {

private:
    Grafo* layout;
    size_t pos_entrada;
    size_t pos_salida;
    size_t pos_jugador;
    std::vector<int> pos_pyramid;
    std::vector<size_t> paredes;
    std::vector<size_t> peligrosas;
    Matriz matriz_tablero;


    //pre:-
    //pos: Desconecta la casilla del layout seteando las aristas a vertices adyacentes a infinito.
    void aislar_casilla(size_t casilla);

    //pre:-
    //pos: Conecta la casilla del layout seteando las aristas a vertices adyacentes a su peso base.
    void conectar_casilla(size_t casilla, int peso, bool bidireccional);

    //pre:-
    //pos: Incrementa el peso de las aristas adyacentes al vertice indicado, en un valor 5 veces el base. 
    void zona_peligrosa(size_t casilla);
    
    //pre: -
    //pos: Reconecta todo vertice peligroso con su PESO_BASE, deja vacio el vector peligrosas.
    void quitar_zona_peligrosa(size_t casilla);

    //pre:-
    //pos: Aisla las casillas "pared" en base a la altura del nivel del arbol de placas.
    void set_layout(int altura);

    //pre:-
    //pos: Crea a lo sumo 2 pyramid heads y los ubica en vertices validos del layout.
    void crear_pyramid();

    //pre:-
    //pos: Quita a pyramid del tablero, restituyendo la casilla y seteando las aristas a vertices adyacentes a valor base.
    void eliminar_pyramid(int casilla);

    //pre:-
    //pos: Inicia el grafo conectando los vertices a traves de aristas de peso base. (GONZA, si le pifie editalo)
    void pre_tablero();

    //pre:-
    //pos: Indica si el numero ingresado es par.
    bool es_par(size_t numero);

    //pre:-
    //pos: Indica si la casilla ingresada esta en el borde derecho.
    bool es_borde_derecho(size_t casilla);

    //pre:-
    //pos: Indica si la casilla ingresada esta en el borde izquierdo.
    bool es_borde_izquierdo(size_t casilla);

    //pre:-
    //pos: Determina que vector de paredes debe asignarse al layout.
    std::vector<size_t> elegir_paredes(bool es_par);

    //pre:-
    //pos: Devuelve true si la casilla es una pared, falso en caso contrario.
    bool es_posicion_pared(int posicion);

    //pre:-
    //pos: Conecta en ambas direcciones a las casillas ingresadas.
    void conectar_casilleros(size_t casilla, size_t casilla_a_conectar,int peso, bool bidireccion);

    //pre:-
    //pos: Restaura todos los atributos del tablero.
    void restaurar_atributos();

    //pre: -
    //pos: Coloca los objetos en la matriz que luego sea mostrada en consola.
    void establecer_matriz_tablero();

public:
    //constructor
    Tablero();

    //pre:-
    //post: Define el layout del nivel, ubicando paredes, enemigos y conectando los vertices con aristas de peso base.  
    void iniciar_tablero(int altura);
    
    //Pre-
    //Pos: Actualiza la posicion del jugador en el tablero, devolviendo los puntos gastados.
    int actualizar_posicion(int movimiento);

    //Pre:-
    //Pos: Actualiza las aristas de los pyramid en el layout en funcion de si el jugador tiene arma.
    void modificar_tablero(bool arma);

    //Pre:-
    //Pos: True si la posicion del jugador es la salida del nivel.
    bool es_posicion_final();

    //Pre:-
    //Pos: Devuelve true si elimina al pyramid head.
    bool es_matar_pyramid();

    //Pre:-
    //Pos:Retorna un pair cuya "primer" componente es el vector de camino y la 2da el peso del mismo.
    std::pair<std::vector<size_t>,int> camino_automatico();

    //Pre:-
    //Pos: True si la casilla ingresada es adyacente al Pyramid, false en cualquier otro caso.
    bool es_zona_peligrosa(size_t casilla);

    //Pre:-
    //Pos: True si la casilla ingresada se encuentra en el borde superior.
    bool es_borde_superior(size_t casilla);

    //Pre:-
    //Pos: True si la casilla ingresada se encuentra en el borde inferior.
    bool es_borde_inferior(size_t casilla);

    //Pre:-
    //Pos: Muestra por consola la situacion actual del tablero.
    void mostrar_matriz_tablero();

    //Pre:-
    //Pos: True si la casilla ingresada tiene un pyramid.
    bool esta_pyramid(size_t casilla);

    //Destructor
    ~Tablero();


};

#endif