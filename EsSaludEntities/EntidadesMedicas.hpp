#ifndef __ENTIDADESMEDICAS__
#define __ENTIDADESMEDICAS__
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "..\AdvancedStructures\AVL_Tree.hpp"
#include "..\AdvancedStructures\HashTable.hpp"
#include "Date.hpp"

using std::string;
using std::to_string;
using std::vector;
using std::ifstream;

namespace EntidadesMedicas{

    string especialidadesDB[] = {"Medicina interna", "Cardiologia", "Neurologia", "Gastrologia", "Neumologia", "Pediatria",
    "Nefrologia","Pediatria","Psiquiatria", "Oftalmologia", "Inmunologia","Cirugía oral y maxilofacial"};
    string medicamentosDB[] = {
            "Paracetamol", "Ambroxol", "Ibuprofeno", "Aspirina", "Repriman", "Omeprazol", "Amoxicilina","Amlodipina",
            "Lansoprazol", "Tolmetina", "ketoprofeno", "Piroxicam", "Sulindaco", "Zanamivir"
        };

    string nombresDB[] = {
            "Hector", "Louis" ,"Javier" ,"Diego" ,"Collen" , "Katy" ,"Jhems" ,"Leonardo" ,"Cristian" ,"Steve",
            "Adal", "Adriel", "Aldo", "Amaro", "Aran", "Ariel", "Asher", "Baco", "Baltasar", "Bastian",
            "Benicio", "Bernal", "Biel", "Camilo", "Cain", "Caetano", "Casiano", "Ciro", "Dante", "Donato",
            "Edan", "Eiden", "Einar", "Enzo", "Farid", "Fausto","Felix","Ferran", "Flavio", "Gael"
        };
    string apellidosDB[] = {
            "Ramirez","Alejo" ,"Alfaro" ,"Belades" , "Rodrigez" , "Martinez" ,"Alvarado" , "Bonifacio" ,"Bertis" ,"Rojas",
            "Gonzales", "Muniooz", "Rojas", "Dias", "Perez", "Solo", "Contreras", "Silva", "Martinez", "Sepulveda",
            "Morales", "Rodriguez", "Lopez", "Fuentes", "Hernandez","Torres", "Araya", "Flores", "Espinoza", "Valenzuela",
            "Castillo", "Tapia", "Reyes", "Gutierres", "Castro", "Pizarro", "Alvarez", "Vasquez", "Sanchez", "Fernandez"
        };

    struct Paciente{
        string DNI;
        string fechaNacimiento;
        string nombres;
        string apellidos;
        string telefono;
        string contrasena;
    };

    struct Medico{
        string nombres;
        string apellidos;
        string telefono;
        string especialidad;
        Medico() : nombres(nombresDB[rand()%40] + " " + nombresDB[rand()%40]), apellidos(apellidosDB[rand()%40] + " " + apellidosDB[rand()%40]), especialidad(especialidadesDB[rand()%12]),
                   telefono(to_string( rand()% 100000000 + 999000000 )) {}
        Medico(const Medico& medico1){ // copy contructor
            nombres = medico1.nombres;
            apellidos = medico1.apellidos;
            telefono = medico1.telefono;
            especialidad = medico1.especialidad;
        }
        friend std::ostream& operator<<(std::ostream& COUT, const Medico& obj) {
            COUT << obj.especialidad;
            return COUT;
        }
    };

    struct Medicacion{
        Medico objMedico;
        string medicamento;
        int tiempoPorMedicina;

        Medicacion(const Medico& medico1) : medicamento(medicamentosDB[rand()%14]) , tiempoPorMedicina(rand() % 8 + 4) {
            objMedico = Medico(medico1);
        }

        bool operator<(const Medicacion& other) const {
            return this->medicamento.compare(other.medicamento) < 0;
        }
        bool operator>(const Medicacion& other) const {
            return this->tiempoPorMedicina > other.tiempoPorMedicina;
        }
        friend std::ostream& operator<<(std::ostream& COUT, const Medicacion& obj) {
            COUT << obj.medicamento << "\t   "<< obj.tiempoPorMedicina << " horas\tDr. " << obj.objMedico.apellidos << " " << obj.objMedico.nombres ;
            return COUT;
        }
        Medicacion(){}
    };
    struct Cita{
        //string fecha;
        Medico objMedico;
        string hora;
        Date fecha;

        Cita() : fecha(Date()),  hora(to_string(rand() % (21 - 6+ 1) + 6) + ":" +  to_string(rand() % (5) + 1) + to_string(rand() % (9) + 1)), objMedico(Medico()){}

