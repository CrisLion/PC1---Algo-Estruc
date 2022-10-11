#pragma once
#include <iostream>
#include <memory>

template <typename T>
struct SNodo{
    T value;
    std::shared_ptr<SNodo<T>> siguiente;
    SNodo(T value) : value(value), siguiente(nullptr) {}
    ~SNodo() {}
};