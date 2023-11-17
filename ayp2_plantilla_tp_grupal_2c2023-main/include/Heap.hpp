#ifndef ALGO2_TP3_PT2_HEAP_H
#define ALGO2_TP3_PT2_HEAP_H

#include <vector>
#include <cstdlib>
#include <exception>

#define POSICION_INVALIDA (size_t)(-1)

class Heap_exception : public std::exception {
};

template<typename T, bool comp(T, T)>
class Heap {
private:
    std::vector<T> datos;

    // Pre: Ambos índices deben ser menor que la cantidad de datos.
    // Post: Intercambia de lugar los datos de los indices indicados.
    void swap(size_t index_1, size_t index_2);

    // Pre: Ambos índices deben ser menor que la cantidad de datos.
    // Post: Realiza un "upheap" sobre los índices indicados.
    // (El dato "sube" en el heap.)
    void upheap(size_t& index_insertado, size_t index_padre);

    // Post: El índice debe ser menor que la cantidad de datos.
    // Post: Realiza un "downheap" sobre el índice indicado.
    // (El dato "baja" en el heap, intercambiándose con el menor/mayor dato.)
    void downheap(size_t& index_movido);
    
    // Pre: Si el indice es igual a 0 el elemento no tiene padre
    // Post: Devuelve la posicion del padre del  elemento con el indice pasado por parametro.
    size_t obtener_posicion_padre(size_t indice);

    // Pre: Si el indice es mayor a el tamaño logico del vector, el elemento no tiene hijo izquierdo.
    // Post: Devuelve la posicion del hijo izquierdo del elemento con el indice pasado por parametro.
    size_t obtener_posicion_hijo_izquierdo(size_t indice);

    // Pre: Si el indice es mayor a el tamaño logico del vector, el elemento no tiene hijo derecho.
    // Post: Devuelve la posicion del hijo derecho del elemento con el indice pasado por parametro.
    size_t obtener_posicion_hijo_derecho(size_t indice);

    // Pre: -
    // Post: Devuelve la posicion del elemento mayor entre los indices pasados por parametro.
    size_t obtener_posicion_dato_mayor(size_t indice_izq, size_t indice_der);

    // NOTA: No es necesario que lancen excepciones en estos métodos porque son privados.
    // Deberian siempre asegurar que los indices pasados por parámetros son válidos.
    // Consideren cada caso con detenimiento.
    // Adicionalmente, tengan cuidado con el casteo de las variables, porque son size_t.
    // Hacer, por ejemplo, size_t i = 0; i - 1; produce un underflow.
public:
    // Constructor.
    Heap();

    // Pre: -
    // Post: Agrega el dato al Heap.
    void alta(T dato);

    // Pre: El heap no puede estar vacío.
    // Post: Elimina y devuelve el primer dato.
    T baja();

    // Pre: El heap no puede estar vacío.
    // Post: Devuelve el primer dato.
    T primero();

    // Pre: -
    // Post: Devuelve true si el heap está vacío.
    bool vacio();

    // Pre: -
    // Post: Devuelve la cantidad de datos en el heap.
    size_t tamanio();

    // El constructor de copia está deshabilitado.
    Heap(const Heap& heap) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const Heap& heap) = delete;

    // Destructor.
    ~Heap();
};

template<typename T, bool comp(T, T)>
Heap<T, comp>::Heap(){
    this->datos = datos;
}

template<typename T, bool comp(T, T)>
void Heap<T, comp>::alta(T dato){
    datos.push_back(dato);
    if (!vacio())
    {
        size_t posicion_nuevo_elemento = tamanio() - 1;
        size_t posicion_padre_nuevo_elemento = obtener_posicion_padre(posicion_nuevo_elemento);
        while ((datos[posicion_nuevo_elemento] > datos[posicion_padre_nuevo_elemento]) && (posicion_padre_nuevo_elemento != POSICION_INVALIDA) ){
            upheap(posicion_nuevo_elemento, posicion_padre_nuevo_elemento);
            posicion_nuevo_elemento = posicion_padre_nuevo_elemento;
            posicion_padre_nuevo_elemento = obtener_posicion_padre(posicion_nuevo_elemento);
        }
    }
}

template<typename T, bool comp(T, T)>
void Heap<T, comp>::upheap(size_t &index_insertado, size_t index_padre) {
    swap(index_insertado, index_padre);
}

template<typename T, bool comp(T, T)>
size_t Heap<T, comp>::obtener_posicion_padre(size_t indice) {
    if (indice == 0){
        return POSICION_INVALIDA;
    }
    return (indice - 1) / 2;
}

template<typename T, bool comp(T, T)>
void Heap<T, comp>::swap(size_t index_1, size_t index_2){
    if ((index_1 < tamanio()) && (index_2 < tamanio()))
    {
        T aux = datos[index_1];
        datos[index_1] = datos[index_2];
        datos[index_2] = aux;
    } 
    else 
    {
        std::cout << "Indice fuera de rango." << std::endl;
    }
}

template<typename T, bool comp(T, T)>
T Heap<T, comp>::baja(){
    if (vacio())
    {
        throw Heap_exception();
    }

    T eliminado = primero();

    if (tamanio() == 1)
    {
        datos.pop_back();
    }
    else
    {
        size_t posicion_eliminado = 0;
        size_t posicion_elemento_sustituto = tamanio() - 1;
        swap(posicion_eliminado, posicion_elemento_sustituto);
        datos.pop_back();

        posicion_elemento_sustituto = posicion_eliminado;

        downheap(posicion_elemento_sustituto);
    }

    return eliminado;  
}

template<typename T, bool (*comp)(T, T)>
void Heap<T, comp>::downheap(size_t &index_movido) {
    size_t posicion_hijo_izq = obtener_posicion_hijo_izquierdo(index_movido);
    size_t posicion_hijo_der = obtener_posicion_hijo_derecho(index_movido);
    size_t posicion_mayor = obtener_posicion_dato_mayor(posicion_hijo_izq, posicion_hijo_der);
    
    if (posicion_mayor == POSICION_INVALIDA)
    {
        return;
    }
    if (datos[posicion_mayor] > datos[index_movido])
    {
        swap(index_movido, posicion_mayor);
        index_movido = posicion_mayor;
        downheap(index_movido);
    }
}

template<typename T, bool (*comp)(T, T)>
size_t Heap<T, comp>::obtener_posicion_hijo_derecho(size_t indice) {
    if (2*indice + 2 > tamanio() - 1){
        return POSICION_INVALIDA;
    }
    return 2*indice + 2;
}

template<typename T, bool (*comp)(T, T)>
size_t Heap<T, comp>::obtener_posicion_hijo_izquierdo(size_t indice) {
    if (2*indice + 1 > tamanio() - 1){
        return POSICION_INVALIDA;
    }
    return 2*indice + 1;
}

template<class T, bool (*comp)(T, T)> 
size_t Heap<T, comp>::obtener_posicion_dato_mayor(size_t indice_izq, size_t indice_der){
    if (datos[indice_izq] > datos[indice_der])
    {
        return indice_izq;
    }
    return indice_der;
}

template<typename T, bool comp(T, T)>
T Heap<T, comp>::primero(){
    if (vacio())
    {
        throw Heap_exception();
    }
    
    return datos.front();
}

template<typename T, bool comp(T, T)>
std::size_t Heap<T, comp>::tamanio(){
    return datos.size();
}

template<typename T, bool comp(T, T)>
bool Heap<T, comp>::vacio(){
    return datos.empty();
}

template<class T, bool (*comp)(T, T)> 
Heap<T, comp>::~Heap(){}

#endif