#pragma once
#include "SingleNode.hpp"

template <typename T>
class Cola{

    std::shared_ptr<SNodo<T>> head;
    std::shared_ptr<SNodo<T>> rear;
    size_t size;

public:
    Cola() : head(nullptr), rear(nullptr), size(0) {}

    void deQueue(){
        if (size != 0){
            std::shared_ptr<SNodo<T>> aux = head;
            head = head->siguiente;
            --size;
            if (size == 0) rear = nullptr;
        }
    }

    void enQueue(const T& value){
        std::shared_ptr<SNodo<T>> aux = std::make_shared<SNodo<T>>(value);
        if (size == 0){
            head = aux;
            rear = aux;
            ++size;
            return;
        }
        rear->siguiente = aux;
        rear = aux;
        ++size;
    }

    size_t Size(){
        return size;
    }

    void seek(){
        std::shared_ptr<SNodo<T>> aux = head;
        while(aux.get()){
            std::cout<<aux->value<<" ";
            aux = aux->siguiente;
        }
        std::cout<<'\n';
    }
};