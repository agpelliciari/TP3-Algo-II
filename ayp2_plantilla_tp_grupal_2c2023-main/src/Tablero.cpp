#include "Tablero.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Constantes.hpp"

using namespace std;


Tablero::Tablero() {
    this->layout = new Grafo(CANT_CASILLEROS);
    this->pos_pyramid = {-1,-1};
    this->pos_entrada = ENTRADA;
    this->pos_salida = SALIDA;
    this->pos_jugador = ENTRADA;
}



void Tablero::conectar_casilla(size_t casilla, int peso, bool bidireccional) {

    size_t ESQUINA_SUPERIOR_IZQUIERDA = CANT_CASILLEROS-TAMANIO_TABLERO;
    size_t ESQUINA_INFERIOR_DERECHA = TAMANIO_TABLERO- 1 ;

    size_t casilla_derecha = casilla+1;
    size_t casilla_izquierda = casilla-1;
    size_t casilla_arriba = casilla+TAMANIO_TABLERO;
    size_t casilla_abajo = casilla-TAMANIO_TABLERO;

    if(casilla < ENTRADA || casilla >(CANT_CASILLEROS-1)){

        return;

    }
    else if( es_borde_derecho(casilla) ){ //BORDE DERECHO

        if( !es_posicion_pared(int(casilla_izquierda) ) ){

            conectar_casilleros(casilla,casilla_izquierda,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_abajo) ) ){

            conectar_casilleros(casilla,casilla_abajo,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_arriba) ) ){

            conectar_casilleros(casilla,casilla_arriba,peso, bidireccional);

        }

    } else if(es_borde_izquierdo(casilla) ){ //BORDE IZQUIERDO

        if( !es_posicion_pared(int(casilla_derecha) ) ){

            conectar_casilleros(casilla,casilla_derecha,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_abajo) ) ){

            conectar_casilleros(casilla,casilla_abajo,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_arriba) ) ){

            conectar_casilleros(casilla,casilla_arriba,peso, bidireccional);

        }

    } else if(casilla == ESQUINA_SUPERIOR_IZQUIERDA){ //ESQUINA IZQUIERDA SUPERIOR

        if( !es_posicion_pared(int(casilla_derecha) ) ){

            conectar_casilleros(casilla,casilla_derecha,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_abajo) ) ){

            conectar_casilleros(casilla,casilla_abajo,peso, bidireccional);

        }

    } else if( casilla == ESQUINA_INFERIOR_DERECHA){ //ESQUINA INFERIOR DERECHA

        if( !es_posicion_pared(int(casilla_izquierda) ) ){

            conectar_casilleros(casilla,casilla_izquierda,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_arriba) ) ){

            conectar_casilleros(casilla,casilla_arriba,peso, bidireccional);

        }

    } else if( es_borde_inferior(casilla) ){ //BORDE DE ABAJO
        
        if( !es_posicion_pared(int(casilla_arriba) ) ){

            conectar_casilleros(casilla,casilla_arriba,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_izquierda) ) ){

            conectar_casilleros(casilla,casilla_izquierda,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_derecha) ) ){

            conectar_casilleros(casilla,casilla_derecha,peso, bidireccional);

        }

    } else if (es_borde_derecho(casilla)){ //BORDE SUPERIOR
        
        if( !es_posicion_pared(int(casilla_izquierda) ) ){

            conectar_casilleros(casilla,casilla_izquierda,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_derecha) ) ){

            conectar_casilleros(casilla,casilla_derecha,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_abajo) ) ){

            conectar_casilleros(casilla,casilla_abajo,peso, bidireccional);

        }

    } else if(casilla == SALIDA){ //CASILLA DE SALIDA

        if( !es_posicion_pared(int(casilla_abajo) ) ){

            conectar_casilleros(casilla,casilla_abajo,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_izquierda) ) ){

            conectar_casilleros(casilla,casilla_izquierda,peso, bidireccional);

        }


    } else if(casilla == ENTRADA){ //CASILLA DE ENTRADA

        if( !es_posicion_pared(int(casilla_arriba) ) ){

            conectar_casilleros(casilla,casilla_arriba,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_derecha) ) ){

            conectar_casilleros(casilla,casilla_derecha,peso, bidireccional);

        }

    }else{ //No es ningun caso borde

        if( !es_posicion_pared(int(casilla_izquierda) ) ){

            conectar_casilleros(casilla,casilla_izquierda,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_derecha) ) ){

            conectar_casilleros(casilla,casilla_derecha,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_abajo) ) ){

            conectar_casilleros(casilla,casilla_abajo,peso, bidireccional);

        }

        if( !es_posicion_pared(int(casilla_arriba) ) ){

            conectar_casilleros(casilla,casilla_arriba,peso, bidireccional);

        }

    }

}

