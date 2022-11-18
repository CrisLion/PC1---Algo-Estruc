#ifndef __BANNER__
#define __BANNER__
#include <iostream>

using std::cout;
using std::string;

struct Banner {
    static void header(){
        cout << "========================================\n";
        cout << "|               EsLaSalud              |\n";
        cout << "========================================\n";
        cout << "                                        \n";
    }
    static void bannerInicial(){
        cout << "        ========================        \n";
        cout << "        |   (1) => Ingresar    |        \n";
        cout << "        |   (2) => Registrase  |        \n";
        cout << "        |   (3) => Salir       |        \n";
        cout << "        ========================        \n";
        cout << "                                        \n";
    }
    static void bannerPrincipalUser(string nombrePaciente) {
        cout << "Hola "<< nombrePaciente << '\n';
        cout << "        ========================        \n";
        cout << "        |    (1) => Citas      |        \n";
        cout << "        |    (2) => Recetas    |        \n";
        cout << "        |    (3) => Salir      |        \n";
        cout << "        ========================        \n";
        cout << "                                        \n";
    }

    static void bannerPrincipalAdmin() {
        cout << "Hola Admin" << '\n';
        cout << "        =========================        \n";
        cout << "        |   (1) => Historial             |        \n";
        cout << "        |   (2) => Paciente mas joven    |        \n";
        cout << "        |   (3) => Paciente mas viejo    |        \n";
        cout << "        |   (4) => Buscar Paciente       |        \n";
        cout << "        |    (5) => Salir                |        \n";
        cout << "        =========================        \n";
        cout << "                                         \n";
    }

    static void bannerCitas() {
        cout << "      ============================      \n";
        cout << "      |   (1) => Reservar cita   |      \n";
        cout << "      |   (2) => Ver mi cita     |      \n";
        cout << "      |      (3) => Salir        |      \n";
        cout << "      ============================      \n";
        cout << "                                        \n";
    }

    static void bannerEspera(const int& tam){
        cout << "      ============================      \n";
        cout << "      |       "<< tam <<" en la cola       |      \n";
        cout << "      |      Espere su turno     |       \n";
        cout << "      |            0.0           |      \n";
        cout << "      ============================      \n";
        cout << "                                        \n";
    }
};

#endif