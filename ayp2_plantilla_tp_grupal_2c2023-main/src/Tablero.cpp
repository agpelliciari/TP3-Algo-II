#include "Tablero.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>


void Tablero::conectar_casilla(size_t casilla, int peso) {

    size_t ESQUINA_SUPERIOR_IZQUIERDA = CANT_CASILLEROS-TAMANIO_TABLERO;
    size_t ESQUINA_INFERIOR_DERECHA = TAMANIO_TABLERO- 1 ;

    size_t casilla_derecha = casilla+1;
    size_t casilla_izquierda = casilla-1;
    size_t casilla_arriba = casilla+TAMANIO_TABLERO;
    size_t casilla_abajo = casilla-TAMANIO_TABLERO;

    if( es_borde_derecho(casilla) ){ //BORDE DERECHO

        if( !es_posicion_pared(int(casilla_izquierda) ) ){

            conectar_casilleros(casilla,casilla_izquierda,peso);

        }

        if( !es_posicion_pared(int(casilla_abajo) ) ){

            conectar_casilleros(casilla,casilla_abajo,peso);

        }

        if( !es_posicion_pared(int(casilla_arriba) ) ){

            conectar_casilleros(casilla,casilla_arriba,peso);

        }

    } else if(es_borde_izquierdo(casilla) ){ //BORDE IZQUIERDO

        if( !es_posicion_pared(int(casilla_derecha) ) ){

            conectar_casilleros(casilla,casilla_derecha,peso);

        }

        if( !es_posicion_pared(int(casilla_abajo) ) ){

            conectar_casilleros(casilla,casilla_abajo,peso);

        }

        if( !es_posicion_pared(int(casilla_arriba) ) ){

            conectar_casilleros(casilla,casilla_arriba,peso);

        }

    } else if(casilla == ESQUINA_SUPERIOR_IZQUIERDA){ //ESQUINA IZQUIERDA SUPERIOR

        if( !es_posicion_pared(int(casilla_derecha) ) ){

            conectar_casilleros(casilla,casilla_derecha,peso);

        }

        if( !es_posicion_pared(int(casilla_abajo) ) ){

            conectar_casilleros(casilla,casilla_abajo,peso);

        }

    } else if( casilla == ESQUINA_INFERIOR_DERECHA){ //ESQUINA INFERIOR DERECHA

        if( !es_posicion_pared(int(casilla_izquierda) ) ){

            conectar_casilleros(casilla,casilla_izquierda,peso);

        }

        if( !es_posicion_pared(int(casilla_arriba) ) ){

            conectar_casilleros(casilla,casilla_arriba,peso);

        }

    } else if( casilla >= 1 && casilla<= (TAMANIO_TABLERO-2) ){ //BORDE DE ABAJO

        if( !es_posicion_pared(int(casilla_arriba) ) ){

            conectar_casilleros(casilla,casilla_arriba,peso);

        }

        if( !es_posicion_pared(int(casilla_izquierda) ) ){

            conectar_casilleros(casilla,casilla_izquierda,peso);

        }

        if( !es_posicion_pared(int(casilla_derecha) ) ){

            conectar_casilleros(casilla,casilla_derecha,peso);

        }

    } else if (casilla >= (CANT_CASILLEROS-(TAMANIO_TABLERO-1)) && casilla <= (CANT_CASILLEROS-2)){ //BORDE SUPERIOR

        if( !es_posicion_pared(int(casilla_izquierda) ) ){

            conectar_casilleros(casilla,casilla_izquierda,peso);

        }

        if( !es_posicion_pared(int(casilla_derecha) ) ){

            conectar_casilleros(casilla,casilla_derecha,peso);

        }

        if( !es_posicion_pared(int(casilla_abajo) ) ){

            conectar_casilleros(casilla,casilla_abajo,peso);

        }

    } else if(casilla == SALIDA){ //CASILLA DE SALIDA

        if( !es_posicion_pared(int(casilla_abajo) ) ){

            conectar_casilleros(casilla,casilla_abajo,peso);

        }

        if( !es_posicion_pared(int(casilla_izquierda) ) ){

            conectar_casilleros(casilla,casilla_izquierda,peso);

        }


    } else if(casilla == ENTRADA){ //CASILLA DE ENTRADA

        if( !es_posicion_pared(int(casilla_arriba) ) ){

            conectar_casilleros(casilla,casilla_arriba,peso);

        }

        if( !es_posicion_pared(int(casilla_derecha) ) ){

            conectar_casilleros(casilla,casilla_derecha,peso);

        }

    }else{ //No es ningun caso borde

        if( !es_posicion_pared(int(casilla_izquierda) ) ){

            conectar_casilleros(casilla,casilla_izquierda,peso);

        }

        if( !es_posicion_pared(int(casilla_derecha) ) ){

            conectar_casilleros(casilla,casilla_derecha,peso);

        }

        if( !es_posicion_pared(int(casilla_abajo) ) ){

            conectar_casilleros(casilla,casilla_abajo,peso);

        }

        if( !es_posicion_pared(int(casilla_arriba) ) ){

            conectar_casilleros(casilla,casilla_arriba,peso);

        }

    }

}

