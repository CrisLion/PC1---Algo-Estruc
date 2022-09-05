#include "Lista.h"

int main(){


    Lista<int> mylista;
    int a, opc;
    auto fun = [] (int valor) -> void {std::cout<<valor<<" ";};

    while (true)
    {
        std::cin>>opc;
        if (opc == 1) {std::cin>> a; mylista.push_front(a);}
        if (opc == 2) {std::cin>> a; mylista.push_back(a);}
        if (opc == 3) mylista.pop_front();
        if (opc == 4) mylista.pop_back();
        if (opc == 5) mylista.displayList(fun);
    }
    
    

}