#ifndef __ENTIDADESMEDICAS__
#define __ENTIDADESMEDICAS__
#include <iostream>
#include <string>
#include "Date.hpp"
using std::string;
using std::to_string;

namespace EntidadesMedicas{

    string nombresDB[] = {"Aldo Ramon", "Juan Alberto", "Tony Stark", "Maria Fernanda", "Rodrigo Pedro","Ada Adriana"};
    string apellidosDB[] = {"Rodriguez Mesco", "Alvarez Alvarado", "Solano Sanchez", "Flores Arauco", "Lopez Olivar",
     "Robles Castillo", "Quito Quito", "Quispe Quispe"};
    string especialidadesDB[] = {"Medicina interna", "Cardiologia", "Neurologia", "Gastrologia", "Neumologia", "Pediatría",
    "Nefrología","Pediatria","Psiquiatria", "Oftalmologia", "Inmunología","Cirugía oral y maxilofacial"};
    string medicamentosDB[] = {"Panadol", "Ambroxol", "Ibuprofeno", "Aspirina", "Repriman", "Omeprasol", "Amoxicilina"};

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
        Medico() : nombres(nombresDB[rand()%6]), apellidos(apellidosDB[rand()%8]), especialidad(especialidadesDB[rand()%12]),
                   telefono(to_string( rand()% 100000000 + 999000000 )) {}
        Medico(const Medico& medico1){ // copy contructor
            nombres = medico1.nombres;
            apellidos = medico1.apellidos;
            telefono = medico1.telefono;
            especialidad = medico1.especialidad;
        }
    };

    struct Medicacion{
        Medico objMedico;
        string medicamento;

        Medicacion(const Medico& medico1) :medicamento(medicamentosDB[rand()%7]) {
            objMedico = Medico(medico1);
        }

        bool operator<(const Medicacion& other) const {
            return this->medicamento.compare(other.medicamento) < 0;
        }
        friend std::ostream& operator<<(std::ostream& COUT, const Medicacion& obj) {
            COUT << obj.medicamento << "\tDr. " << obj.objMedico.apellidos << " " << obj.objMedico.nombres ;
            return COUT;
        }
        Medicacion(){}
    };
    struct Cita{
        //string fecha;
        Medico objMedico;
        string hora;
        Date fecha;

        Cita() : fecha(Date()),  hora(to_string(rand() % (21 - 6+1) +6) + ":" +  to_string(rand() % (5) +1) + to_string(rand() % (9) +1)), objMedico(Medico()){}

        Cita(const Cita& cita1) {
            //fecha = cita1.fecha;
            objMedico = cita1.objMedico;
            hora = cita1.hora;
            fecha = cita1.fecha;
        }
    };

}

#endif