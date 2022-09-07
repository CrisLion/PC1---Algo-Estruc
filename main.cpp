#include "Lista.hpp"
#include "Verificador.hpp"
#include "FileHandler.hpp"
#include "Controladora.hpp"

int main(){
    srand(time(NULL));
    
    Controladora* controladoraObj = new Controladora();
    controladoraObj->IniciarPrograma();

    delete controladoraObj;

    return 0;
}