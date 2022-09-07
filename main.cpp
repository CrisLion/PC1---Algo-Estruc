#include "Lista.hpp"
#include "Verificador.hpp"
#include "FileHandler.hpp"
#include "Controladora.hpp"

int main(){

    Controladora* controladoraObj = new Controladora();
    controladoraObj->IniciarPrograma();

    delete controladoraObj;

    return 0;
}