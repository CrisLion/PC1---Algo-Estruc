#include "Nodo.hpp"
#include "Iterador.hpp"
#include <iostream>
#include <functional>
#include <vector>
using std::function;
using std::vector;
template<typename T>
class ListaCD{ //Lista circular doblemente enlazada
private:
    Nodo<T>* _cabeza;
    Nodo<T>* _cola;
    unsigned int _n;
public:
    ListaCD() : _cabeza(nullptr), _cola(nullptr), _n(0) {}
    ~ListaCD() { while (_cabeza != nullptr) pop_back();}

    void push_back(const T& valor){                 //O(1)
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);    // 1
        if (_n == 0){                               // 1
            _cabeza = _cola = nuevoNodo;            // 2
            nuevoNodo->_anterior = nuevoNodo;       // 2
            nuevoNodo->_siguiente = nuevoNodo;      // 2
            ++_n;                                   // 2  
            return;
        }
        nuevoNodo->_anterior = _cola;               // 2
        nuevoNodo->_siguiente = _cabeza;            // 2
        _cabeza->_anterior = nuevoNodo;             // 2
        _cola->_siguiente = nuevoNodo;              // 2
        _cola= nuevoNodo;                           // 1
        ++_n;                                       // 2
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

    void Sort(function<bool(T&, T&)> compare){                          // O(n^2)

        int size = this->_n;                                        // 1
        vector<T> aux;                                              // 1

        int i = 0;                                                  // 1
        for (Iterador<T> iter = this->begin(); i < size; ++iter){   // 1 + n(1 + 3 + 2) = 1 + 4n
            aux.emplace_back(*iter);                                // 1
            i++;                                                    // 2
        }

        this->~ListaCD();                                           // n

        for(int i = 1; i < size; i++){                              // 1 + n(1 + 6n + 2) = 1 + n(3 + 6n)
            T key = aux[i];                                         // 2
            int k = i-1;                                            // 1
            while(k>=0 && compare(aux[k],key)){                     // n - 1
                aux[k+1] = aux[k];                                  // 2
                k--;                                                // 2
            }
            aux[k+1] = key;                                         // 2
        }

        for(int i = 0; i < size; i++){                              // 1 + n(1 + 1 + 2 ) = 1 + 4n
            this->push_back(aux[i]);                                // 1
        }
    }
    // Analisis Detallado: 3 + 1 + 6n + 1 + n(3 + 6n) + 2 + 1 + 4n = 8 + 13n + 6n^2
    // Tiempo Asintotico: O(n^2)


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