#include "../Application/Controladora.hpp"

int main(){
    srand(time(NULL));
    
    Controladora* controladoraObj = new Controladora();
    controladoraObj->IniciarPrograma();

    delete controladoraObj;

    return 0;
}