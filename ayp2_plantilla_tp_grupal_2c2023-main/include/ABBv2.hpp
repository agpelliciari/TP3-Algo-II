#ifndef ABB_H
#define ABB_H

#include <exception>
#include "NodoABBv2.hpp"

class ABB_exception : public std::exception {
};

template<typename T, bool menor(T, T), bool igual(T, T)>
class ABB {
private:
    NodoABB<T, menor, igual>* raiz;
    std::size_t cantidad_datos;

    // Pre: -
    // Post: Agrega el dato al árbol.
    // NOTA: Ya se debería haber revisado si el dato está o no.
    void alta(T dato, NodoABB<T, menor, igual>* nodo_actual);

    // Pre: -
    // Post: Elimina el dato del árbol y devuelve la nueva raiz, de haberla.
    // NOTA: Ya se debería haber revisado si el dato está o no.
    void baja(T dato, NodoABB<T, menor, igual>* nodo_actual);

    // Pre: -
    // Post: Devuelve true si el dato está en el subárbol.
    bool consulta(T dato, NodoABB<T, menor, igual>* nodo_actual);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido inorder.
    void inorder(NodoABB<T, menor, igual>* nodo_actual, std::vector<T>& datos);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido preorder.
    void preorder(NodoABB<T, menor, igual>* nodo_actual, std::vector<T>& datos);

    // Pre: -
    // Post: Carga los datos, respetando el recorrido postorder.
    void postorder(NodoABB<T, menor, igual>* nodo_actual, std::vector<T>& datos);

    // Pre: -
    // Post: Ejecuta el método/función en el subárbol.
    void ejecutar(void metodo(T), NodoABB<T, menor, igual>* nodo_actual);

public:
    // Constructor.
    ABB();

    // Pre: El dato a ingresar no puede estar en el árbol.
    // Post: Agrega el dato al árbol. Si no hay datos, crea una nueva raiz.
    void alta(T dato);

    // Pre: -
    // Post: Elimina el dato del árbol. Si no existe, no hace nada.
    // NOTA: Si la raiz cambia (sin importar el caso), se debe reasignar correctamente.
    void baja(T dato);

    // Pre: -
    // Post: Devuelve true si el dato está en el árbol. Si no hay datos, devuelve false.
    bool consulta(T dato);

    // Pre: -
    // Post: Devuelve el recorrido inorder.
    std::vector<T> inorder();

    // Pre: -
    // Post: Devuelve el recorrido preorder.
    std::vector<T> preorder();

    // Pre: -
    // Post: Devuelve el recorrido postorder.
    std::vector<T> postorder();

    // Pre: -
    // Post: Devuelve el recorrido en ancho.
    std::vector<T> ancho();

    // Pre: -
    // Post: Ejecuta el método/función en cada uno de los nodos.
    // NOTA: No abusar de este método, está solamente para simplificar
    // algunas cosas, como liberar la memoria de los nodos de usar punteros
    // o imprimir por pantalla el contenido. Pueden usar cualquier recorrido.
    void ejecutar(void metodo(T));

    // Pre: -
    // Post: Devuelve la cantidad de datos en el árbol.
    std::size_t tamanio();

    // Pre: -
    // Post: Devuelve true si el árbol está vacio.
    bool vacio();

    // El constructor de copia está deshabilitado.
    ABB(const ABB& abb) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const ABB& abb) = delete;

    // Destructor.
    ~ABB();
};

// --------------------------- IMPLEMENTACION -----------------------
template<typename T, bool menor(T, T), bool igual(T, T)>
ABB<T, menor, igual>::ABB() {

    this->raiz = 0;
    this ->cantidad_datos = 0;

}

template<typename T, bool menor(T, T), bool igual(T, T)>
bool ABB<T, menor, igual>::vacio() {
    return (this->raiz == 0);
}

template<typename T, bool menor(T, T), bool igual(T, T)>
void ABB<T, menor, igual>::alta(T dato, NodoABB<T, menor, igual>* nodo_actual) {

    if (menor(nodo_actual->dato, dato)) {

        if (nodo_actual->hijo_derecho != 0) {

            alta(dato, nodo_actual->hijo_derecho);  // Recursividad

        }
        else {

            NodoABB<T, menor, igual>* puntero_nodo_nuevo = new NodoABB<T, menor, igual> ;
            puntero_nodo_nuevo->dato = dato;
            puntero_nodo_nuevo->padre = nodo_actual;
            puntero_nodo_nuevo->hijo_izquierdo = 0;
            puntero_nodo_nuevo->hijo_derecho = 0;

            nodo_actual->hijo_derecho = puntero_nodo_nuevo;
        }
    }
    else if (menor(dato, nodo_actual->dato)) {

        if (nodo_actual->hijo_izquierdo != 0) {

            alta(dato, nodo_actual->hijo_izquierdo);    // Recursividad

        }
        else {

            NodoABB<T, menor, igual>* puntero_nodo_nuevo = new NodoABB<T, menor, igual> ;
            puntero_nodo_nuevo->dato = dato;
            puntero_nodo_nuevo->padre = nodo_actual;
            puntero_nodo_nuevo->hijo_izquierdo = 0;
            puntero_nodo_nuevo->hijo_derecho = 0;

            nodo_actual->hijo_izquierdo = puntero_nodo_nuevo;
        }
    }
    else {
        throw ABB_exception();
    }

}

