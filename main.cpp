#include "Lista.hpp"
#include "Verificador.hpp"
#include "FileHandler.hpp"
#include "Controladora.hpp"

int main(){

    //testeo
    // Lista<Perro*> mylista;
    // std::string a;
    // int opc;
    // auto fun = [] (Perro* valor) -> void {std::cout<<valor->anos<<" "<<valor->letra <<" ";};
    // std::cout<<Verificador::verificarUsuario("74395344","contrasena1234");

    // //Testeo
    // Lista<string> mylista2;
    // mylista2.push_back("82950164");
    // mylista2.push_back("MAria");
    // mylista2.push_back("De los santos");
    // mylista2.push_back("micontra1234");

    // FileHandler::saveData("Registros/Usuarios.txt",mylista2);

    Controladora* controladoraObj = new Controladora();
    
    controladoraObj->IniciarPrograma();

    //while (true) [] {}
    //
    //    std::cin>>opc;
    //    if (opc == 1) {/*std::cin>> a*/; mylista.push_front(new Perro());}
    //    if (opc == 2) {/*std::cin>> a*/; mylista.push_back(new Perro());}
    //    if (opc == 3) mylista.pop_front();
    //    if (opc == 4) mylista.pop_back();
    //    if (opc == 5) mylista.~Lista();
    //    if (opc == 6) mylista.displayList(fun);
    //}
}