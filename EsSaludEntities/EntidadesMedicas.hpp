#ifndef __ENTIDADESMEDICAS__
#define __ENTIDADESMEDICAS__
#include <iostream>
#include <string>
#include "Date.hpp"
using std::string;
using std::to_string;

namespace EntidadesMedicas{

    string especialidadesDB[] = {"Medicina interna", "Cardiologia", "Neurologia", "Gastrologia", "Neumologia", "Pediatria",
    "Nefrologia","Pediatria","Psiquiatria", "Oftalmologia", "Inmunologia","Cirugía oral y maxilofacial"};
    string medicamentosDB[] = {"Paracetamol", "Ambroxol", "Ibuprofeno", "Aspirina", "Repriman", "Omeprasol", "Amoxicilina"};

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

        Medicacion(const Medico& medico1) : medicamento(medicamentosDB[rand()%7]) , tiempoPorMedicina(rand() % 8 + 4) {
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

}

#endif