void Tablero::set_layout(int altura) {

    paredes = elegir_paredes(es_par(static_cast<size_t>(altura)));

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


    } else if ((posicion >= (CANT_CASILLEROS - TAMANIO_TABLERO)) && (posicion < CANT_CASILLEROS)) {

        this->layout->eliminar_arista(posicion, posicion + 1);
        this->layout->eliminar_arista(posicion + 1, posicion);

        this->layout->eliminar_arista(posicion, posicion - 1);
        this->layout->eliminar_arista(posicion - 1, posicion);

        this->layout->eliminar_arista(posicion, posicion - TAMANIO_TABLERO);
        this->layout->eliminar_arista(posicion - TAMANIO_TABLERO, posicion);

    } else {

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
    size_t i = 0;
    while (i < paredes.size() && !es_pared) {
        if (paredes[i] == (size_t) posicion) {
            es_pared = true;
        }
        i++;
    }

    return es_pared;
}

void Tablero::crear_pyramid() {

    srand(static_cast<unsigned int>(time(0)));

    int primer_numero_aleatorio = 1 + (rand() % 2) ;
    int segundo_numero_aleatorio = 1 + (rand() % 2) ;
    
    if (primer_numero_aleatorio == 1) {
        int posicion_primer_pyramid = 1 + static_cast<int>(static_cast<size_t>(rand()) % (CANT_CASILLEROS - 2));
        while (es_posicion_pared(posicion_primer_pyramid)) {
            posicion_primer_pyramid = 1 + static_cast<int>(static_cast<size_t>(rand()) % (CANT_CASILLEROS - 2));
        }
        pos_pyramid[0] = posicion_primer_pyramid;
    }

    if (segundo_numero_aleatorio == 1) {
        int posicion_segundo_pyramid = 1 + static_cast<int>(static_cast<size_t>(rand()) % (CANT_CASILLEROS - 2));
        while ((es_posicion_pared(posicion_segundo_pyramid)) || (posicion_segundo_pyramid == pos_pyramid[0])) {
            posicion_segundo_pyramid = 1 + static_cast<int>(static_cast<size_t>(rand()) % (CANT_CASILLEROS - 2));
        }
        pos_pyramid[1] = posicion_segundo_pyramid;
    }

    if (pos_pyramid[0] != (-1)) {

        zona_peligrosa((size_t) pos_pyramid[0]);

    }

    if (pos_pyramid[1] != (-1)) {

        zona_peligrosa((size_t) pos_pyramid[1]);

    }

}

void Tablero::iniciar_tablero(int altura){
    cout<<"Generando tablero.."<<endl;
    pre_tablero();  //genera el tablero bruto con todas las aristas base
    cout<<"Restaurando Atributos.."<<endl;
    restaurar_atributos();
    cout<<"Ubicando Paredes.."<<endl;
    set_layout(altura); //ubica paredes
    cout<<"Ubicando pyramids.."<<endl;
    crear_pyramid();// ubica los enemigos en el tablero.
    cout<<"Arranca el juego.."<<endl;
}

