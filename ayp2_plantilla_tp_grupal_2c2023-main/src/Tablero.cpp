#include "Tablero.hpp"


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


