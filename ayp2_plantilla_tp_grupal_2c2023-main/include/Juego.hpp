#ifndef JUEGO_H
#define JUEGO_H

#include "Menu_principal.hpp"
#include "Arbol_de_placas.hpp"
#include "Inventario_de_Armas.hpp"
#include "Tablero.hpp"

class Juego {
private:
    Menu_principal menu_juego;

    Tablero tablero_juego;

    Arbol_de_placas arbol_placas;

    Inventario_de_Armas inventario;
    
    int costo_total_movimientos;

    int nivel;

    bool partida_en_curso;
    
    // Pre: -.
    // Post: Establece las condiciones iniciales de la partida.
    void condiciones_iniciales();
    
    // Pre: -.
    // Post: Genera una placa aleatoria de id entre 100 y 666.
    void generar_placa_aleatoria();

    // Pre: -.
    // Post: Genera un arma aleatoria de potencia entre 0 y 100.
    void generar_arma_aleatoria();

    // Pre: -.
    // Post: Desequipa y elimina el arma actual.
    void romper_arma();

    // Pre: -.
    // Post: Inicializa un tablero.
    void nuevo_tablero();
    
    // Pre: -.
    // Post: Inicializa una partida de cero.
    void nueva_partida();

    // Pre: -.
    // Post: Crea un nuevo nivel.
    void nuevo_nivel();

    // Pre: -.
    // Post: Simula el movimiento dentro del tablero.
    void moverse_en_tablero();
    
    // Pre: -.
    // Post: Muestra el camino minimo desde la posicion que se encuentra el usuario.
    void imprimir_camino_minimo();
    
    // Pre: -.
    // Post: Usa el camino minimo desde la posicion que se encuentra el usuario.
    void usar_camino_minimo();

    // Pre: -.
    // Post: Le da la opcion al usuario de equipar o desequipar el arma con mayor o menos potencia.
    void equipar_o_desequipar_arma();

    // Pre: -.
    // Post: Muestra el puntaje total recolectado por el usuario.
    void imprimir_puntaje_total();

    // Pre: -.
    // Post: Flujo de una partida.
    void partida();
public:
    
    // Constructor.
    Juego();
    
    // Pre: -.
    // Post: Inicializa el menu principal del juego.
    void inicializar_juego();

    // Destructor.
    ~Juego();
};

#endif