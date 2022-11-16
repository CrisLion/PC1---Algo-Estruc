#ifndef __CONTROLADORA__
#define __CONTROLADORA__

#include <conio.h>
#include "../EsSaludEntities/EntidadesMedicas.hpp"
#include "../StaticClasses/Verificador.hpp"
#include "../StaticClasses/FileHandler.hpp"
#include "../DoubleNodeStructures/ListaCD.hpp"
#include "../SimpleNodeStructures/Cola.hpp"
#include "../AdvancedSorting/SortingAlgorithms.hpp"

#define CANTIDAD_CITAS 10
#define CANTIDAD_MAX_COLA 5
#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77
#define ENTER 13
#define ESC 27

using std::cout;
using std::vector;
using namespace EntidadesMedicas;
using namespace SortingAlgorithms;

class Controladora{
private:
    Paciente* objPaciente;
    ListaCD<Cita> citasReservadas;
    ListaCD<Medicacion> medicacionesDelPaciente;
    Cola<Paciente> colaEspera;

    vector<Cita> citasReservadasV;
    vector<Medicacion> medicacionesDelPacienteV;

    void header(){
        cout << "========================================\n";
        cout << "|               EsLaSalud              |\n";
        cout << "========================================\n";
        cout << "                                        \n";
    }
    void bannerInicial(){
        cout << "        ========================        \n";
        cout << "        |   (1) => Ingresar    |        \n";
        cout << "        |   (2) => Registrase  |        \n";
        cout << "        |   (3) => Historial   |        \n";
        cout << "        |   (4) => Salir       |        \n";
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

    void bannerEspera(const int& tam){
        cout << "      ============================      \n";
        cout << "      |       "<< tam <<" en la cola       |      \n";
        cout << "      |      Espere su turno     |       \n";
        cout << "      |            0.0           |      \n";
        cout << "      ============================      \n";
        cout << "                                        \n";
    }

    void GenerarCola(int n){ //rand() % CANTIDAD_MAX_COLA +1
        if (n == 0) return;
        this->colaEspera.enQueue(Paciente());
        GenerarCola(--n);
    }

    void Descolar(){
        do{
            system("cls");
            bannerEspera(this->colaEspera.Size());
            this->colaEspera.deQueue();
            _sleep(2000);
        }while(this->colaEspera.Size() != 0);
    }

    void VerHistorial(){
        system("cls");
        header();
        Pila<string> pilaHistorial;
        FileHandler::LoadHistory("../Registros/Historial.txt",pilaHistorial);
        auto PrintValue = [] (string &a) ->void {cout<<a<<endl;};
        pilaHistorial.seek(PrintValue);
        getch();
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
            FileHandler::LoadData("../Registros/Usuarios.txt",DNI, objPaciente);
            //Dando los datos necesarios para el llenado de mi historial txt
            Lista<string> temporal;
            temporal.push_back(objPaciente->DNI);
            temporal.push_back(objPaciente->nombres);
            temporal.push_back(objPaciente->apellidos);
            FileHandler::saveData("../Registros/Historial.txt",temporal);

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

        FileHandler::saveData("../Registros/Usuarios.txt",temporal);
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
                case 3:
                    VerHistorial(); break;
                default:
                    system("cls");
            }
        } while(opc != 4);
    }

    void reservarCitas(){ // Interaccion

        GenerarCola(rand() % CANTIDAD_MAX_COLA +1);
        Descolar();

        system("cls");
        header();
        
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

            cout<<"INTRO Seleccionar esta cita"<<endl;
            cout<<"->    Siguiente"<<endl;
            cout<<"<-    Atras"<<endl;
            cout<<"ESC   Salir"<<endl;

            switch(getch()){
                case ENTER:
                    citasReservadas.push_back(Cita(*iter)); 
                    medicacionesDelPaciente.push_back(Medicacion((*iter).objMedico));

                    citasReservadasV.push_back(Cita(*iter)); 
                    medicacionesDelPacienteV.push_back(Medicacion((*iter).objMedico));
                    return; break;
                case DERECHA:
                    ++iter; break;
                case IZQUIERDA:
                    --iter; break;
                case ESC:
                    return ;
            }

        }while(true);
    }


    void verMisCitas(){
        system("cls");
        header();
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

            
            cout<<"-> Siguiente"<<endl;
            cout<<"<- Atras"<<endl;
            cout<<"^ Ordenar por fecha"<<endl;
            cout<<"ESC Salir"<<endl;
            
            switch(getch()){
                case DERECHA:
                    ++iter; break;
                case IZQUIERDA:
                    --iter; break;
                case ARRIBA:
                    {
                        auto compare = [] (Cita& a, Cita& key) -> bool {return a.fecha > key.fecha;};
                        citasReservadas.Sort(compare);
                        iter = citasReservadas.begin();
                        break;
                    }
                case ESC:
                    return;
            }
        }while(true);
    }

    void verMisMedicaciones(){ // solo lectura
        system("cls");
        header();
        
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

            cout<<"-> Siguiente"<<endl;
            cout<<"<- Atras"<<endl;
            cout<<"/\\ Ver registro: "<<endl;
            cout<<"ESC Salir"<<endl;
           
            switch(getch()){
                case DERECHA:
                    ++iter; break;
                case IZQUIERDA:
                    --iter; break;
                case ARRIBA:{
                    VerRegistrio();
                    break;
                }
                case ESC:
                    return ;
            }

        }while(true);
    }

    void VerRegistrio(){
        system("cls");
        header();
        auto compare = [](const Medicacion& a,const  Medicacion& b) -> bool  {
            return a < b;
        };
        quickSort<Medicacion>(medicacionesDelPacienteV, compare, 0, medicacionesDelPacienteV.size() - 1);
        // MergeSort<Medicacion>(medicacionesDelPacienteV, compare, 0 , medicacionesDelPacienteV.size() - 1);

        for (int  i = 0; i < medicacionesDelPacienteV.size(); i++)
        {
            std::cout << medicacionesDelPacienteV.at(i) << '\n';
        }
        cin.get();
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
                if(citasReservadas.size() != 0) verMisCitas();
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
                    if(medicacionesDelPaciente.size() != 0) verMisMedicaciones();
                    break;                
                case 3:
                system("cls");
                return;
            }
        } while(opc != 3);  
    }
};
#endif