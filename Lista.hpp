#ifndef __LISTA__
#define __LISTA__
#include "Librerias.hpp"
#include "Nodo.hpp"
#include "Iterador.hpp"

template<typename T>
class Lista {
public:
    Lista() : _cabeza(nullptr), _cola(nullptr), _n(0) {}
    ~Lista() { while (_cabeza != nullptr) pop_front(); }

    void push_front(const T& valor){
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
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
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
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
            Nodo<T>* aux;
            aux = _cabeza;
            if (_cabeza == _cola) _cola = nullptr;
            _cabeza = _cabeza->_siguiente;
            if (_cabeza != nullptr) _cabeza->_anterior = nullptr;
            delete aux;
            _n--;
        }     
    }

    void pop_back(){
        if (_n != 0){
            Nodo<T>* aux;
            aux = _cola;
            if (_cabeza == _cola) _cabeza = nullptr;
            _cola = _cola->_anterior;
            if(_cola != nullptr) _cola->_siguiente = nullptr;
            delete aux;
            _n--;
        }
    }

    void displayList(std::function<void(T)> printNodeValue){ // [] (T valor) -> void {std::cout<<valor<<" ";};
        Nodo<T>* aux = _cabeza;
        while(aux != nullptr){
            printNodeValue(aux->_dato);
            aux = aux->_siguiente;
        }
        std::cout<<std::endl;     
    }

    void Sort(std::function<bool(const T&, const T&)> compare){
        for(Nodo<T>* i = this->_cabeza; i != nullptr; i = i->_siguiente){
            bool isSorted = true;
            for(Nodo<T>* j = i->_siguiente; j != nullptr; j = j->_siguiente){
                    
                    if(compare(i->_dato, j->_dato)){
                        T aux = i->_dato;
                        i->_dato = j->_dato;
                        j->_dato = aux;
                        isSorted = false;
                    }
            }
            if (isSorted) break;
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

private:
    
    Nodo<T>* _cabeza;
    Nodo<T>* _cola;
    unsigned int _n;
};

#endif

