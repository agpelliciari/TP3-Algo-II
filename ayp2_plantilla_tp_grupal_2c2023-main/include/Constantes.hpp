#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Constantes de opciones del Menu del juego
const string MOVERSE_EN_EL_TABLERO = "1";
const string MOSTRAR_CAMINO_MINIMO = "2";
const string USAR_CAMINO_MINIMO = "3";
const string EQUIPAR_DESEQUIPAR_ARMA = "4";
const string MOSTRAR_PUNTAJE = "5";
const string SALIR = "6";

// Constantes de niveles del juego
const int PRIMER_NIVEL = 1;
const int ULTIMO_NIVEL = 5;
const int PORCENTAJE_MAXIMO = 100;
const int PROBABILIDAD = 20;

// Constantes de opciones de movimiento en el juego
const string ARRIBA = "W";
const int MOVERSE_ARRIBA = 9;

const string ABAJO = "S";
const int MOVERSE_ABAJO = 1;

const string IZQUIERDA = "A";
const int MOVERSE_IZQUIERDA = -1;

const string DERECHA = "D";
const int MOVERSE_DERECHA = -9;

#endif