#include "Inventario_de_Armas.hpp"
#include "Arma.hpp"

Inventario_de_Armas::Inventario_de_Armas(){
    this->ahorro_municion=false;
    this->arma_actual=ARMA_DEFAULT;
}

void Inventario_de_Armas::consulta(){
    if (armas_rapidas.vacio()){
        cout << "No hay mas armas! Solo te queda defenderte con tus propios puños."<<endl;
    }
    else{
        string respuesta;
        Arma arma_rapida;
        arma_rapida=armas_rapidas.primero();
        cout << "Deseas equipar el " << arma_rapida <<"? (s/n)"<<endl;
        cin >> respuesta;
        transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);
        if (respuesta.find(CONFIRMACION) != string::npos)
            cambiar_arma();
    } 
}

void Inventario_de_Armas::cambiar_arma(){
    Arma guardada=arma_actual;
    arma_actual=armas_rapidas.baja();
    if (!(guardada==ARMA_DEFAULT))  //Aca lo que chequeo es q no este guardando los puños en el inventario.
        armas_rapidas.alta(guardada);
}

void Inventario_de_Armas::alta() {
    std::string nombre; 
    size_t potencia;

    cout << "Que arma deseas guardar?" << endl;
    cin >> nombre;
    cin.ignore();
    cout << "Tu conocimiento de armas te permite estimar su potencia." << endl;
    std::string input;
    bool entradaValida = false;
    do {
        std::getline(std::cin, input);
        std::istringstream stream(input);
        if (stream >> potencia) {
            char caracter;
            if (!(stream >> caracter)) {
                entradaValida = true;
            } else {
                std::cout << "Ingresa un valor numérico válido." << std::endl;
            }
        } else {
            std::cout << "Ingresa un valor numérico válido." << std::endl;
        }
    } while (!entradaValida);

    Arma nueva_arma(nombre, potencia);
    cout << "Objeto recogido!" << endl;
    armas_rapidas.alta(nueva_arma);

    if (ahorro_municion) {          //Esto es para q se reorganice usando modo ahorro.
        armas_rapidas.heapsort();
    }
}

void Inventario_de_Armas::baja(){
    if (armas_rapidas.vacio()){
        cout <<"No quedan mas armas que descartar!!"<<endl;
    }
    else{
        Arma arma_descartada=armas_rapidas.baja();
        cout <<"Has descartado el:"<<arma_descartada;
        if (ahorro_municion){
            armas_rapidas.heapsort();
        }
    }
}
void Inventario_de_Armas::activar_modo_ahorro(){
    if (!armas_rapidas.vacio()){
        if (!ahorro_municion){
            ahorro_municion=true;
            armas_rapidas.heapsort(); //aca reordeno de menor a mayor, para q ahora seleccione el peor arma primero.
            cout <<"Ahorro de municion activado, equiparas las armas menos potentes primero."<<endl;
        }
        else
            cout << "El ahorro de municion ya esta activado.";
    }
    else
        cout <<"No hay armas que gestionar!!";
}
void Inventario_de_Armas::desactivar_modo_ahorro(){
    if (!armas_rapidas.vacio()){
        if (ahorro_municion){
            ahorro_municion=false;
            for (size_t i = (armas_rapidas.tamanio() / 2) - 1; i != SIZE_MAX; i--){
                armas_rapidas.rearmar_heap(armas_rapidas.tamanio(),i);
            }
            cout<<"Ahorro de municion desactivado, hora de la artilleria pesada."<<endl;
        }
        else
            cout<<"El modo ahorro no esta activo!."<<endl;
    }
    else{
        cout <<"No hay armas que gestionar!!";
    }
}

bool Inventario_de_Armas::arma_equipada(){
    return !(arma_actual ==  ARMA_DEFAULT);
}

void Inventario_de_Armas::desequipar_arma(){
    if (!(arma_equipada())){
        cout << "No tiene un arma equipada." << endl;
    }
    else
    {
        armas_rapidas.alta(arma_actual);
        arma_actual = ARMA_DEFAULT;
    }
}

void Inventario_de_Armas::agregar_arma_aleatoria(){
    vector<string> vec_armas = {"Espada", "Arco", "Hacha", "Ballesta", "Daga", "Lanza", "Pistola", "Rifle", "Escopeta", "Subfusil", "Ametralladora"};
    srand(static_cast<unsigned int>(time(0)));
    int indice_aleatorio = rand() % (static_cast<int>(vec_armas.size()));
    string nombre_aleatorio = vec_armas[indice_aleatorio];

    size_t potencia_aleatoria = rand() % POTENCIA_MAX;

    Arma arma_aleatoria(nombre_aleatorio, potencia_aleatoria);
    
    armas_rapidas.alta(arma_aleatoria);
}

Inventario_de_Armas::~Inventario_de_Armas(){}
