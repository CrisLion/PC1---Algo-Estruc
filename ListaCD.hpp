#include "Nodo.hpp"
#include "Iterador.hpp"
#include <iostream>
#include <functional>
using std::function;
template<typename T>
class ListaCD{ //Lista circular doblemente enlazada
private:
    Nodo<T>* _cabeza;
    Nodo<T>* _cola;
    unsigned int _n;
public:
    ListaCD() : _cabeza(nullptr), _cola(nullptr), _n(0) {}
    ~ListaCD() { while (_cabeza != nullptr) pop_back();}

    void push_back(const T& valor){ //O(1)
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);// 1
        if (_n == 0){// 1
            _cabeza = _cola = nuevoNodo; // 2
            nuevoNodo->_anterior = nuevoNodo; // 2
            nuevoNodo->_siguiente = nuevoNodo;// 2
            ++_n; // 2 
            return;
        }
        nuevoNodo->_anterior = _cola; // 2
        nuevoNodo->_siguiente = _cabeza; // 2
        _cabeza->_anterior = nuevoNodo; // 2
        _cola->_siguiente = nuevoNodo; // 2
        _cola= nuevoNodo; // 1
        ++_n; // 2
    } // Analisis Detallado max(1 +2 +2 +2 +2 , 2 +2 +2 +2+1+2) +1 = 11 +1 = 12
      // Analisis Asintotico = O(1)

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

    void Sort(function<bool(T& a, T& b)> compare){

        int size = this->_n;
        T* aux = new T[size];

        int i = 0;
        for (Iterador<T> iter = this->begin(); i < size; ++iter){
            aux[i] = *iter;
            i++;
        }

        this->~ListaCD();

        for(int i = 1; i < size; i++){
            T key = aux[i];
            int k = i-1;
            while(k>=0 && compare(aux[k],key)){
                aux[k+1] = aux[k];
                k--;
            }
            aux[k+1] = key;
        }

        for(int i = 0; i < size; i++){
            this->push_back(aux[i]);
        }
        
        delete aux;
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