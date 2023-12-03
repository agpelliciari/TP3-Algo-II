#include "Tablero.hpp"
#include <iostream>

void Tablero::conectar_casilla(size_t casilla,int peso) {
    //PASS
}

void Tablero::iniciar_tablero(int altura){
    pre_tablero();  //genera el tablero bruto con todas las aristas base
    set_layout(altura); //ubica paredes
    crear_pyramid(); // ubica los enemigos en el tablero.
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

    conectar_casilla(casilla+DER);
    conectar_casilla(casilla+IZQ);
    conectar_casilla(casilla+ARRIBA);
    conectar_casilla(casilla+ABAJO);  //casillas aledanias a piramid restituidas

    conectar_casilla(casilla);  //reconecta a piramid
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
    for (size_t i=0; i<peligrosas.size();i++)
        if (pos_destino==peligrosas[i])
            es_peligrosa=true;

    if (!es_peligrosa)
        return (movimiento.second);
    else
        return (movimiento.second-4*PESO_BASE);
}