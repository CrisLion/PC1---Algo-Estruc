#include "Nodo.hpp"
#include "Iterador.hpp"
#include <iostream>

template<typename T>
class ListaCD{ //Lista circular doblemente enlazada
private:
    Nodo<T>* _cabeza;
    Nodo<T>* _cola;
    unsigned int _n;
public:
    ListaCD() : _cabeza(nullptr), _cola(nullptr), _n(0) {}
    ~ListaCD() { while (_cabeza != nullptr) pop_back();}

    void push_back(const T& valor){
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        if (_n == 0){
            _cabeza = _cola = nuevoNodo;
            nuevoNodo->_anterior = nuevoNodo;
            nuevoNodo->_siguiente = nuevoNodo;
            ++_n;
            return;
        }
        nuevoNodo->_anterior = _cola;
        nuevoNodo->_siguiente = _cabeza;
        _cabeza->_anterior = nuevoNodo;
        _cola->_siguiente = nuevoNodo;
        _cola= nuevoNodo;
        ++_n;
    }

    void pop_back(){   
        if (_n != 0){// 0  ->  0 -> nu
            Nodo<T>* aux = _cola;
            if (_n == 1){
                _cola = _cabeza = nullptr;
                delete aux;
                --_n;
                return;
            }
            _cola->_anterior->_siguiente = _cabeza;
            _cola = _cola->_anterior;
            _cabeza->_anterior = _cola;
            delete aux;
            --_n;
        }
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

    Iterador<T> begin(){
        return Iterador<T>(0,_cabeza);
    }

    Iterador<T> end(){
        return Iterador<T>(_n,nullptr);
    }
    

};