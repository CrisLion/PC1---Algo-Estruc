#ifndef __FILEHANDLER__
#define __FILEHANDLER__
#include "Lista.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
using namespace std;

class Verificador {
public:
    static bool verificarUsuario(string DNI, string constrasena){ //O(n2)
        Lista<string> listaTemporal;
        string linea, palabra;
        fstream miArchivo;

        miArchivo.open("Registros/Usuarios.txt", ios::in);
        while (getline(miArchivo, linea)){ //Iteracion para recorrer de linea en linea

            stringstream total(linea);
            while(getline(total,palabra, ',')){ //iteracion para recorrer de palabra en palabra de una linea separada por comas
                listaTemporal.push_back(palabra);
            }

            if (DNI == listaTemporal.get_cabeza() && constrasena == listaTemporal.get_cola()){
                listaTemporal.~Lista();
                miArchivo.close();
                return true;
            }

            listaTemporal.~Lista();
        }
        miArchivo.close();
        return false;
    }

};

#endif