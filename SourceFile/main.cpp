#include "../Application/Controladora.hpp"
#include <ctime>
int main(){
    srand(time(NULL));
    
    Controladora* controladoraObj = new Controladora();
    controladoraObj->IniciarPrograma();

    delete controladoraObj;

    return 0;
}