#ifndef __FILEHANDLER__
#define __FILEHANDLER__
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../DoubleNodeStructures/Lista.hpp"
#include "../EsSaludEntities/EntidadesMedicas.hpp"
#include "../SimpleNodeStructures/Pila.hpp"
using namespace std;
using namespace EntidadesMedicas;
class FileHandler{

private:
    static void Atributes_toCSV(string& allAtributes,Lista<string>& listaAtributos ,Iterador<string> iter){ // O(n)
        if(!(iter != listaAtributos.end())){                // n
            allAtributes.pop_back();                        // 1
            return;                                         // 1
        }           
        allAtributes += *iter + ",";                        // 2
        ++iter;                                             // 2
        Atributes_toCSV(allAtributes,listaAtributos,iter);  // 1
    }
    // Analisis Detallado: n + 1 + 1 + 2 + 2 + 1  = n + 7
    // Tiempo Asintotico: O(n)


public:
    static void saveData(string filePath, Lista<string>& listaAtributos){ // [obj (class Paciente)] () -> Lista<string> {Lista<string> L}
        fstream miArchivo;
        string allAtributes = "";

        Atributes_toCSV(allAtributes,listaAtributos,listaAtributos.begin());
        
        miArchivo.open(filePath, ios::app);//1
        miArchivo<<allAtributes<<'\n';// 1
        miArchivo.close();//1
    }//Tiempo detallado: n(m+1) +13 +1 +1 +1 = nm + n + 16
     //Tiempo asintotico: O(n*m)

    static void LoadData(string filePath,string DNI, Paciente*& object){ // [] (Lista<string>) -> T {class Paciente*} {}
        fstream miArchivo;
        string linea, palabra;
        Lista<string> listaTemporal;

        miArchivo.open(filePath, ios::in);
        while (getline(miArchivo, linea)){ //Iteracion para recorrer de linea en linea

            stringstream total(linea);
            while(getline(total,palabra, ',')){ //iteracion para recorrer de palabra en palabra de una linea separada por comas
                listaTemporal.push_back(palabra);
            }

            if (DNI == listaTemporal.get_cabeza()){
                
                Iterador<string> iter = listaTemporal.begin(); 
                object->DNI = *iter; ++iter;
                object->fechaNacimiento = *iter; ++iter;
                object->nombres = *iter; ++iter;
                object->apellidos = *iter; ++iter;
                object->telefono = *iter; ++iter;
                object->contrasena = *iter; ++iter;

                miArchivo.close();
                return ;
            }
            listaTemporal.~Lista();
        }
        miArchivo.close();
    }
    
    static void LoadHistory(string filePath, Pila<string>& pilaHistorial){
        fstream miArchivo;
        string linea, palabra;
        string cadenaCompleta;
        
        miArchivo.open(filePath, ios::in);
        while (getline(miArchivo, linea)){ //Iteracion para recorrer de linea en linea

            stringstream total(linea);
            while(getline(total,palabra, ',')){ //iteracion para recorrer de palabra en palabra de una linea separada por comas  
                cadenaCompleta += palabra + "-"; 
            }
            cadenaCompleta.pop_back();
            pilaHistorial.push(cadenaCompleta);
            cadenaCompleta.clear();
        }
    }
};
#endif