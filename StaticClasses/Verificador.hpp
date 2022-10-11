#ifndef __VERIFICADOR__
#define __VERIFICADOR__
#include <fstream>
#include <string>
#include <sstream>
#include "../DoubleNodeStructures/Lista.hpp"
using namespace std;

class Verificador {
public:
    static bool verificarUsuario(string DNI, string constrasena){ //O(n)(m+z+k)
        Lista<string> listaTemporal;//1
        string linea, palabra;// 1
        fstream miArchivo; //1

        miArchivo.open("../Registros/Usuarios.txt", ios::in);// 1
        while (getline(miArchivo, linea)){ //Iteracion para recorrer de linea en linea //n +1

            stringstream total(linea);// 1
            while(getline(total,palabra, ',')){ //iteracion para recorrer de palabra en palabra de una linea separada por comas //m+1
                listaTemporal.push_back(palabra); //13
            }

            if (DNI == listaTemporal.get_cabeza() && constrasena == listaTemporal.get_cola()){//w + z +3
                listaTemporal.~Lista();//m
                miArchivo.close();//1
                return true;//1
            }

            listaTemporal.~Lista();//m
        }
        miArchivo.close();//1
        return false;//1
    }//Notación Detallada: 4 + (n+1) (m+1+1+13+z+w+3+m+1+1) = 4 + (n+1) (2m+20+z+w)
    // Notación Asintótica: O(n)(m+z+k)

};

#endif