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

    void enQueue(const T& value){                                               // O(1)
        std::shared_ptr<SNodo<T>> aux = std::make_shared<SNodo<T>>(value);  // 1
        if (size == 0){                                                     // 1
            head = aux;                                                     // 1
            rear = aux;                                                     // 1
            ++size;                                                         // 2
            return;                                                         // 1
        }
        rear->siguiente = aux;                                              // 1
        rear = aux;                                                         // 1
        ++size;                                                             // 2
    }
    // Analisis Detallado: 1 + 1 + 1 + 1 + 2 + 1 + 1 + 1 + 2 = 11
    // Tiempo Asintotico: O(1)

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