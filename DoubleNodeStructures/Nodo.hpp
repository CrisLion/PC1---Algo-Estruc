#ifndef __NODO___
#define __NODO___
template <typename T>
struct Nodo {
    public:
        Nodo(T dato) : _dato(dato), _siguiente(nullptr), _anterior(nullptr) {}
        Nodo() = delete;
        T _dato;
        Nodo<T>* _siguiente;
        Nodo<T>* _anterior;
};

#endif