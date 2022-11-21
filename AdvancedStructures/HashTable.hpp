#pragma once
#include <iostream>
#include <string>
#include <list>
#include <cmath>

template <typename T>
class HashTable { //Not resizable
private:
    
    struct Element{
        std::string key;
        T value;
    };

    void (*_show)(const T&);
    size_t _size;
    size_t _capacity;
    std::list<Element>** _arr;
    const long double c_A = (sqrt(5) - static_cast<long double>(1))/static_cast<long double>(2);

private:
    bool _isPrime(const size_t& n){//O(sqrt(n)) < O(n)
        if (n == 1) return false;

        for(int i = 2; i*i<=n; i++){
            if (n % i == 0) return false;
        }
        return true;
    }

    size_t _FindNextPrime(const size_t& n){ //O(n*sqrt(m))
        for(int i = n; i <= 2*n; i++){
            if (_isPrime(i)) return i;
        }
        return 0;
    }

    size_t _hashFunction(const std::string& key){
        long double res = 0;
        long double fractPart;

        for(unsigned int i = 0; i < key.size(); i++){
            res += pow(key[i],(i+1)/7.f);
        }

        fractPart = static_cast<long double>(res)*c_A;
        fractPart = fractPart - floor(fractPart);

        return floor(fractPart*_capacity);        
    }

public:
    HashTable(size_t capacity, void (*show)(const T&)) : _size(0), _show(show) {

        if (!_isPrime(capacity)){
            _capacity = _FindNextPrime(capacity);
        }

        _arr = new std::list<Element>*[_capacity];

        for(int i =0; i < _capacity; i++){
            _arr[i] = nullptr;
        }
    }

    ~HashTable(){
        for(int i = 0; i < _capacity; i++){
            if (_arr[i] != nullptr) delete _arr[i];
        }
        delete[] _arr;
    }

    size_t get_capacity(){
        return _capacity;
    }

    size_t get_size(){
        return _size;
    }
    
    void insert(const std::string& key, const T& value){

        size_t index = _hashFunction(key);

        if (_arr[index] == nullptr){
            _arr[index] = new std::list<Element>();
        }

        _arr[index]->emplace_back(Element{key, value});
        ++_size;
    }

    T& operator[] (const std::string& key){ //Just for searching given a key. If the key does not exist, It will throw a runtime error.
        size_t index = _hashFunction(key);
        
        for(auto iter = _arr[index]->begin(); iter != _arr[index]->end(); ++iter){
            if ((*iter).key == key)
                return (*iter).value;
        }
    }

    void erase(const std::string& key){
        size_t index = _hashFunction(key);

        if (_arr[index] == nullptr) return;

        for(auto iter = _arr[index]->begin(); iter != _arr[index]->end(); ++iter){
            if ((*iter).key == key){
                _arr[index]->erase(iter);
                --_size;
                if (_arr[index]->size() == 0){ //if the list remains with 0 elements, then we must set that pointer to NULL
                    delete _arr[index];
                    _arr[index] = nullptr;
                }
                return;
            }       
        }
    }

    void print(){
        for(int i = 0; i < _capacity; i++){

            std::cout<<"Bucket "<<i<<": ";

            if (_arr[i] != nullptr){                

                for(auto &element : (*_arr[i])){
                    _show(element.value);
                }
            }
            std::cout<<std::endl;
        }
    }
};