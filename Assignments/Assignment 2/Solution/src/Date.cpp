
#include "Date.h"
#include <iostream>
#include <string.h>

using namespace std;

Date::Date(){};
Date::Date(string str){
    this->setDate(str);
};

int Date::getDay() const{
    return this->day;
}

int Date::getMonth() const{
    return this->month;
}

int Date::getYear() const{
    return this->year;
}

void Date::setDate(string str) {
    this->day = stoi(str.substr(0,2));
    this->month = stoi(str.substr(3,2));
    this->year = stoi(str.substr(6,4));
}

// is equal operator
bool Date::operator==(const Date& other) {
    return (this->day==other.getDay() && this->month==other.getMonth() && this->year==other.getYear());
}
// is less than operator
bool Date::operator<(const Date& other){
    
    if (this->year < other.getYear()){
        return true;
    }else if (other.getYear() < this->year){
        return false;
    }else{ // if the years are the same
        
        if (this->month < other.getMonth()){
            return true;
        }else if (other.getMonth() < this->getMonth()){
            return false;
        }else { // if both the years and the months are the same
            
            if (this->day < other.getDay()){
                return true;
            }else if(other.getDay() < this->day){
                return false;
            }else{ // if all the parameters are equal then they're equal too.
                return false;
            }
        }
    }
}
// is greater than operator
bool Date::operator>(const Date& other){
    
    if (this->year > other.getYear()){
        return true;
    }else if (other.getYear() > this->year){
        return false;
    }else{ // if the years are the same
        
        if (this->month > other.getMonth()){
            return true;
        }else if (other.getMonth() > this->getMonth()){
            return false;
        }else { // if both the years and the months are the same
            
            if (this->day > other.getDay()){
                return true;
            }else if(other.getDay() > this->day){
                return false;
            }else{ // if all the parameters are equal then they're equal too.
                return false;
            }
        }
    }
}
// is less than and equal to operator
bool Date::operator<=(const Date& other){
    
    if (this->year < other.getYear()){
        return true;
    }else if (other.getYear() < this->year){
        return false;
    }else{ // if the years are the same
        
        if (this->month < other.getMonth()){
            return true;
        }else if (other.getMonth() < this->getMonth()){
            return false;
        }else { // if both the years and the months are the same
            
            if (this->day < other.getDay()){
                return true;
            }else if(other.getDay() < this->day){
                return false;
            }else{ // if all the parameters are equal then they're equal too.
                return true;
            }
        }
    }
}
// is greater than and equal to operator
bool Date::operator>=(const Date& other){
    
    if (this->year > other.getYear()){
        return true;
    }else if (other.getYear() > this->year){
        return false;
    }else{ // if the years are the same
        
        if (this->month > other.getMonth()){
            return true;
        }else if (other.getMonth() > this->getMonth()){
            return false;
        }else { // if both the years and the months are the same
            
            if (this->day > other.getDay()){
                return true;
            }else if(other.getDay() > this->day){
                return false;
            }else{ // if all the parameters are equal then they're equal too.
                return true;
            }
        }
    }
}

ostream& operator<<(ostream& stream, Date& other) {
    
    if (other.getDay() < 10){
        stream << "0" << other.getDay() << "-";
    }else{
        stream << other.getDay() << "-";
    }
    if (other.getMonth() < 10){
        stream << "0" << other.getMonth() << "-";
    }else {
        stream << other.getMonth() << "-";
    }
    stream << other.getYear();
    
    return stream;
}