void Tablero::zona_peligrosa(size_t casilla){
    //Conecto todas las casillas adyacentes a piramid con el metodo conectar.
    //Luego aislo a pyramid.

    if (!es_posicion_pared(static_cast<int>(casilla + MOVERSE_DERECHA)) && !es_zona_peligrosa(casilla + MOVERSE_DERECHA) && !es_borde_derecho(casilla)){   //Casilla Derecha a pyramid

        conectar_casilla(casilla + MOVERSE_DERECHA, FACTOR_RIESGO * PESO_BASE, true);
        conectar_casilla((casilla + MOVERSE_DERECHA), PESO_BASE, false);
        peligrosas.push_back(casilla + MOVERSE_DERECHA);

    }

    if (!es_posicion_pared(static_cast<int>(casilla + (size_t) MOVERSE_IZQUIERDA)) && !es_zona_peligrosa(casilla + (size_t) MOVERSE_IZQUIERDA) && !es_borde_izquierdo(casilla)){ //Casilla Izq a pyramid
        conectar_casilla(casilla + (size_t) MOVERSE_IZQUIERDA, FACTOR_RIESGO * PESO_BASE, true);
        conectar_casilla((casilla + (size_t) MOVERSE_IZQUIERDA), PESO_BASE, false);
        peligrosas.push_back(casilla + (size_t) MOVERSE_IZQUIERDA);

    }

    if (!es_posicion_pared(static_cast<int>(casilla + MOVERSE_ARRIBA)) && !es_zona_peligrosa(casilla + MOVERSE_ARRIBA) && !es_borde_superior(casilla)){ //Casilla arriba a pyramid
        conectar_casilla(casilla + MOVERSE_ARRIBA, FACTOR_RIESGO * PESO_BASE, true);
        conectar_casilla((casilla + MOVERSE_ARRIBA), PESO_BASE, false);
        peligrosas.push_back(casilla + MOVERSE_ARRIBA);

    }

    if (!es_posicion_pared(static_cast<int>(casilla + (size_t) MOVERSE_ABAJO)) && !es_zona_peligrosa(casilla +
                                                                                                     (size_t) MOVERSE_ABAJO) && !es_borde_inferior(casilla)){ //Casilla abajo a pyramid
        conectar_casilla(casilla + (size_t) MOVERSE_ABAJO, FACTOR_RIESGO * PESO_BASE, true);
        conectar_casilla((casilla + (size_t) MOVERSE_ABAJO), PESO_BASE, false);
        peligrosas.push_back(casilla + (size_t) MOVERSE_ABAJO);

    }

    aislar_casilla(casilla);    //desconecto a pyramid del resto de casillas.
}

void Tablero::quitar_zona_peligrosa(size_t casilla){
    

    for(size_t i = 0; i< peligrosas.size();i++){

        conectar_casilla(peligrosas[i],PESO_BASE, true);

    }

    conectar_casilla(casilla, PESO_BASE, true);  //reconecta a piramid
}

void Tablero::modificar_tablero(bool arma){

    if (arma){

        for (size_t i=0; i<pos_pyramid.size();i++){
            if (pos_pyramid[i]!=-1)
                quitar_zona_peligrosa(static_cast<size_t>(pos_pyramid[i]));
            }
        peligrosas={};  //cuando termina de quitar las peligrosas, setea el atributo a vector vacio.
    }
    else{

        for (size_t i=0; i<pos_pyramid.size();i++){
            if (pos_pyramid[i]!=-1){
                zona_peligrosa(static_cast<size_t>(pos_pyramid[i])); // las casillas alrededor de c/pyramid se marcan peligrosas.
            }        
        }
    }
}

