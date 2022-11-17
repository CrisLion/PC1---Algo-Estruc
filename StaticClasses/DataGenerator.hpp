#ifndef __DATAGENERATOR__
#define __DATAGENERATOR__
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>

using std::cout;
using std::string;
using std::to_string;
using std::ofstream;

struct DataGenerator {
    static void GeneradorDatos(){
        string nombres[] = {
            "Hector", "Louis" ,"Javier" ,"Diego" ,"Collen" , "Katy" ,"Jhems" ,"Leonardo" ,"Cristian" ,"Steve",
            "Adal", "Adriel", "Aldo", "Amaro", "Aran", "Ariel", "Asher", "Baco", "Baltasar", "Bastian",
            "Benicio", "Bernal", "Biel", "Camilo", "Cain", "Caetano", "Casiano", "Ciro", "Dante", "Donato",
            "Edan", "Eiden", "Einar", "Enzo", "Farid", "Fausto","Felix","Ferran", "Flavio", "Gael"
        };
        string apellidos[] = {
            "Ramirez","Alejo" ,"Alfaro" ,"Belades" , "Rodrigez" , "Martinez" ,"Alvarado" , "Bonifacio" ,"Bertis" ,"Rojas",
            "Gonzales", "Muniooz", "Rojas", "Dias", "Perez", "Solo", "Contreras", "Silva", "Martinez", "Sepulveda",
            "Morales", "Rodriguez", "Lopez", "Fuentes", "Hernandez","Torres", "Araya", "Flores", "Espinoza", "Valenzuela",
            "Castillo", "Tapia", "Reyes", "Gutierres", "Castro", "Pizarro", "Alvarez", "Vasquez", "Sanchez", "Fernandez"
        };

        string numeros[10] = { "0","1","2","3","4","5","6","7","8","9" };

        string clave[33] = { "1","3","5","7","9","G","E","d","w","p","&","*","_","Y",
           "L","g","c","s","#","q","z","u","i","o","P","n","M","B","X","Z","R","H","k" };

        string aux = "";

        for (int i = 0; i < pow(10,6); i++) {

            //Appending a DNI
            for (int i = 0; i < 9; i++) {
                aux += numeros[rand() % 10];
            }
            aux += ",";

            //Appending the date
            int dia = (rand() % 31) + 1;
            if (dia < 10)
                aux += '0' + to_string(dia) + '/';
            else
                aux += to_string(dia) + '/';
            int mes = rand() % 12 + 1;
            if (mes < 10)
                aux += '0' + to_string(mes) + '/';
            else
                aux += to_string(mes) + '/';
            aux += to_string((rand() % 63) + 1960);
            aux += ",";

            //Appending a name
            aux += nombres[rand() % 40];
            aux += ",";

            //Appending a last name
            aux += apellidos[rand() % 40];
            aux += ",";

            //Appending the telephone
            aux += to_string((rand() % 40000000) + 960000000);
            aux += ",";

            //Appending the password
            for (int i = 0; i < 9; i++) {
                aux += clave[rand() % 33];
            }
            aux += "\n";
        }

        std::ofstream myFile;
        myFile.open("../Registros/Usuarios.txt");
        myFile<<aux;
        myFile.close();
    }
};

#endif
