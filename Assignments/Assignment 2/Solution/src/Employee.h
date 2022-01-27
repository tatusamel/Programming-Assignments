#pragma once
#include <iostream>
#include "Date.h"
using namespace std;

class Employee{
private:
    const int emp_num,len_of_srv;
    const bool emp_type; // 0 for temp 1 for permanent
    const string name,surname;
    string title;
    double sal_coef;
    Date birth,apt_date;
public:
    Employee();
    Employee(int emp_num);
    Employee(int emp_num,bool emp_type,string name,string surname,string title,double sal_coef,Date birth,Date aptDate);
    Employee(int emp_num,bool emp_type,string name,string surname,string title,double sal_coef,Date birth,Date aptDate,int len_of_service);
    
    int getEmp_num() const;
    bool getEmp_type() const ;
    string getName()  const;
    string getSurname() const;
    void setTitle(string title);
    string getTitle() const;
    void setSal_coef(double sal_coef);
    double getSal_coef() const;
    int getLenOfSrv() const;
    Date getBirth() const;
    Date getAptDate() const;
    
    friend ostream& operator<<(ostream& stream, Employee& other);

};

class TemporaryEmployee : public Employee
{
public:
    TemporaryEmployee();
    TemporaryEmployee(int emp_num);
    TemporaryEmployee(int emp_num,bool emp_type,string name,string surname,string title,double sal_coef,Date birth,Date aptDate);
    TemporaryEmployee(int emp_num,bool emp_type,string name,string surname,string title,double sal_coef,Date birth,Date aptDate,int len_of_srv);
};

class PermanentEmployee : public Employee
{
public:
    PermanentEmployee();
    PermanentEmployee(int emp_num);
    PermanentEmployee(int emp_num,bool emp_type,string name,string surname,string title,double sal_coef,Date birth,Date aptDate);
    PermanentEmployee(int emp_num,bool emp_type,string name,string surname,string title,double sal_coef,Date birth,Date aptDate,int len_of_srv);
    
};
