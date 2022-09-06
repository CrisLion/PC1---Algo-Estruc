#include "Lista.hpp"
#include "Verificador.hpp"
#include <string>

class Perro{
public:
    int anos;
    char letra;
    Perro() : anos(rand()), letra(rand() % (90 - 65 +1) +65) {}
};

int main(){


    Lista<Perro*> mylista;
    std::string a;
    int opc;
    auto fun = [] (Perro* valor) -> void {std::cout<<valor->anos<<" "<<valor->letra <<" ";};

    std::cout<<Verificador::verificarUsuario("74395344","contrasena1234");

    while (true)
    {
        std::cin>>opc;
        if (opc == 1) {/*std::cin>> a*/; mylista.push_front(new Perro());}
        if (opc == 2) {/*std::cin>> a*/; mylista.push_back(new Perro());}
        if (opc == 3) mylista.pop_front();
        if (opc == 4) mylista.pop_back();
        if (opc == 5) mylista.~Lista();
        if (opc == 6) mylista.displayList(fun);
    }
    
    
    

}