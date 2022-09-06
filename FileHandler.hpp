#ifndef __FILEHANDLER__
#define __FILEHANDLER__
#include "Lista.hpp"

using namespace std;

class FileHandler{
public:
    static void saveData(string filePath, Lista<string> listaAtributos){ // [obj (class Paciente)] () -> Lista<string> {Lista<string> L}
        fstream miArchivo;
        string allAtributes;

        miArchivo.open(filePath, ios::app);

        for(Iterador<string> iter = listaAtributos.begin(); iter != listaAtributos.end(); ++iter){
            
        }

    }
};
#endif