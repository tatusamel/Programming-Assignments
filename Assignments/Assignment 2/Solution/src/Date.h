#pragma once
#include <iostream>
using namespace std;

class Date{
private:
    int day,month,year;
public:
    Date();
    Date(string date);
    void setDate(string str);
    
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    
    bool operator==(const Date& other);
    bool operator<(const Date& other);
    bool operator>(const Date& other);
    bool operator<=(const Date& other);
    bool operator>=(const Date& other);
    friend ostream& operator<<(ostream& stream, Date& other) ;

};

