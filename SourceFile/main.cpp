#include "../Application/Controller.hpp"

int main(){
    srand(time(NULL));

    Controller* controllerObj = new Controller();
    controllerObj->IniciarPrograma();

    delete controllerObj;
    return 0;
}