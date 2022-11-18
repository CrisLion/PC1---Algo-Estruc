#ifndef __FECHA__
#define __FECHA__
#include <iostream>
#include <string>
#include <sstream>

struct Date
{
    int year;
    int month;
    int day;

    Date() : year(2022), month(rand()%12 +1), day(rand() % 30 +1) {}

    Date(const Date& other) {
        year = other.year;
        this->month = other.month;
        this->day = other.day; 
    }

    Date(std::string& date){
        std::stringstream total(date);
        std::string auxiliar;

        std::getline(total,auxiliar,'/');
        day = std::stoi(auxiliar);
        std::getline(total,auxiliar,'/');
        month = std::stoi(auxiliar);
        std::getline(total,auxiliar,'/');
        year = std::stoi(auxiliar);
    }

    Date(int day, int month, int year) : day(day), month(month) , year(year) {}

    int gatherDateAtributes() const {
        return this->year * 10000 + this->month * 100 + this->day;
    }

    bool operator>(const Date& other) const { // fech1 > fecha2
        return this->gatherDateAtributes() > other.gatherDateAtributes();   
    }
    bool operator<(const Date& other) const { // fech1 < fecha2
        return this->gatherDateAtributes() < other.gatherDateAtributes();   
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& obj) {
        os << obj.day <<"/" <<obj.month<<"/"<<obj.year;
        return os;
    }
};

#endif