void Tablero::set_layout(int altura) {

    paredes = elegir_paredes(es_par(altura));

    for(size_t i = 0;i<paredes.size();i++){

        aislar_casilla(paredes[i]);

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

    size_t acumulador = TAMANIO_TABLERO - 1;
    std::vector<size_t> borde_derecho;
    bool devolver = false;

    for(size_t i = 0; i < TAMANIO_TABLERO-2;i++) {

        borde_derecho.push_back(acumulador + TAMANIO_TABLERO);
        acumulador+=TAMANIO_TABLERO;
    }

    size_t i = 0;
    while (i < borde_derecho.size() && !devolver){

        if (casilla == borde_derecho[i]){
            devolver = true;
        } else {
            i++;
        }

    }

    return devolver;
}

bool Tablero::es_borde_izquierdo(size_t casilla) {

    size_t acumulador = 0;
    std::vector<size_t> borde_izquierdo;
    bool devolver = false;

    for(size_t i = 0; i < TAMANIO_TABLERO-2;i++) {

        borde_izquierdo.push_back(acumulador+TAMANIO_TABLERO);
        acumulador+=TAMANIO_TABLERO;
    }

    size_t i =0;
    while ( i < borde_izquierdo.size() && !devolver){

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
    this->pos_entrada = ENTRADA;
    this->pos_salida = SALIDA;
    this->pos_jugador = ENTRADA;
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

    srand(static_cast<unsigned int>(time(0)));

    int primer_numero_aleatorio = 1 + (rand() % 2) ;
    int segundo_numero_aleatorio = 1 + (rand() % 2) ;
    
    if (primer_numero_aleatorio == 1) {
        int posicion_primer_pyramid = 1 + static_cast<int>(rand() % (CANT_CASILLEROS-1));
        while (es_posicion_pared(posicion_primer_pyramid)) {
            posicion_primer_pyramid = 1 + static_cast<int>(rand() % (CANT_CASILLEROS-1));
        }
        pos_pyramid[0] = posicion_primer_pyramid;
    }

    if (segundo_numero_aleatorio == 1) {
        int posicion_segundo_pyramid = 1 + static_cast<int>(rand() % (CANT_CASILLEROS-1));
        while ((es_posicion_pared(posicion_segundo_pyramid)) || (posicion_segundo_pyramid == pos_pyramid[0])) {
            posicion_segundo_pyramid = 1 + static_cast<int>(rand() % (CANT_CASILLEROS-1));
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

void Tablero::iniciar_tablero(int altura){
    pre_tablero();  //genera el tablero bruto con todas las aristas base
    restaurar_atributos();
    set_layout(altura); //ubica paredes
    crear_pyramid();// ubica los enemigos en el tablero.
}

void Tablero::zona_peligrosa(size_t casilla){
    
    const int DER=1; const int IZQ=-1; const int ARRIBA=9; const int ABAJO=-9;
    //Conecto todas las casillas adyacentes a piramid con el metodo conectar. //hablar con marian para sobrecargarlo
    //Luego aislo a pyramid.

    conectar_casilla(casilla+DER,FACTOR_RIESGO*PESO_BASE);
    conectar_casilla(casilla+IZQ,FACTOR_RIESGO*PESO_BASE);
    conectar_casilla(casilla+ARRIBA,FACTOR_RIESGO*PESO_BASE);
    conectar_casilla(casilla+ABAJO,FACTOR_RIESGO*PESO_BASE);

    peligrosas.push_back(casilla+DER);
    peligrosas.push_back(casilla+IZQ);
    peligrosas.push_back(casilla+ARRIBA);
    peligrosas.push_back(casilla+ABAJO);
    
    aislar_casilla(casilla);    //desconecto a pyramid del resto de casillas.
}

void Tablero::quitar_zona_peligrosa(size_t casilla){
    
    const int DER=1; const int IZQ=-1; const int ARRIBA=9; const int ABAJO=-9;

    conectar_casilla(casilla+DER, PESO_BASE);
    conectar_casilla(casilla+IZQ, PESO_BASE);
    conectar_casilla(casilla+ARRIBA, PESO_BASE);
    conectar_casilla(casilla+ABAJO, PESO_BASE);  //casillas aledanias a piramid restituidas

    conectar_casilla(casilla, PESO_BASE);  //reconecta a piramid/*/
}

void Tablero::modificar_tablero(bool arma){
    if (arma){
        for (size_t i=0; i<pos_pyramid.size();i++){
            quitar_zona_peligrosa(pos_pyramid[i]);
            }
        peligrosas={};  //cuando termina de quitar las casillas peligrosas, setea el atributo a vector vacio.
    }
    else{
        for (size_t i=0; i<pos_pyramid.size();i++){ 
            zona_peligrosa(pos_pyramid[i]); // las casillas alrededor de c/pyramid se marcan peligrosas.
        }        
    }
}

int Tablero::actualizar_posicion(int comando){   

    /*No necesito verificar paredes o bordes. Si no se puede pasar, el camino sera un vector vacio.Pues: 
    Caso Pared: "Dijkstra::obtener_camino" retornara un vector vacio, pues arista=INFINITO.
    Caso borde del layout: el vertice pos_destino no es valido en el borde inferior o superior,
    asique Grafo::obtener_camino_minimo retorna vacio. En los bordes laterales, izquierdo o derecho,
    para ir, por ejde :9->8 o 17->18 no estan conectados, entonces idem caso pared. Arista=INFINITO. 
    Caso pyramid sin arma: IDEM caso Pared:retorna vector vacio, pues arista=INFINITO.*/

    layout->usar_dijkstra();
    std::pair<std::vector<size_t>, int> movimiento;
    size_t pos_destino = static_cast <size_t> (pos_jugador+comando);    
    movimiento=layout->obtener_camino_minimo(pos_jugador,pos_destino); //el movimiento es de donde a donde y cuanto cuesta

    if (movimiento.first.empty()){
        std::cout << "No puedes moverte hacia alla!\n";   
    }
    else
        pos_jugador=movimiento.first[movimiento.first.size()-1];

    bool es_peligrosa=false;
    size_t i=0;
    while(!es_peligrosa && i<peligrosas.size()){
        if (pos_destino==peligrosas[i])
            es_peligrosa=true;
    }
    
    if (!es_peligrosa)
        return (movimiento.second);
    else
        return (movimiento.second-4*PESO_BASE);
}

void Tablero::conectar_casilleros(size_t casilla, size_t casilla_a_conectar, int peso) {
    layout->cambiar_arista(casilla,casilla_a_conectar,peso);
    layout->cambiar_arista(casilla_a_conectar,casilla,peso);
}

void Tablero::restaurar_atributos() {

    this->pos_pyramid = {-1,-1};
    this->pos_jugador = ENTRADA;

}

bool Tablero::es_posicion_final() {

    return pos_jugador == SALIDA;
}

bool Tablero::es_posicion_pyramid() {
    bool devolver = false;

    while(size_t i = 0 < pos_pyramid.size() && !devolver){

        if(pos_pyramid[i] == static_cast<int>(pos_jugador)){

            devolver = true;

        }

        i++;

    }
    return devolver;
}
