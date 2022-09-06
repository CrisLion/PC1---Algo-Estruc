#include "ListaCD.hpp"
#include <conio.h>
#include <windows.h>
int main(){

    ListaCD<int> lista;
    lista.push_back(1);
    lista.push_back(12);
    lista.push_back(14);
    lista.push_back(15);
    
    Iterador<int> iter = lista.begin();
    bool continuar = true;
    while(continuar){
        std::cout<<"Usted se encuentre en el valor: "<<*iter<<std::endl;
        if (_kbhit()){
            switch(getch()){
                case 75:
                    --iter;break;
                case 77:
                    ++iter;break;
                case 27:
                    continuar = !continuar; break;
            }
        }
        Sleep(30);
        system("cls");
    
    return 0;
}