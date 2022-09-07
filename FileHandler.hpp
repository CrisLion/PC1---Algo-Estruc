#ifndef __FILEHANDLER__
#define __FILEHANDLER__
#include "Lista.hpp"
#include "EntidadesMedicas.hpp"
using namespace std;
using namespace EntidadesMedicas;
class FileHandler{
public:
    static void saveData(string filePath, Lista<string>& listaAtributos){ // [obj (class Paciente)] () -> Lista<string> {Lista<string> L}
        fstream miArchivo;
        string allAtributes;

        for(Iterador<string> iter = listaAtributos.begin(); iter != listaAtributos.end(); ++iter){//n
            allAtributes += *iter + ",";// m + 1
        }
        allAtributes.pop_back();
        
        miArchivo.open(filePath, ios::app);
        miArchivo<<allAtributes<<'\n';
        miArchivo.close();
    }

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
};
#endif