template<typename T, bool menor(T, T), bool igual(T, T)>
void ABB<T, menor, igual>::alta(T dato) {

    if (vacio()) {

        NodoABB<T, menor, igual>* puntero_nodo_nuevo = new NodoABB<T, menor, igual> ;
        puntero_nodo_nuevo->dato = dato;
        puntero_nodo_nuevo->hijo_izquierdo = 0;
        puntero_nodo_nuevo->hijo_derecho = 0;
        puntero_nodo_nuevo->padre = 0;

        this->raiz = puntero_nodo_nuevo;

    }
    else {
        alta(dato, this->raiz);
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>  //Este es el privado.
bool ABB<T,menor,igual>::consulta(T dato, NodoABB<T, menor, igual>* nodo_actual){   
    if (nodo_actual==nullptr)
        return false;
    else if (igual(nodo_actual->dato,dato))    
        return true;                           //2 CASOS BASES O NO HAY HIJO (NULLPTR) o ENCONTRO DATO.
    else{                                      //sino empieza la recurrencia. 
        if (menor(nodo_actual->dato,dato))
            return(consulta(dato,nodo_actual->hijo_izquierdo)) //si mas chico voy al subarbol izq
        else
            return (consulta(dato,nodo_actual->hijo_derecho)) //sino al derecho.
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)> //publico
bool ABB<T,menor,igual>::consulta(T dato){
    return consulta(dato,raiz);
}

template<typename T, bool menor(T, T), bool igual(T, T)>
void ABB<T, menor, igual>::inorder(NodoABB<T, menor, igual>* nodo_actual, std::vector<T>& datos) {

    if (nodo_actual->hijo_izquierdo != 0) {
        inorder(nodo_actual->hijo_izquierdo, datos);
    }

    datos.push_back(nodo_actual->dato);
    
    if (nodo_actual->hijo_derecho != 0) {
        inorder(nodo_actual->hijo_derecho, datos);
    }
}

template<typename T, bool menor(T, T), bool igual(T, T)>
std::vector<T> ABB<T, menor, igual>::inorder() {

    std::vector<T> datos;

    if (!vacio()) {
        inorder(this->raiz, datos);
    }
    return datos;

}

template<typename T, bool menor(T, T), bool igual(T, T)>  //OJO, es el privado.
void ABB<T,menor,igual>::postorder(NodoABB<T, menor, igual>* nodo_actual, std::vector<T>& datos){

    if (nodo_actual->hijo_izquierdo!=nullptr)
        postorder(nodo_actual->hijo_izquierdo, datos);
    if (nodo_actual->hijo_derecho!=nullptr)
        postorder(nodo_actual->hijo_derecho, datos);
    datos.push_back(nodo_actual->dato);
}

template<typename T, bool menor(T, T), bool igual(T, T)> //el publico q inicia desde la raiz.
std::vector<T> ABB<T,menor,igual>::postorder(){
    std::vector<T> datos;
    postorder(raiz,datos);
    return datos;
}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
void ABB<T, menor, igual>::preorder(NodoABB<T, menor, igual> *nodo_actual, std::vector<T> &datos) {
    if (nodo_actual == nullptr){
        return;
    }

    datos.push_back(nodo_actual->dato);

    preorder(nodo_actual->hijo_izquierdo,datos);
    preorder(nodo_actual->hijo_derecho,datos);

}

template<typename T, bool (*menor)(T, T), bool (*igual)(T, T)>
std::vector<T> ABB<T, menor, igual>::preorder() {

    std::vector<T> vector_preorder;
    preorder(raiz,vector_preorder);

    return vector_preorder;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
std::vector<T> ABB<T,menor,igual>::ancho(){
    std::vector<T> cola;
    std::vector<T> datos;
    
    cola.push_back(raiz);

    while (!cola.empty())
    {
        if (cola.front()->hijo_izquierdo !=nullptr)
        {
            cola.push_back(cola.front()->hijo_izquierdo);
        }

        if (cola.front()->hijo_derecho !=nullptr)
        {
            cola.push_back(cola.front()->hijo_derecho);
        }

        datos.push_back(cola.front());

        cola.erase(cola.front());
    }

    delete cola;
    
    return datos;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
std::size_t ABB<T,menor,igual>::tamanio(){
    return cantidad_datos;
}

template<typename T, bool menor(T, T), bool igual(T, T)>
bool ABB<T,menor,igual>::vacio(){
    return cantidad_datos == 0;
}
#endif
