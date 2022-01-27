
#include "Date.h"
#include "Employee.h"
using namespace std;

Employee::Employee()
: emp_num(0), emp_type(0), len_of_srv(0)
{}

Employee::Employee(int emp_num) : emp_num(emp_num), emp_type(0), len_of_srv(0){}

Employee::Employee(int emp_num,bool emp_type,string name,string surname,string title,double sal_coef,Date birth,Date aptDate)
: emp_num(emp_num), emp_type(emp_type), name(name), surname(surname), title(title), sal_coef(sal_coef), apt_date(aptDate),birth(birth), len_of_srv(0)
{}


Employee::Employee(int emp_num,bool emp_type,string name,string surname,string title,double sal_coef,Date birth,Date aptDate,int len_of_srv)
: emp_num(emp_num), emp_type(emp_type), name(name), surname(surname), title(title), sal_coef(sal_coef), apt_date(aptDate),birth(birth), len_of_srv(len_of_srv)
{}

int Employee::getEmp_num() const{
    return this->emp_num;
}

bool Employee::getEmp_type() const{
    return this->emp_type;
}

string Employee::getName() const{
    return this->name;
}

string Employee::getSurname() const{
    return this->surname;
}
void Employee::setTitle(string new_title){
    this->title = new_title;
}
string Employee::getTitle() const{
    return this->title;
}
void Employee::setSal_coef(double sal_coef){
    this->sal_coef = sal_coef;
}
double Employee::getSal_coef() const{
    return this->sal_coef;
}

int Employee::getLenOfSrv() const{
    return this->len_of_srv;
}

Date Employee::getBirth() const{
    return this->birth;
}
Date Employee::getAptDate() const{
    return this->apt_date;
}

ostream& operator<<(ostream& stream, Employee& other){
    stream << other.getEmp_num() << " - " << other.getEmp_type() << " - " << other.getName() << " - " <<  other.getSurname() << " - "
    << other.getTitle() << " - " << other.getSal_coef() << " - ";
    
    if (other.getLenOfSrv()){
        stream << other.getLenOfSrv() << " - ";
    }
    
    stream << other.birth << " - " << other.apt_date;
    
    return stream;
}


TemporaryEmployee::TemporaryEmployee(){}

TemporaryEmployee::TemporaryEmployee(int emp_num): Employee(emp_num) {}

TemporaryEmployee::TemporaryEmployee(int emp_num,bool emp_type,string name,string surname,string title,double sal_coef,Date birth,Date aptDate)
: Employee(emp_num, emp_type, name, surname, title, sal_coef, birth, aptDate)
{}

TemporaryEmployee::TemporaryEmployee(int emp_num,bool emp_type,string name,string surname,string title,double sal_coef,Date birth,Date aptDate,int len_of_srv)
: Employee(emp_num, emp_type, name, surname, title, sal_coef, birth, aptDate, len_of_srv)
{}

PermanentEmployee::PermanentEmployee(){}

PermanentEmployee::PermanentEmployee(int emp_num): Employee(emp_num) {}

PermanentEmployee::PermanentEmployee(int emp_num,bool emp_type,string name,string surname,string title,double sal_coef,Date birth,Date aptDate)
: Employee(emp_num, emp_type, name, surname, title, sal_coef, birth, aptDate)
{}

PermanentEmployee::PermanentEmployee(int emp_num,bool emp_type,string name,string surname,string title,double sal_coef,Date birth,Date aptDate,int len_of_srv)
: Employee(emp_num, emp_type, name, surname, title, sal_coef, birth, aptDate, len_of_srv)
{}
