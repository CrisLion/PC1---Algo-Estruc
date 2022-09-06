#ifndef __ITERADOR___
#define __ITERADOR___
#include "Nodo.hpp"
template <typename T>
class Iterador {
    unsigned int _pos;
    Nodo<T>* _aux;

public:
    Iterador(unsigned int pos, Nodo<T>* aux) : _pos(pos), _aux(aux) {}
    void operator ++() {++_pos; _aux->_siguiente;}
    void operator --() {--_pos; _aux->_anterior;}
    bool operator !=(Iterador iter) {return _pos != iter._pos;}
    T operator *() {return _aux->_dato;}
};
#endif