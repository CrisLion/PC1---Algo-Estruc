#ifndef __ENTIDADESMEDICAS__
#define __ENTIDADESMEDICAS__
#include <iostream>
#include <string>
using std::string;

namespace EntidadesMedicas{

    string nombresDB[] = {"Aldo Ramon", "Juan Alberto", "Tony Stark", "Maria Fernanda", "Rodrigo Pedro","Ada Adriana"};
    string apellidosDB[] = {"Rodriguez Mesco", "Alvarez Alvarado", "Solano Sanchez", "Flores Arauco", "Lopez Olivar",
     "Robles Castillo", "Quito Quito", "Quispe Quispe"};
    string especialidadesDB[] = {"Medicina interna", "Cardiologia", "Neurologia", "Gastrologia", "Neumologia", "Pediatría",
    "Nefrología","Pediatria","Psiquiatria", "Oftalmologia", "Inmunología","Cirugía oral y maxilofacial"};

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
                   telefono(to_string(rand()% (900000000) + 100000000)) {}
    };

    struct Cita{
        string fecha;
        Medico objMedico;
        string hora;

        Cita() : fecha(to_string(rand() % (30) +1) + "/" +  to_string(rand() % (12) +1) + "/2022"),
                hora(to_string(rand() % (21 - 6+1) +6) + ":" +  to_string(rand() % (5) +1) + to_string(rand() % (9) +1)) {}
    };

}

#endif