int Tablero::actualizar_posicion(int comando){   

    size_t ESQUINA_SUPERIOR_IZQUIERDA = CANT_CASILLEROS-TAMANIO_TABLERO;
    size_t ESQUINA_INFERIOR_DERECHA = TAMANIO_TABLERO- 1 ;

    /*No necesito verificar paredes o bordes. Si no se puede pasar, el camino sera un vector vacio.Pues:
    Caso Pared: "Dijkstra::obtener_camino" retornara un vector vacio, pues arista=INFINITO.
    Caso borde del layout: el vertice pos_destino no es valido en el borde inferior o superior,
    asique Grafo::obtener_camino_minimo retorna vacio. En los bordes laterales, izquierdo o derecho,
    para ir, por ejde :9->8 o 17->18 no estan conectados, entonces idem caso pared. Arista=INFINITO.
    Caso pyramid sin arma: IDEM caso Pared:retorna vector vacio, pues arista=INFINITO.*/

    layout->usar_dijkstra();
    std::pair<std::vector<size_t>, int> movimiento;
    size_t pos_destino = static_cast <size_t> (pos_jugador + static_cast<size_t>(comando));

    if(comando == MOVERSE_ARRIBA && (es_borde_superior(pos_jugador) || pos_jugador == ESQUINA_SUPERIOR_IZQUIERDA) ){

        std::cout << "No puedes moverte hacia alla!"<< endl;
        return 0;

    } else if(comando == MOVERSE_ABAJO && (es_borde_inferior(pos_jugador) || pos_jugador == ESQUINA_INFERIOR_DERECHA || pos_jugador == pos_entrada) ){

        std::cout << "No puedes moverte hacia alla!"<< endl;
        return 0;

    } else if(comando == MOVERSE_DERECHA && (es_borde_derecho(pos_jugador) || pos_jugador == ESQUINA_INFERIOR_DERECHA)){

        std::cout << "No puedes moverte hacia alla!"<< endl;
        return 0;

    } else if(comando == MOVERSE_IZQUIERDA && (es_borde_izquierdo(pos_jugador) || pos_jugador == ESQUINA_SUPERIOR_IZQUIERDA || pos_jugador == pos_entrada)){

        std::cout << "No puedes moverte hacia alla!"<< endl;
        return 0;

    }

    movimiento=layout->obtener_camino_minimo(pos_jugador,pos_destino); //el movimiento es de donde a donde y cuanto cuesta

    if (movimiento.first.empty()){
        std::cout << "No puedes moverte hacia alla!\n";
    }
    else{
        pos_jugador=movimiento.first[movimiento.first.size()-1];
    }

    bool es_peligrosa=false;
    size_t i=0;
    while(!es_peligrosa && i<peligrosas.size()){
        if (pos_destino==peligrosas[i])
            es_peligrosa=true;
        i++;
    }

    return movimiento.second;

    }

void Tablero::conectar_casilleros(size_t casilla, size_t casilla_a_conectar, int peso, bool bidireccional) {
    if(bidireccional){

        if(!es_posicion_pared(int(casilla_a_conectar)) && (casilla_a_conectar >= ENTRADA && casilla_a_conectar < (CANT_CASILLEROS-1)) ){
            layout->cambiar_arista(casilla,casilla_a_conectar,peso);
            layout->cambiar_arista(casilla_a_conectar,casilla,peso);
        }

    } else{

        if(!es_posicion_pared(int(casilla_a_conectar)) && !es_zona_peligrosa(casilla_a_conectar) && (casilla_a_conectar >= ENTRADA && casilla_a_conectar < (CANT_CASILLEROS-1))){ //corregir

            layout->cambiar_arista(casilla,casilla_a_conectar,peso);

        }

    }
}

void Tablero::restaurar_atributos() {

    this->pos_pyramid = {-1,-1};
    this->pos_jugador = ENTRADA;
    this->peligrosas={};

}

bool Tablero::es_posicion_final() {

    return pos_jugador == SALIDA;
}

