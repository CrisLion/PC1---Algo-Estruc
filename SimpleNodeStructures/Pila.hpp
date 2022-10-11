#pragma once
#include "SingleNode.hpp"
#include <functional>

template <typename T>
class Pila{

    std::shared_ptr<SNodo<T>> head;

public:
    Pila() : head(nullptr) {}

    void push(const T& value){
        std::shared_ptr<SNodo<T>> aux = std::make_shared<SNodo<T>>(value);
        aux->siguiente = head;
        head = aux;
    }

    void pop(){
        std::shared_ptr<SNodo<T>> aux = head;
        head = head->siguiente;
    }

    void seek(std::function<void(T&)> PrintValue){
        std::shared_ptr<SNodo<T>> aux = head;
        while(aux.get()){
            PrintValue(aux->value);
            aux = aux->siguiente;
        }
        std::cout<<'\n';
    }

};