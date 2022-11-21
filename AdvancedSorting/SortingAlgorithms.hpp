#pragma once
#include <vector>

namespace SortingAlgorithms{

    template<typename T>
    static void Merge(std::vector<T>& vec, bool (*compare)(const T&,const T&) ,int inicio,int medio, int final){
        int tam1 = medio - inicio +1;
        int tam2 = final - medio;

        T* arrIzq = new T[tam1];
        T* arrDer = new T[tam2];

        //Copiando los valores al subarreglo de la izquierda
        for(int i = 0; i < tam1; i++){
            arrIzq[i] = vec[inicio+i];
        }
        //Copiando los valores al subarreglo de la derecha
        for(int i = 0; i < tam2; i++){
            arrDer[i] = vec[medio+1+i];
        }

        int indexIzq = 0, indexDer = 0, indexArrMerged = inicio;

        while(indexIzq < tam1  && indexDer < tam2){
            if (compare(arrIzq[indexIzq], arrDer[indexDer])){ //arrIzq[indexIzq] <= arrDer[indexDer]
                vec[indexArrMerged] = arrIzq[indexIzq];
                indexIzq++;
            }
            else{
                vec[indexArrMerged] = arrDer[indexDer];
                indexDer++;
            }
            indexArrMerged++;
        }

        //Copiando los elementos restantes del sub arrIzq en el arreglo Merged
        while (indexIzq < tam1){
            vec[indexArrMerged] = arrIzq[indexIzq];
            indexArrMerged++;
            indexIzq++;
        }

        //Copiando los elementos restantes del sub arrDer en el arreglo Merged
        while (indexDer < tam2){
            vec[indexArrMerged] = arrDer[indexDer];
            indexArrMerged++;
            indexDer++;
        }

        delete[] arrIzq;
        delete[] arrDer;
    }

    template<typename T>
    void MergeSort(std::vector<T>& vec, bool (*compare)(const T&,const T&) ,int inicio, int final){
        if (inicio >= final){
            return;
        }
        int medio = (inicio + final)/2;
        MergeSort(vec,compare, inicio, medio);
        MergeSort(vec,compare,medio+1,final);
        Merge<T>(vec,compare,inicio,medio,final);
    }

    template<typename T>
    static void swap(T& a, T& b){
        T aux = a;
        a = b;
        b = aux;
    }

    template<typename T>
    static int partition(std::vector<T>& vec, bool (*compare)(const T&,const T&), int low, int high){
        T pivot = vec[high];
        int i = low -1;
        for (int j = low; j <= high - 1; j++){
            if (compare(vec[j],pivot)){
                i++;
                swap(vec[i],vec[j]);
            }
        }
        swap(vec[i+1],vec[high]);
        return i+1;
    }

    template<typename T>
    void quickSort(std::vector<T>& vec, bool (*compare)(const T&,const T&), int low, int high){
        
        if (low < high) {
            int pi = partition(vec, compare , low, high);
            quickSort(vec, compare ,low, pi - 1);
            quickSort(vec, compare ,pi + 1, high);
        }
    }

    template <typename T>
    void heapify(std::vector<T>& arr, bool (*compare)(const T&, const T&), int size ,int i) {

        int left = 2*i+1;
        int right = 2*i+2; 
        int selected = i;

        if (left < size && compare(arr[left], arr[selected])) // for minheapify: _arr[left] < _arr[smaller]
            selected = left;                                  // for maxheapify: _arr[left] > _arr[smaller]

        if (right < size && compare(arr[right], arr[selected])) // for minheapify: _arr[right] < _arr[smaller]
            selected = right;                                   // for maxheapify: _arr[right] > _arr[smaller]
    
        if (selected != i){
            swap(arr[selected], arr[i]);
            heapify(arr, compare, size, selected);
        }
    }

    template <typename T>
    void HeapSort(std::vector<T>& arr, bool (*compare)(const T&, const T&)) {
        for (int i = arr.size() / 2 - 1; i >= 0; i--){
            heapify(arr, compare, arr.size(), i);
        }
    
        for (int i = arr.size() - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, compare, i ,0);
        }
    }
}