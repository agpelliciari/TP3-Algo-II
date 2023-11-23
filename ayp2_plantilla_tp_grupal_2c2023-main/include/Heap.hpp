#ifndef ALGO2_TP3_PT2_HEAP_H
#define ALGO2_TP3_PT2_HEAP_H

#include <vector>
#include <cstdlib>
#include <exception>
#include <iostream>
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
    // Post: Ordena el vector de forma creciente usando un heap de maxima.
    void heapsort();
    
    // Pre: El heap no puede estar vacío.
    // Post: Convierte el vector en un heap de maxima.
    void rearmar_heap(size_t tamanio_logico, size_t indice);

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

template<class T, bool (*comp)(T, T)>
void Heap<T, comp>::heapsort(){
    for (size_t i = tamanio() - 1; i > 0; i--) //aca hay bug? 
    {
        swap(0, i);  //el 0 representa la raiz, la i es el ultimo elemento.
        rearmar_heap(i, 0);
    }
}

template<class T, bool (*comp)(T, T)>
void Heap<T, comp>::rearmar_heap(size_t tamanio_logico, size_t indice){
    size_t indice_mayor = indice;
    size_t indice_hijo_izq = 2*indice + 1;
    size_t indice_hijo_der = 2*indice + 2;
    
    if (indice_hijo_izq < tamanio_logico && datos[indice_hijo_izq] > datos[indice_mayor])
    {
        indice_mayor = indice_hijo_izq;
    }

    if (indice_hijo_der < tamanio_logico && datos[indice_hijo_der] > datos[indice_mayor])
    {
        indice_mayor = indice_hijo_der;
    }

    if (indice_mayor != indice)
    {
        swap(indice, indice_mayor);
        indice = indice_mayor;
        rearmar_heap(tamanio_logico, indice);
    }
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
    size_t indice_mayor = index_movido;
    size_t indice_hijo_izq = 2*index_movido + 1;
    size_t indice_hijo_der = 2*index_movido + 2;
    
    if ((indice_hijo_izq < tamanio() - 1) && (datos[indice_hijo_izq] > datos[indice_mayor]))
    {
        indice_mayor = indice_hijo_izq;
    }

    if ((indice_hijo_der < tamanio() - 1) && (datos[indice_hijo_der] > datos[indice_mayor]))
    {
        indice_mayor = indice_hijo_der;
    }

    if (indice_mayor != index_movido)
    {
        swap(index_movido, indice_mayor);
        index_movido = indice_mayor;
        downheap(index_movido);
    }
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