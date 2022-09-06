#ifndef __CONTROLADORA__
#define __CONTROLADORA__

#include "EntidadesMedicas.hpp"
#include "Verificador.hpp"
#include "FileHandler.hpp"

using std::cout;
using namespace EntidadesMedicas;

class Controladora{
private:
    Paciente* objPaciente;

    void header(){
        cout << "========================================\n";
        cout << "|               EsLaSalud              |\n";
        cout << "========================================\n";
    }
    void bannerInicial(){
        cout << "        ========================        \n";
        cout << "        |    (1) => Ingresar   |        \n";
        cout << "        |   (2) => Registrase  |        \n";
        cout << "        ========================        \n";
        cout << "                                        \n";
    }
    void bannerPrincipal(string nombrePaciente) {
        header();
        cout << "Hola "<< nombrePaciente << '\n';
        cout << "        ========================        \n";
        cout << "        |     (1) => Cita      |        \n";
        cout << "        |    (2) => Receta     |        \n";
        cout << "        ========================        \n";
        cout << "                                        \n";
    }
    
public:
    Controladora() {}
    ~Controladora() { delete objPaciente; }
    
    
    void logIn(){
        system("cls");
        header();
// ---
        string DNI;
        string contrasena;
        static int contador = 3;
        
        //Ingresando los datos
        cout << "Ingrese su DNI: ";
        getline(std::cin,DNI);
        cout << "\nIngrese su contrase" << char(164) << "a: ";
        getline(std::cin,contrasena);

        if(Verificador::verificarUsuario(DNI,contrasena)){
            objPaciente = new Paciente();
            cout << "Usuario verificado\n";
            FileHandler::LoadData("Registros/Usuarios.txt",DNI, objPaciente);
            return;
        }
        else {
            contador--;
            cout << " Usuario no encontrado\n Por favor verifique sus datos\n" ;
            cout << "Te quedan " << contador << " Intentos";
            if (contador== 0) exit(0);
            logIn();
        }
    }

    void SignIn(){        
        string DNI;
        string FechaNacimiento;
        string nombre;
        string apellido;        
        string telefono;        
        string contrasena;
        Lista<string> temporal;

        cout << "Ingresa su DNI: ";
        getline(std::cin,DNI); temporal.push_back(DNI);
        cout << "Ingresa su Fecha de nacimineto: ";
        getline(std::cin,FechaNacimiento); temporal.push_back(FechaNacimiento);
        cout << "Ingresa tu primer nombre: ";
        getline(std::cin,nombre); temporal.push_back(nombre);
        cout << "Ingresa tu primer apellido: ";
        getline(std::cin,apellido); temporal.push_back(apellido);
        cout << "Ingresa su tel" << char(130) << "fono: ";
        getline(std::cin,telefono); temporal.push_back(telefono);
        cout << "\nIngresa su contrase" << char(164) << "a: ";
        getline(std::cin,contrasena); temporal.push_back(contrasena);

        FileHandler::saveData("Registros/Usuarios.txt",temporal);
        system("cls"); //probando
    }

    void display(){
        std::cout<< objPaciente->DNI<<" "<<
                    objPaciente->fechaNacimiento<<" "<<
                    objPaciente->nombres<<" "<<
                    objPaciente->apellidos<<" "<<
                    objPaciente->telefono<<" "<<
                    objPaciente->contrasena<<std::endl;
        getch();
        }

    void IniciarPrograma(){
        int opc;
        header();
        bannerInicial();
        cin>> opc; cin.ignore(1);
        switch (opc){
        case 1: logIn(); display(); break;
        case 2: SignIn(); IniciarPrograma(); break;
        }
    }
    void Citas(){
        header();
        bannerPrincipal(objPaciente->nombres);

    }
};
#endif