        Cita(const Cita& cita1) {
            //fecha = cita1.fecha;
            objMedico = cita1.objMedico;
            hora = cita1.hora;
            fecha = cita1.fecha;
        }

        friend std::ostream& operator<<(std::ostream& COUT, const Cita& obj) {
            COUT <<" La cita sera el dia: " << obj.fecha << "\n\t  En la especialidad de: " << obj.objMedico.especialidad;
            return COUT;
        }
    };

    struct Registro{
        string DNI;
        Date fechaNacimiento;
        string nombres;
        string apellidos;
        string telefono;
        string contrasena;
    };

    struct Medicamento {
        string nombre;
        int stock;
    };

    class Farmacia{
    private:
        AVL_T<Medicamento>* arbol;

    public:

        Farmacia(){
            auto print = [] (const Medicamento& medicamento) -> void {std::cout<<"Nombre: "<<medicamento.nombre<<" / Stock: "<<medicamento.stock<<std::endl;};
            auto compare = [] (const Medicamento& medicamento1, const Medicamento& medicamento2) -> bool {return medicamento1.stock > medicamento2.stock;};

            arbol = new AVL_T<Medicamento>(print,compare);

            for(int i = 0; i < 14; i++){
                arbol->insert({medicamentosDB[i],rand() % 800 + 80});
            }
        }

        ~Farmacia(){
            delete arbol;
        }

        void ImprimirMedicamentosEnOrden(){
            arbol->InOrder();
        }
    };

    class Admin{
    private:
        vector<Registro> temporal;
        AVL_T<Registro>* tree;
        HashTable<Registro>* ht;

    private:
        void _ObtenerDatos(){
            //Apertirar txt en modo lectura
            ifstream myFile;
            string line;
            myFile.open("../Registros/Usuarios.txt");
            
            while(std::getline(myFile,line)){

                std::stringstream total(line);
                string word;
                

                string DNI;
                string fecha;
                string nombres;
                string apellidos;
                string telefono;
                string contrasena;

                std::getline(total,DNI,',');
                std::getline(total,fecha,',');
                std::getline(total,nombres,',');
                std::getline(total,apellidos,',');
                std::getline(total,telefono,',');
                std::getline(total,contrasena,',');
            

                Registro obj = {DNI,Date(fecha),nombres,apellidos,telefono,contrasena};
                temporal.emplace_back(obj); //->llenar datos en el vector // O(n)      
            }
            myFile.close();

            for(Registro &registro : temporal){

                string key = "";
                key += registro.contrasena[0];
                key += registro.contrasena[1];
                key += registro.contrasena[2];
                key += registro.contrasena[3]; 

                tree->insert(registro); //->llenar el arbol a partir del vector // O(n*log(n))
                ht->insert(key, registro); //->llenar la hashtable a partir del vector // O(n*m) n: los registros, m: el tam de la lista colisionada
            }

            //Limpiando el temporal
            temporal.clear();
        }

    public:
        //Metodos
        Admin(){
            auto print = [] (const Registro& registro) -> void {std::cout<<registro.fechaNacimiento<<" "<<registro.nombres<<" "<<registro.apellidos<<" // ";};
            auto compare = [] (const Registro& registro1, const Registro& registro2) -> bool {return registro1.fechaNacimiento > registro2.fechaNacimiento; };
            
            tree = new AVL_T<Registro>(print,compare);
            ht = new HashTable<Registro>(pow(10,6),print);
            _ObtenerDatos();
        }

        ~Admin(){
            delete tree;
            delete ht;
        }

        void RegistroDelPacienteMasJoven(){
            Registro registro = tree->getMax();
            std::cout<<"Paciente mas joven: "<<std::endl;
            std::cout<<registro.fechaNacimiento<<" "<<registro.nombres<<" "<<registro.apellidos<<std::endl;
        }

        void RegistroDelPacienteMásViejo(){
            Registro registro = tree->getMin();
            std::cout<<"Paciente mas viejo: "<<std::endl;
            std::cout<<registro.fechaNacimiento<<" "<<registro.nombres<<" "<<registro.apellidos<<std::endl;
        }

        void BuscarRegistro(string& key){
            Registro registroEncontrado = (*ht)[key];
            std::cout<<"Registro solicitado: "<<std::endl;
            std::cout<<registroEncontrado.fechaNacimiento<<" "<<registroEncontrado.nombres<<" "<<registroEncontrado.apellidos<<std::endl;
        }

    };

}

#endif