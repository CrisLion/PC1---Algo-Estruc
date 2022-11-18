#ifndef __CONTROLADORA__
#define __CONTROLADORA__

#include <conio.h>
#include <math.h>
#include "../EsSaludEntities/EntidadesMedicas.hpp"
#include "../StaticClasses/Verificador.hpp"
#include "../StaticClasses/FileHandler.hpp"
#include "../DoubleNodeStructures/ListaCD.hpp"
#include "../SimpleNodeStructures/Cola.hpp"
#include "../AdvancedSorting/SortingAlgorithms.hpp"
#include "../StaticClasses/Banner.hpp"
#include "../StaticClasses/DataGenerator.hpp"

#define CANTIDAD_CITAS 10
#define CANTIDAD_MAX_COLA 1
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

    void GenerarCola(int n){ //rand() % CANTIDAD_MAX_COLA +1
        if (n == 0) return;
        this->colaEspera.enQueue(Paciente());
        GenerarCola(--n);
    }

    void Descolar(){
        do{
            system("cls");
            Banner::bannerEspera(this->colaEspera.Size());
            this->colaEspera.deQueue();
            _sleep(2000);
        }while(this->colaEspera.Size() != 0);
    }

    void VerHistorial(){
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
    Controladora() {}
    ~Controladora() { delete objPaciente; }
    
    int logIn(){
        system("cls");
        Banner::header();
// ---
        string DNI;
        string contrasena;
        static int contador = 3;
        
        //Ingresando los datos
        cout << "Ingrese su DNI: ";
        getline(std::cin,DNI);
        cout << "Ingrese su contrasena: ";
        getline(std::cin,contrasena);

        if (DNI == "admin" && contrasena == "admin") return 1;

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

            return 2;
        }
        else {
            contador--;
            cout << "\tUsuario no encontrado\n \tPor favor verifique sus datos\n" ;
            cout << "\tTe quedan " << contador << " Intentos";
            getch();
            if (contador== 0) exit(0);
            logIn();
        }
        return 0;
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
        DataGenerator::GeneradorDatos();
        system("cls");
        do{
            Banner::header();
            Banner::bannerInicial();
            cout << "Opcion: ";
            cin>> opc; cin.ignore(1);
            switch (opc){
                case 1:{
                    int aux = logIn();
                    system("cls");
                    if (aux == 1) 
                        MenuPrincipalAdmin();
                    if (aux == 2) 
                        MenuPrincipalUser();
                    break;
                }
                case 2:{
                    SignIn();
                    system("cls");
                    break;
                }
                default:
                    system("cls");
            }
        } while(opc != 3);
    }

    void reservarCitas(){ // Interaccion

        GenerarCola(rand() % CANTIDAD_MAX_COLA +1);
        Descolar();

        system("cls");
        Banner::header();
        
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
            Banner::header();
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
        Banner::header();
        Iterador<Cita> iter = citasReservadas.begin();

        do{
            //Dibujar ficha de Cita
            system("cls");
            Banner::header();
            cout << "==========================================\n";
            cout << "| " << char(190) << " "<< (*iter).objMedico.nombres << ", " << (*iter).objMedico.apellidos << '\n';
            cout << "| " << char(190) << " "<< (*iter).objMedico.especialidad << '\n';
            cout << "| " << char(190) << " Dia de la cita: " << (*iter).fecha << " " <<(*iter).hora << '\n';
            cout << "|                     Contacto: " << (*iter).objMedico.telefono << '\n';
            cout << "==========================================\n";

            
            cout<<"-> Siguiente"<<endl;
            cout<<"<- Atras"<<endl;
            cout<<"/\\ Ordenar por fecha"<<endl;
            cout<<"\\/ Informacion"<<endl;
            cout<<"ESC Salir"<<endl;
            
            switch(getch()){
                case DERECHA:
                    ++iter; break;
                case IZQUIERDA:
                    --iter; break;
                case ARRIBA: {
                        auto compare = [] (const Cita& a,const Cita& key) -> bool {return a.fecha > key.fecha;};
                        citasReservadas.Sort(compare);
                        iter = citasReservadas.begin();
                        break;
                    }
                case ABAJO: {
                    VerCitas();
                    break;
                }
                case ESC:
                    return;
            }
        }while(true);
    }

    void verMisMedicaciones(){ // solo lectura
        system("cls");
        Banner::header();
        
        Iterador<Medicacion> iter = medicacionesDelPaciente.begin();
        do{
            //Dibujar ficha de Receta
            system("cls");
            Banner::header();
            cout << "==========================================\n";
            cout << "| " << char(190) << " "<< (*iter).objMedico.nombres << ", " << (*iter).objMedico.apellidos << '\n';
            cout << "| " << char(190) << " "<< (*iter).objMedico.especialidad << '\n';
            cout << "| " << char(190) << " "<< (*iter).medicamento<< '\n';
            cout << "| " << char(190) << " Tomar cada "<< (*iter).tiempoPorMedicina << " horas" << '\n';
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
                    VerRegistro();
                    break;
                }
                case ESC:
                    return ;
            }

        }while(true);
    }

    void VerRegistro(){
        short opc;
        do {
            system("cls");
            Banner::header();

            cout << "01) Por orden alfabetico\n";
            cout << "02) Por tiempo\n";
            cout << "03) Salir\n";
            cout << "Ingrese la opcion: ";
            
            cin >> opc;
            switch (opc) {
                case 1: {
                    auto compare = [](const Medicacion& a,const  Medicacion& b) -> bool  {
                        return a < b;
                    };
                    quickSort<Medicacion>(medicacionesDelPacienteV, compare, 0, medicacionesDelPacienteV.size() - 1);
                    cout << "==========================================\n";
                    cout << "Medicamento:\tTomar cada:\tRecetado por:\n";
                    for (int  i = 0; i < medicacionesDelPacienteV.size(); i++) {
                        std::cout << i + 1 << "| " << medicacionesDelPacienteV.at(i) << '\n';
                    }
                    cout << "==========================================\n";
                    getch();
                    VerRegistro();
                    break;
                }
                case 2: {
                    auto compare = [](const Medicacion& a,const  Medicacion& b) -> bool  {
                        return a > b;
                    };
                    MergeSort<Medicacion>(medicacionesDelPacienteV, compare, 0 , medicacionesDelPacienteV.size() - 1);
                    cout << "==========================================\n";
                    cout << "Medicamento:\tTomar cada:\tRecetado por:\n";
                    for (int  i = 0; i < medicacionesDelPacienteV.size(); i++) {
                        std::cout << i + 1 << "| " <<  medicacionesDelPacienteV.at(i) << '\n';
                    }
                    cout << "==========================================\n";
                    getch();
                    VerRegistro();
                    break;
                }
                case 3:
                    return;
            }                      
        } while (opc < 3 || opc > 0);
        
    }

    void VerCitas(){
        system("cls");
        Banner::header();
        auto compare = [] (const Cita& a,const Cita& key) -> bool {return a.fecha > key.fecha;};
        HeapSort<Cita>(citasReservadasV,compare);
        cout << "==========================================\n";
        cout << " " << char(190) << " Cita mas proxima:\n \t-";
        cout << " " <<  citasReservadasV.at(0) << '\n';
        cout << " " << char(190) << " Cita mas lejana:\n \t-";
        cout << " " <<  citasReservadasV.at(citasReservadasV.size() - 1) << '\n';
        cout << "==========================================\n";
        getch();

    }
    
    void MenuCitas(){
        int opc;
        do {
            system("cls");
            Banner::header();
            Banner::bannerCitas();
            cin>>opc;
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
            
        } while (opc < 4 || opc > 0);
        
    }

    void MenuPrincipalUser(){ //Aqui hay recursion
        int opc; 
        do{
            system("cls");
            Banner::header();
            Banner::bannerPrincipalUser(objPaciente->nombres);
            cin>>opc;
            if (opc > 3 || opc < 1) {
                std::cout << "Ingrese solo las opciones del menu";
                getch();
                MenuPrincipalUser();
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

    void MenuPrincipalAdmin(){
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
                    string key = "";
                    std::cin.ignore();

                    std::cout<<"Ingrese una contrasena: ";
                    getline(std::cin,pass);
                    
                    key += pass[0];
                    key += pass[1];
                    key += pass[2];
                    key += pass[3];

                    objAdmin.BuscarRegistro(key);
                    
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
#endif