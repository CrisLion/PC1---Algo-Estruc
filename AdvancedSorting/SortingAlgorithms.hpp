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

    template<typename T>
    T quickSelect(std::vector<T>& vec, bool (*compare)(const T&,const T&), int low, int high, int k){
        if (low == high) return vec[low];

        int index = partition(vec,compare,low,high);
        int len = index - low +1;

        if (k == len) return vec[index];

        else if (k < len){
            return quickSelect(vec,compare,low,index-1,k);
        }

        else{
            return quickSelect(vec,compare,index+1,high,k-len);
        }
    }
}