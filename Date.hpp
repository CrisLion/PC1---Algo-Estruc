#ifndef __FECHA__
#define __FECHA__
#include "Librerias.hpp"

struct Date
{
    int year;
    int month;
    int day;

    Date() : year(2022), month(rand()%12 +1), day(rand() % 30 +1) {}

    Date(const Date& other) {
        year = 2022;
        this->month = other.month;
        this->day = other.day; 
    }

    int gatherDateAtributes() const {
        return this->year * 10000 + this->month * 100 + this->day;
    }

    bool operator>(Date& other){ // fech1 < fecha2
        return this->gatherDateAtributes() > other.gatherDateAtributes();   
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& obj) {
        os << obj.day <<"/" <<obj.month<<"/"<<obj.year;
        return os;
    }
};

#endif