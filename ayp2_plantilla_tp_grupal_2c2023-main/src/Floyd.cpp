#include "Floyd.hpp"
#include <iostream>

Floyd::Floyd() {}

void Floyd::inicializar_matrices() {
    matriz_caminos = Matriz(cantidad_vertices);
    for (size_t i = 0; i < cantidad_vertices; i++) {
        for (size_t j = 0; j < cantidad_vertices; j++) {
            matriz_caminos.elemento(i, j) = (int) j;
        }
    }

    matriz_costos = matriz_adyacencia;
}

std::vector<size_t> Floyd::obtener_camino(size_t origen, size_t destino) {
    std::vector<size_t> camino;

    if (matriz_costos.elemento(origen, destino) == INFINITO) {
        std::cout << "No hay un camino que conecte " <<  origen << " con " << destino;
    } else {
        camino.push_back(origen);
        while (origen != destino) {
            origen = (size_t) this->matriz_caminos.elemento(origen, destino) ;
            camino.push_back(origen) ;
        } 
    }

    return camino;
}

std::vector<size_t>
Floyd::calcular_camino_minimo(Matriz adyacencia, size_t vertices, size_t origen, size_t destino, bool hay_cambios) {
    if (hay_cambios) {
        matriz_adyacencia = adyacencia;
        cantidad_vertices = vertices;
        inicializar_matrices();

        for (size_t k = 0; k < cantidad_vertices; k++) {

            for (size_t i = 0; i < cantidad_vertices; i++) {

                for (size_t j = 0; j < cantidad_vertices; j++) {

                    if ((i != k) && (j != k)) {

                        int costo_mediante_k = matriz_costos.elemento(i, k) + matriz_costos.elemento(k, j) ;

                        if (costo_mediante_k < matriz_costos.elemento(i, j)) {

                            matriz_costos.elemento(i, j) = costo_mediante_k ;

                            matriz_caminos.elemento(i, j) = matriz_caminos.elemento(i, k) ;

                        }
                    }
                }
            }
        }
        
    }

    return obtener_camino(origen, destino);
}

Floyd::~Floyd() {}