#include "Tablero.hpp"

#include <cstdlib>
#include <ctime>


Tablero::Tablero() {
    this->layout = new Grafo(CANT_CASILLEROS);
    this->pos_pyramid = {-1,-1};
}


void Tablero::pre_tablero() {

    for (size_t i = 0; i < TAMANIO_TABLERO; i++) {

        for (size_t j = 0; j < TAMANIO_TABLERO; j++) {

            if (i == 0) {

                if (j == 0) {
                    layout->cambiar_arista(j, j + 1, PESO_BASE);

                    layout->cambiar_arista(j, j + TAMANIO_TABLERO, PESO_BASE);
                }
                else if (j == (TAMANIO_TABLERO - 1)) {
                    layout->cambiar_arista(j, j - 1, PESO_BASE);
                    
                    layout->cambiar_arista(j, j + TAMANIO_TABLERO, PESO_BASE);
                }
                else {
                    layout->cambiar_arista(j, j - 1, PESO_BASE);

                    layout->cambiar_arista(j, j + 1, PESO_BASE);
                    
                    layout->cambiar_arista(j, j + TAMANIO_TABLERO, PESO_BASE);
                }

            }
            else if (i == (TAMANIO_TABLERO - 1)) {

                layout->cambiar_arista(j + (i*TAMANIO_TABLERO), j + (i*TAMANIO_TABLERO) - TAMANIO_TABLERO, PESO_BASE);

                if (j == 0) {
                    layout->cambiar_arista(j + (i*TAMANIO_TABLERO), j + (i*TAMANIO_TABLERO) + 1, PESO_BASE);
                }
                else if (j == (TAMANIO_TABLERO - 1)) {
                    layout->cambiar_arista(j + (i*TAMANIO_TABLERO), j + (i*TAMANIO_TABLERO) - 1, PESO_BASE);
                }
                else {
                    layout->cambiar_arista(j + (i*TAMANIO_TABLERO), j + (i*TAMANIO_TABLERO) + 1, PESO_BASE);
                    layout->cambiar_arista(j + (i*TAMANIO_TABLERO), j + (i*TAMANIO_TABLERO) - 1, PESO_BASE);
                }
            }
            else {

                layout->cambiar_arista(j + (i*TAMANIO_TABLERO), j + (i*TAMANIO_TABLERO) + TAMANIO_TABLERO, PESO_BASE);
                    
                layout->cambiar_arista(j + (i*TAMANIO_TABLERO), j + (i*TAMANIO_TABLERO) - TAMANIO_TABLERO, PESO_BASE);

                if (j == 0) {
                    layout->cambiar_arista(j + (i*TAMANIO_TABLERO), j + (i*TAMANIO_TABLERO) + 1, PESO_BASE);
                }
                else if (j == (TAMANIO_TABLERO - 1)) {
                    layout->cambiar_arista(j + (i*TAMANIO_TABLERO), j + (i*TAMANIO_TABLERO) - 1, PESO_BASE);
                }
                else {
                    layout->cambiar_arista(j + (i*TAMANIO_TABLERO), j + (i*TAMANIO_TABLERO) + 1, PESO_BASE);
                    layout->cambiar_arista(j + (i*TAMANIO_TABLERO), j + (i*TAMANIO_TABLERO) - 1, PESO_BASE);
                }

            }

        }

    }
}


void Tablero::aislar_casilla(size_t posicion) {

    if (posicion < TAMANIO_TABLERO) {

        this->layout->eliminar_arista(posicion, posicion + 1);
        this->layout->eliminar_arista(posicion + 1, posicion);

        this->layout->eliminar_arista(posicion, posicion - 1);
        this->layout->eliminar_arista(posicion - 1, posicion);

        this->layout->eliminar_arista(posicion, posicion + TAMANIO_TABLERO);
        this->layout->eliminar_arista(posicion + TAMANIO_TABLERO, posicion);

    }
    else if ((posicion >= (CANT_CASILLEROS - TAMANIO_TABLERO)) && (posicion < CANT_CASILLEROS)) {

        this->layout->eliminar_arista(posicion, posicion + 1);
        this->layout->eliminar_arista(posicion + 1, posicion);

        this->layout->eliminar_arista(posicion, posicion - 1);
        this->layout->eliminar_arista(posicion - 1, posicion);

        this->layout->eliminar_arista(posicion, posicion - TAMANIO_TABLERO);
        this->layout->eliminar_arista(posicion - TAMANIO_TABLERO, posicion);

    }
    else {

        this->layout->eliminar_arista(posicion, posicion + 1);
        this->layout->eliminar_arista(posicion + 1, posicion);

        this->layout->eliminar_arista(posicion, posicion - 1);
        this->layout->eliminar_arista(posicion - 1, posicion);

        this->layout->eliminar_arista(posicion, posicion + TAMANIO_TABLERO);
        this->layout->eliminar_arista(posicion + TAMANIO_TABLERO, posicion);

        this->layout->eliminar_arista(posicion, posicion - TAMANIO_TABLERO);
        this->layout->eliminar_arista(posicion - TAMANIO_TABLERO, posicion);

    }
}


bool Tablero::es_posicion_pared(int posicion) {

    bool es_pared = false;

    for (size_t i = 0; i < paredes.size(); i++) {
        if (paredes[i] == (size_t) posicion) {
            es_pared = true;
        }
    }

    return es_pared;
}


void Tablero::crear_pyramid() {

    srand(time(0));

    int primer_numero_aleatorio = 1 + (rand() % 2) ;
    int segundo_numero_aleatorio = 1 + (rand() % 2) ;
    
    if (primer_numero_aleatorio == 1) {
        int posicion_primer_pyramid = 1 + rand() % (CANT_CASILLEROS-1) ;
        while (es_posicion_pared(posicion_primer_pyramid)) {
            posicion_primer_pyramid = 1 + rand() % (CANT_CASILLEROS-1) ;
        }
        pos_pyramid[0] = posicion_primer_pyramid;
    }

    if (segundo_numero_aleatorio == 1) {
        int posicion_segundo_pyramid = 1 + rand() % (CANT_CASILLEROS-1) ;
        while ((es_posicion_pared(posicion_segundo_pyramid)) || (posicion_segundo_pyramid == pos_pyramid[0])) {
            posicion_segundo_pyramid = 1 + rand() % (CANT_CASILLEROS-1) ;
        }
        pos_pyramid[1] = posicion_segundo_pyramid;
    }

    if (pos_pyramid[0] != (-1)) {

        aislar_casilla((size_t) pos_pyramid[0]);

    }

    if (pos_pyramid[1] != (-1)) {

        aislar_casilla((size_t) pos_pyramid[1]);

    }

}