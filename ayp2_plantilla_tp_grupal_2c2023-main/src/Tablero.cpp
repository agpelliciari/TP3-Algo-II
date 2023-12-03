#include "Tablero.hpp"
#include <cstdlib>
#include <ctime>


void Tablero::conectar_casilla(size_t casilla) {

    //No incluyo entrada y salida ya que ni pyramid head ni las paredes pueden ser entradas validas a esta funcion.

    size_t ESQUINA_SUPERIOR_IZQUIERDA = 72;
    size_t ESQUINA_INFERIOR_DERECHA = 8;

    if (casilla == ESQUINA_INFERIOR_DERECHA) {

        layout->cambiar_arista(casilla, casilla + 9, PESO_BASE);
        layout->cambiar_arista(casilla, casilla - 1, PESO_BASE);

    }else if(casilla == ESQUINA_SUPERIOR_IZQUIERDA) {

        layout->cambiar_arista(casilla,casilla+1,PESO_BASE);
        layout->cambiar_arista(casilla,casilla-9,PESO_BASE);

    }else if (casilla <= 7 && casilla >=1){ //borde inferior

        layout->cambiar_arista(casilla,casilla+1,PESO_BASE);
        layout->cambiar_arista(casilla,casilla+9,PESO_BASE);
        layout->cambiar_arista(casilla,casilla-1,PESO_BASE);

    }else if(casilla <= 79 && casilla >= 73){ // borde superior

        layout->cambiar_arista(casilla,casilla+1,PESO_BASE);
        layout->cambiar_arista(casilla,casilla-1,PESO_BASE);
        layout->cambiar_arista(casilla,casilla-9,PESO_BASE);

    }else if(es_borde_izquierdo(casilla)){

        layout->cambiar_arista(casilla,casilla+1,PESO_BASE);
        layout->cambiar_arista(casilla,casilla+9,PESO_BASE);
        layout->cambiar_arista(casilla,casilla-9,PESO_BASE);

    }else if(es_borde_derecho(casilla)){

        layout->cambiar_arista(casilla,casilla+9,PESO_BASE);
        layout->cambiar_arista(casilla,casilla-1,PESO_BASE);
        layout->cambiar_arista(casilla,casilla-9,PESO_BASE);

    } else{ //No es ningun borde

        layout->cambiar_arista(casilla,casilla+1,PESO_BASE);
        layout->cambiar_arista(casilla,casilla+9,PESO_BASE);
        layout->cambiar_arista(casilla,casilla-1,PESO_BASE);
        layout->cambiar_arista(casilla,casilla-9,PESO_BASE);

    }

}

void Tablero::set_layout(int altura) {

    paredes = elegir_paredes(es_par(altura));

    for(size_t i = 0;i<paredes.size();i++){
        aislar_casilla(i);
    }

}

std::pair<std::vector<size_t>, int> Tablero::camino_automatico() {

    layout->usar_dijkstra();

    return layout->obtener_camino_minimo(pos_jugador,SALIDA);

}

bool Tablero::es_par(size_t numero) {

    return numero%2 == 0;
}

std::vector<size_t> Tablero::elegir_paredes(bool es_par) {
    std::vector<size_t> devolver;
    if (es_par){

        devolver = {3,12,14,16,19,21,23,25,28,32,34,37,39,43,48,50,52,55,57,59,64,68,70,73,75,77,79};

    } else{

        devolver = {3,10,12,14,16,17,28,29,30,32,34,43,45,46,48,49,50,61,64,65,66,67,68,70};

    }
    return devolver;
}

bool Tablero::es_borde_derecho(size_t casilla) {

    std::vector<size_t> borde_derecho = {17,26,35,44,53,62,71};
    bool devolver = false;

    while (size_t i = 0 < borde_derecho.size() || devolver){

        if (casilla == borde_derecho[i]){
            devolver = true;
        } else {
            i++;
        }

    }
    return devolver;
}

bool Tablero::es_borde_izquierdo(size_t casilla) {
    std::vector<size_t> borde_izquierdo = {9,18,27,36,45,54,63};
    bool devolver = false;

    while (size_t i = 0 < borde_izquierdo.size() || devolver){

        if (casilla == borde_izquierdo[i]){
            devolver = true;
        } else {
            i++;
        }

    }
    return devolver;
}

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