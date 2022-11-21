#pragma once

#include <conio.h>
#include <math.h>
#include "../StaticClasses/FileHandler.hpp"
#include "../AdvancedSorting/SortingAlgorithms.hpp"
#include "../StaticClasses/Banner.hpp"

class AdminHandler {
private:
    static void VerHistorial(){
        system("cls");
        Banner::header();
        Pila<string> pilaHistorial;
        FileHandler::LoadHistory("../Registros/Historial.txt",pilaHistorial);
        auto PrintValue = [] (string &a) ->void {cout<<a<<endl;};
        pilaHistorial.seek(PrintValue);
        getch();
        system("cls");
    }
    
public:
    static void MenuPrincipalAdmin(){
        int opc;
        Admin objAdmin;
        Farmacia objFarmacia;

        do {
            system("cls");
            Banner::header();
            Banner::bannerPrincipalAdmin();
            cin >> opc;
            switch (opc) {
                case 1:{
                    VerHistorial();
                    break;
                }
                case 2:
                    objAdmin.RegistroDelPacienteMasJoven();
                    getch();
                    break;
                case 3:
                    objAdmin.RegistroDelPacienteMásViejo();
                    getch();
                    break;
                case 4:{
                    string pass;
                    std::cin.ignore();

                    std::cout<<"Ingrese una contrasena: ";
                    getline(std::cin,pass);
                    objAdmin.BuscarRegistro(pass);
                    
                    getch();
                    break;
                }
                case 5:
                    objFarmacia.ImprimirMedicamentosEnOrden();
                    getch();
                    break;
                case 6:
                    system("cls");
                    return;
            }
            
        } while (opc < 3 || opc > 0);
        
        getch();
    }
};