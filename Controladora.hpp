#ifndef __CONTROLADORA__
#define __CONTROLADORA__
#define CANTIDAD_CITAS 10
#include "EntidadesMedicas.hpp"
#include "Verificador.hpp"
#include "FileHandler.hpp"
#include "ListaCD.hpp"

using std::cout;
using namespace EntidadesMedicas;

class Controladora{
private:
    Paciente* objPaciente;
    ListaCD<Cita> citasReservadas;
    ListaCD<Medicacion> medicacionesDelPaciente; 

    void header(){
        cout << "========================================\n";
        cout << "|               EsLaSalud              |\n";
        cout << "========================================\n";
        cout << "                                        \n";
    }
    void bannerInicial(){
        cout << "        ========================        \n";
        cout << "        |    (1) => Ingresar   |        \n";
        cout << "        |   (2) => Registrase  |        \n";
        cout << "        |     (3) => Salir     |        \n";
        cout << "        ========================        \n";
        cout << "                                        \n";
    }
    void bannerPrincipal(string nombrePaciente) {
        cout << "Hola "<< nombrePaciente << '\n';
        cout << "        ========================        \n";
        cout << "        |    (1) => Citas       |        \n";
        cout << "        |    (2) => Recetas     |        \n";
        cout << "        |    (3) => Salir       |        \n";
        cout << "        ========================        \n";
        cout << "                                        \n";
    }

    void bannerCitas() {
        cout << "      ============================      \n";
        cout << "      |   (1) => Reservar cita   |      \n";
        cout << "      |   (2) => Ver mi cita     |      \n";
        cout << "      |      (3) => Salir        |      \n";
        cout << "      ============================      \n";
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
        cout << "Ingrese su contrasena: ";
        getline(std::cin,contrasena);

        if(Verificador::verificarUsuario(DNI,contrasena)){
            objPaciente = new Paciente();
            cout << "Usuario verificado\n";
            FileHandler::LoadData("Registros/Usuarios.txt",DNI, objPaciente);
            return;
        }
        else {
            contador--;
            cout << "\tUsuario no encontrado\n \tPor favor verifique sus datos\n" ;
            cout << "\tTe quedan " << contador << " Intentos";
            getch();
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
        cout << "Ingresa su telefono: ";
        getline(std::cin,telefono); temporal.push_back(telefono);
        cout << "\nIngresa su contrasena: ";
        getline(std::cin,contrasena); temporal.push_back(contrasena);

        FileHandler::saveData("Registros/Usuarios.txt",temporal);
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
        do{
            header();
            bannerInicial();
            cout << "Opcion: ";
            cin>> opc; cin.ignore(1);
            switch (opc){
                case 1: 
                    logIn(); system("cls"); MenuPrincipal();break;
                case 2: 
                    SignIn();system("cls"); break;
            }
        } while(opc != 3);
    }

    void reservarCitas(){ // Interaccion
        system("cls");
        header();
        cout << "Opcion: ";
        int opc;
        ListaCD<Cita> CitasDisponibles;
        for(int i = 0; i < CANTIDAD_CITAS; i++){
            CitasDisponibles.push_back(Cita());
        }

        Iterador<Cita> iter = CitasDisponibles.begin();

        do{
            //Dibujar ficha de cita
            /**
             * Nonbre Apellido  ---- Especialidad
             * Fecha y hora 
             * contacto
             */
            system("cls");
            header();
            cout << "==========================================\n";
            cout << "| " << char(190) << " "<< (*iter).objMedico.nombres << ", " << (*iter).objMedico.apellidos << '\n';
            cout << "| " << char(190) << " "<< (*iter).objMedico.especialidad << '\n';
            cout << "| " << char(190) << " Dia de la cita: " << (*iter).fecha << " " <<(*iter).hora << '\n';
            cout << "|                     Contacto: " << (*iter).objMedico.telefono << '\n';
            cout << "==========================================\n";

            cout<<"1. Seleccionar esta cita"<<endl;
            cout<<"2. Siguiente"<<endl;
            cout<<"3. Atras"<<endl;
            cout<<"4. Salir"<<endl;
            cout<<"Opcion: ";cin>>opc;

            switch(opc){
                case 1:
                    citasReservadas.push_back(Cita(*iter)); 
                    medicacionesDelPaciente.push_back(Medicacion((*iter).objMedico));
                    opc = 4;  break;
                case 2:
                    ++iter; break;
                case 3:
                    --iter; break;
            }

        }while(opc != 4);
    }


    void verMisCitas(){
        system("cls");
        header();
        int opc;
        Iterador<Cita> iter = citasReservadas.begin();

        do{
            //Dibujar ficha de Cita
            system("cls");
            header();
            cout << "==========================================\n";
            cout << "| " << char(190) << " "<< (*iter).objMedico.nombres << ", " << (*iter).objMedico.apellidos << '\n';
            cout << "| " << char(190) << " "<< (*iter).objMedico.especialidad << '\n';
            cout << "| " << char(190) << " Dia de la cita: " << (*iter).fecha << " " <<(*iter).hora << '\n';
            cout << "|                     Contacto: " << (*iter).objMedico.telefono << '\n';
            cout << "==========================================\n";

            
            cout<<"1. Siguiente"<<endl;
            cout<<"2. Atras"<<endl;
            cout<<"3. Salir"<<endl;
            cout<<"Opcion: ";cin>>opc;

            switch(opc){
                case 1:
                    ++iter; break;
                case 2:
                    --iter; break;
            }

        }while(opc != 3);
    }

    void verMisMedicaciones(){ // solo lectura
        system("cls");
        header();
        int opc;
        Iterador<Medicacion> iter = medicacionesDelPaciente.begin();
        do{
            //Dibujar ficha de Receta
            system("cls");
            header();
            cout << "==========================================\n";
            cout << "| " << char(190) << " "<< (*iter).objMedico.nombres << ", " << (*iter).objMedico.apellidos << '\n';
            cout << "| " << char(190) << " "<< (*iter).objMedico.especialidad << '\n';
            cout << "| " << char(190) << " "<< (*iter).medicamento<< '\n';
            cout << "==========================================\n";

            cout<<"1. Siguiente"<<endl;
            cout<<"2. Atras"<<endl;
            cout<<"3. Salir"<<endl;
            cout<<"Opcion: ";cin>>opc;

            switch(opc){
                case 1:
                    ++iter; break;
                case 2:
                    --iter; break;
            }

        }while(opc != 3);
    }

    void MenuCitas(){
        system("cls");
        header();
        bannerCitas();
        int opc; cin>>opc;
        switch (opc){
            case 1:                
                reservarCitas(); break;
                break;
            case 2:
                verMisCitas();
                break;
            case 3:
                system("cls");
                return;
        }
    }

    void MenuPrincipal(){ //Aqui hay recursion
        int opc; 
        
        do{
            system("cls");
            header();
            bannerPrincipal(objPaciente->nombres);
            cin>>opc;
            if (opc > 3 || opc < 1) {
                std::cout << "Ingrese solo las opciones del menu";
                getch();
                MenuPrincipal();
            }

            switch (opc){
                case 1:
                    MenuCitas();                
                    break;
                case 2:
                    verMisMedicaciones();
                    break;
                case 3:
                    system("cls");
                    return;
            }
        } while(opc != 3);  
    }
};
#endif