bool Tablero::es_matar_pyramid() {
    bool devolver = false;
    size_t i = 0;
    while( i < pos_pyramid.size() && !devolver){

        if(pos_pyramid[i] == static_cast<int>(pos_jugador)){
            eliminar_pyramid(static_cast<int>(i));
            devolver = true;
        }

        i++;

    }
    return devolver;
}

bool Tablero::es_zona_peligrosa(size_t casilla){
     bool devolver = false;
     size_t i = 0;
     while( i < peligrosas.size() && !devolver){

         if(peligrosas[i] == casilla){

             devolver = true;

         }

         i++;

     }
     return devolver;
}

bool Tablero::es_borde_superior(size_t casilla){

    return casilla >= (CANT_CASILLEROS-(TAMANIO_TABLERO-1)) && casilla <= (CANT_CASILLEROS-2);
}

bool Tablero::es_borde_inferior(size_t casilla){

    return casilla >= 1 && casilla<= (TAMANIO_TABLERO-2);
}

void Tablero::eliminar_pyramid(int indice){
    pos_pyramid[size_t(indice)]=-1;
}

void Tablero::establecer_matriz_tablero() {

    this->matriz_tablero = Matriz(TAMANIO_TABLERO);

    // Agrego las paredes a la matriz_tablero.

    size_t posicion_i ;
    size_t posicion_j ;

    for (size_t iterador = 0; iterador < paredes.size(); iterador++) {

        posicion_i = (paredes[iterador]) / (TAMANIO_TABLERO);
        posicion_j = (paredes[iterador]) % (TAMANIO_TABLERO);

        matriz_tablero.elemento(posicion_i, posicion_j) = 1;
        
    }

    // Agrego los pyramid head a la matriz_tablero.

    for (size_t iterador = 0; iterador < pos_pyramid.size(); iterador++) {

        if (pos_pyramid[iterador] != -1) {

            posicion_i = (static_cast<size_t>(pos_pyramid[iterador])) / (TAMANIO_TABLERO);
            posicion_j = (static_cast<size_t>(pos_pyramid[iterador])) % (TAMANIO_TABLERO);

            matriz_tablero.elemento(posicion_i, posicion_j) = -1;
        }
    }

    // Agrego la SALIDA a la matriz_tablero.

    posicion_i = SALIDA / TAMANIO_TABLERO;
    posicion_j = SALIDA % TAMANIO_TABLERO;
    matriz_tablero.elemento(posicion_i, posicion_j) = (int) SALIDA;

    // Agrego la posicion del jugador a la matriz_tablero.

    posicion_i = pos_jugador / TAMANIO_TABLERO;
    posicion_j = pos_jugador % TAMANIO_TABLERO;
    matriz_tablero.elemento(posicion_i, posicion_j) = 99;

}

void Tablero::mostrar_matriz_tablero() {

    establecer_matriz_tablero();

    for (int i = (((int)TAMANIO_TABLERO)-1); i >= 0; i--) {

        for (size_t j = 0; j < TAMANIO_TABLERO; j++) {

            if (matriz_tablero.elemento((size_t)i, j) == 99) {
                std::cout << ROJO_EMOJI;
            }
            else if (matriz_tablero.elemento((size_t)i, j) == -1) {
                std::cout << NEGRO_EMOJI;
            }
            else if (matriz_tablero.elemento((size_t)i, j) == 0) {
                std::cout << BLANCO_EMOJI;
            }
            else if (matriz_tablero.elemento((size_t)i, j) == 1) {
                std::cout << LADRILLO_EMOJI;
            }
            else if (matriz_tablero.elemento((size_t)i, j) == (int) SALIDA) {
                std::cout << SALIDA_EMOJI;
            }
        }

        std::cout << "\n";

    }

}

bool Tablero::esta_pyramid(size_t casilla) {

    return int(casilla) == pos_pyramid[1] || int(casilla) == pos_pyramid[0];

}

Tablero::~Tablero(){

    delete layout;

}