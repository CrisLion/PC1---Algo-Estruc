#ifndef __LISTA__
#define __LISTA__
#include <functional>
#include <iostream>
template<typename T>
class Lista {
public:
    Lista() : _cabeza(nullptr), _cola(nullptr), _n(0) {}
    ~Lista() { while (_cabeza != nullptr) pop_front(); }

    void push_front(const T& valor){
        Nodo* nuevoNodo = new Nodo(valor);
        if (_n == 0){
            _cabeza = _cola = nuevoNodo;
            _n++;
            return;
        }
        nuevoNodo->_siguiente = _cabeza;
        _cabeza->_anterior = nuevoNodo;
        _cabeza = nuevoNodo;
        _n++;
    }

    void push_back(const T& valor){
        Nodo* nuevoNodo = new Nodo(valor);
        if (_n == 0) {
            _cabeza = _cola = nuevoNodo;
            _n++;
            return;
        }
        nuevoNodo->_anterior = _cola;
        _cola->_siguiente = nuevoNodo;
        _cola = nuevoNodo;
        _n++;
    }               
                
    void pop_front(){
        if (_n != 0){
            Nodo* aux;
            aux = _cabeza;
            if (_cabeza == _cola) _cola == nullptr;
            _cabeza = _cabeza->_siguiente;
            if (_cabeza != nullptr) _cabeza->_anterior = nullptr;
            delete aux;
            _n--;
        }     
    }

    void pop_back(){
        if (_n != 0){
            Nodo* aux;
            aux = _cola;
            if (_cabeza == _cola) _cabeza = nullptr;
            _cola = _cola->_anterior;
            if(_cola != nullptr) _cola->_siguiente = nullptr;
            delete aux;
            _n--;
        }
    }

    void displayList(std::function<void(T)> printNodeValue){ // [] (T valor) -> void {std::cout<<valor<<" ";};
        Nodo* aux = _cabeza;
        while(aux != nullptr){
            printNodeValue(aux->_dato);
            aux = aux->_siguiente;
        }
        std::cout<<std::endl;
    }

    unsigned int size(){
        return _n;
    }

    T get_cabeza(){
        return _cabeza->_dato;
    }

    T get_cola(){
        return _cola->_dato;
    }

private:
    class Nodo {
    public:
        Nodo(T dato) : _dato(dato), _siguiente(nullptr), _anterior(nullptr) {}
        Nodo() = delete;
    private:
        T _dato;
        Nodo* _siguiente;
        Nodo* _anterior;
        friend class Lista;
    };
    Nodo* _cabeza;
    Nodo* _cola;
    unsigned int _n;
};

#endif

