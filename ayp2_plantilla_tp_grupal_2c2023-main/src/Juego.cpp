#include "Juego.hpp"

Juego::Juego(){
    costo_total_movimientos = 0;
    nivel = 0;
    partida_en_curso = false;
}

void Juego::condiciones_iniciales(){
    nivel = PRIMER_NIVEL;
    partida_en_curso = true;

    generar_arma_aleatoria();

}

void Juego::nueva_partida(){
    condiciones_iniciales();
    nuevo_tablero();
    partida();
}

void Juego::generar_placa_aleatoria(){
    arbol_placas.agregar_placa_aleatoria();
}

void Juego::generar_arma_aleatoria(){
    inventario.agregar_arma_aleatoria();
}

void Juego::romper_arma(){
    inventario.desequipar_arma();
    inventario.baja();
}

void Juego::nuevo_nivel(){
    nivel++;

    generar_placa_aleatoria();

    int numero_aleatorio = rand() % PORCENTAJE_MAXIMO;
    if (numero_aleatorio <= PROBABILIDAD)
    {
        generar_arma_aleatoria();
    }

    cout << "Cargando nivel " << nivel << " ..." << endl;
    
    nuevo_tablero();
}

void Juego::nuevo_tablero(){
    int altura = arbol_placas.altura_arbol_placas();
    tablero_juego.iniciar_tablero(altura);
}

void Juego::inicializar_juego(){
    nueva_partida();
}

void Juego::partida(){
    string opcion, opcionValida;
    cout << "Cargando nivel " << nivel << " ..." << endl;
    do
    {
        // tablero_juego.imprimir_tablero();

        menu_juego.imprimir_menu_juego();

        opcionValida = menu_juego.recibir_opcion_juego(opcion);

        if (opcionValida == MOVERSE_EN_EL_TABLERO){
            moverse_en_tablero();
        }
        else if (opcionValida == MOSTRAR_CAMINO_MINIMO){
            imprimir_camino_minimo();
        }
        else if (opcionValida == USAR_CAMINO_MINIMO){
            usar_camino_minimo();
        }
        else if (opcionValida == EQUIPAR_DESEQUIPAR_ARMA){
            equipar_o_desequipar_arma();
            tablero_juego.modificar_tablero(inventario.arma_equipada());
        }
        else if (opcionValida == MOSTRAR_PUNTAJE){
            imprimir_puntaje_total();
        }

    } while ((opcionValida != SALIR) && (nivel <= ULTIMO_NIVEL) && (partida_en_curso));
}

void Juego::moverse_en_tablero(){
    int costo_movimiento;
    string direccion;

    cout << "Para que direccion desea moverse? (W/A/S/D): " << endl;
    cin >> direccion;
    transform(direccion.begin(), direccion.end(), direccion.begin(), ::toupper);
        
    if (direccion == ARRIBA) {
        costo_movimiento = tablero_juego.actualizar_posicion(MOVERSE_ARRIBA);
    }
    else if (direccion == ABAJO) {
        costo_movimiento = tablero_juego.actualizar_posicion(MOVERSE_ABAJO);
    }
    else if (direccion == IZQUIERDA) {
        costo_movimiento = tablero_juego.actualizar_posicion(MOVERSE_IZQUIERDA);
    }
    else if (direccion == DERECHA) {
        costo_movimiento = tablero_juego.actualizar_posicion(MOVERSE_DERECHA);
    }
        
    costo_total_movimientos += costo_movimiento;

    if (tablero_juego.es_posicion_final())
    {
        if (nivel == ULTIMO_NIVEL)
        {
            partida_en_curso = false;
            cout << "Felicitaciones! a completado todos los niveles. El costo total para llegar al final que necesito fueron: " << costo_total_movimientos << " PUNTOS" << endl;
        }
        else
        {
            nuevo_nivel();
        }
    }

    if (tablero_juego.es_posicion_pyramid())
    {
        romper_arma();
    }
}

void Juego::imprimir_camino_minimo(){
    pair tupla = tablero_juego.camino_automatico();

    vector<size_t> posiciones_camino_minimo = tupla.first;
    int costo_camino_minimo = tupla.second;

    cout << "Direcciones del camino minimo para completar el nivel " << nivel << ": ";

    for (size_t i = 0; i < posiciones_camino_minimo.size(); i++)
    {
        cout << posiciones_camino_minimo[i] << ", ";
    }
    cout << endl;

    cout << "El costo de estos movimientos es: " << costo_camino_minimo << endl;
}

void Juego::usar_camino_minimo(){
    pair tupla = tablero_juego.camino_automatico();

    vector<size_t> posiciones_camino_minimo = tupla.first;
    int costo_camino_minimo = tupla.second;

    if (posiciones_camino_minimo.empty())
    {
        partida_en_curso = false;
        cout << "No hay caminos minimos disponibles, finaliza la partida." << endl;
    }
    else
    {
        if (nivel == ULTIMO_NIVEL)
        {
            partida_en_curso = false;
            cout << "Felicitaciones! a completado todos los niveles. El costo total para llegar al final que necesito fueron: " << costo_total_movimientos << " PUNTOS" << endl;
        }
        else
        {
            costo_total_movimientos += costo_camino_minimo;
            nuevo_nivel();
        }
    }
}

void Juego::equipar_o_desequipar_arma(){
    
    string respuesta;
	cout << "Deseas equipar o desequipar un arma?" << endl;
    cin >> respuesta;
    transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);

    if (respuesta.find(DESEQUIPAR) != string::npos)
    {
		inventario.desequipar_arma();
    }
    else
    {
        cout << "Deseas equipar el arma con menor potencia? (s/n)" << endl;
        cin >> respuesta;
        transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);
        if (respuesta.find(CONFIRMACION) != string::npos){
            inventario.activar_modo_ahorro();
        }
    
        inventario.consulta();
    }
}

void Juego::imprimir_puntaje_total(){
    cout << "El puntaje actual acumulado hasta el momento es: " << costo_total_movimientos << " PUNTOS" << endl;
}

Juego::~Juego(){}