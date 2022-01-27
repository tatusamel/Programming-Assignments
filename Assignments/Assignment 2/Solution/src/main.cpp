#include <iostream>
#include <set>
#include "CircularArrayLinkedList.h"
#include "DoubleDynamicLinkedList.h"
#include "Employee.h"
using namespace std;


void onlyPrintbyEmployeeNumber(CircularArrayLinkedList& tempEmps, DoubleDynamicLinkedList& permEmps){
    
    int i=0;
    bool doneWithTemps = !tempEmps.getSize(), doneWithPerms = !permEmps.getSize(); // if their size is 0, then we are done with them
    
    // this set will be used to store the indexes of the employees in the permEmps for the program to not
    // take the same value as the minimum. If we print a value then we will store its index in the set and whenever we face it again
    // we will not take it, because we already print it. Otherwise, we'd have printed the same value again and again. And it would be an
    // infinite loop
    
    set<int> mySet;
    
    // while we are not both done with temporaryEmployees and PermanenEmployees
    while ( !doneWithTemps || !doneWithPerms ){
        
        // we have the circular linked list which keeps the temporary employees ordered by their employee numbers
        // but unfortunately, we also have a doubly linked list which keeps the permanent emps. ordered by their appointment date.
        // we'll use a technique that is also used in merge sort, after when we divide all the elements we should apply conquer part.
        // in this part we'll have 2 indexes which are i and j ( they can be thought as pointers too ). One of them will keep the index
        // of the already sorted array, and one of them move between the elements of the non-sorted array which is permEmps in this case
        
        // we first create a temporary employee t1 
        TemporaryEmployee* t1 = new TemporaryEmployee();
        
        // if we are done with all the temporary employees, then we cannot assign its [i]th value to t1, because we'd be out of index
        // so we should check first if are we done with all the tempEmps
        if ( !doneWithTemps ){
            // since temporary employees are ordered by emp_num. the first item will give the employee with the smallest emp_num
            t1 = tempEmps.getEmployee(i);
        }
        
        // before traversing through the permanent Employee list we can first check if all the employees in permEmps list are printed,
        // if they are, then we do not need to find the minimum element of it anymore because all of the elements of that list
        // have been already printed. So in such case,  we'll just keep printing the employees in tempEmps list.
        // this part is not mandatory but saves a lot of time for us, if this part didn't exist, we would had to traverse the permEmps list
        if (doneWithPerms){
            cout << *t1 << endl;
            i++;
            
            if (i == tempEmps.getSize() ){
                doneWithTemps = 1;
            }
            continue;
        }
        
        // if we are here at this point, then it means that we still have permanent employees to be printed
        //we will first find the permanent employee with the minimum emp_number and store it in minEmp
        // initially we set its emp_number to -1, so that means it wasn't set yet
        PermanentEmployee* minEmp = new PermanentEmployee(-1);
        
        // find the permanent employee with the smallest emp_num
        // we should keep the index of the employee with the smallest employee number so that we can later add it to our set
        int last_index = 0;
        for (int j=0; j < permEmps.getSize(); j++){
            
            PermanentEmployee* p1 = permEmps.getEmployee(j);
            
            // there are two possible situation here, but for both of them this employees index shouldn't be in the 'mySet' set
            // case 1 - minEmp employee might have a emp_num = -1 which means we set the smallest employee yet, so we'd set
            // it as the first employee of the list whose index is not in mySet
            // case 2 - if this employee's emp_num is less than the minimum emp_num  and it is not in
            // mySet set then set it as min employee.
            if ( (minEmp->getEmp_num() == -1 || p1->getEmp_num() < minEmp->getEmp_num()) && !mySet.count(j) ) {
                minEmp = p1;
                last_index = j;
            }
        }
        
        // if we are done with the temporary employees, then we do not have to compare it with the employee who has the smallest
        // emp_num of the list tempEmp
        if(doneWithTemps){
            cout << *minEmp << endl;
            mySet.insert(last_index);
            if ( mySet.size() == permEmps.getSize() ){// that means we are now done with permanent Employees. So we'll only check temporary emps.
                doneWithPerms = 1;
            }
            continue;
        }
        
        //after finding the minimum element in permEmps we should compare it with a temporary emp with the least emp num in tempEmps list
        if (  minEmp->getEmp_num() < t1->getEmp_num() ){
            cout << *minEmp << endl;
            mySet.insert(last_index); // if we print it we should insert it to a set so that we will not print it again later.
            
        }else{
            cout << *t1 << endl;
            i++; // we can increase the index of temp employees since we print it.
        }
        
        if ( i == tempEmps.getSize() ){ // that means we are now done with temporary Employees. So we'll only check permanent emps.
            doneWithTemps = 1;
        }
        if ( mySet.size() == permEmps.getSize() ){// that means we are now done with permanent Employees. So we'll only check temporary emps.
            doneWithPerms = 1;
        }
        
    }
}


void onlyPrintbyAppointmentDate(CircularArrayLinkedList& tempEmps, DoubleDynamicLinkedList& permEmps){
    // this function is the vice versa of the function above (mergeAndPrintbyEmployeeNumber). This time, since permanent
    // employees are in order but not temporary employees we will swap the spots.
    // (according to the appointment date), we'll change their spot. And also we changed the comparison criteria from emp_number to appointment date.
    
    int i=0;
    bool doneWithTemps=!tempEmps.getSize(),doneWithPerms = !permEmps.getSize();
    set<int> mySet;
    
    while ( !doneWithTemps || !doneWithPerms ){
        
        PermanentEmployee* p1 = new PermanentEmployee();
        if(!doneWithPerms){ // if perm employees are not done, then we can set a value into it, otherwise we'll get index out of bounds exception
            p1 =permEmps.getEmployee(i);
        }
        
        if (doneWithTemps){
            cout << *p1 << endl;
            i++;
            
            if (i == permEmps.getSize()){
                doneWithPerms = 1; // it basically means break
            }
            continue;
        }
        
        // if we are at this point we still have some temporary employees to be printed
        TemporaryEmployee* minEmp = new TemporaryEmployee(-1);// which means it hasn't been set yet
        
        int last_index = 0;
        for (int j=0; j < tempEmps.getSize(); j++){
            
            TemporaryEmployee* t1 = tempEmps.getEmployee(j);
            
            if ( ( minEmp->getEmp_num() == -1 || t1->getAptDate() < minEmp->getAptDate() ) && !mySet.count(j)) {
                minEmp = t1;
                last_index = j;
            }
        }
        if(doneWithPerms){
            cout << *minEmp << endl;
            mySet.insert(last_index);
            if( mySet.size() == tempEmps.getSize()){
                doneWithTemps = 1;
            }
            continue;
        }
        
        // if we are here, then we are not done with both of them either, so check which one has the smaller empnum
        if ( minEmp->getAptDate() < p1->getAptDate() ){
            cout << *minEmp << endl;
            mySet.insert(last_index);
        }else{
            cout << *p1 << endl;
            i++;
        }
        
        if( i== permEmps.getSize()){
            doneWithPerms = 1;
        }
        if ( mySet.size() == tempEmps.getSize()) {
            doneWithTemps = 1;
        }
    }
}

void printAfterAppointmentDate(Date& d1,CircularArrayLinkedList& tempEmps, DoubleDynamicLinkedList& permEmps){
    // this function is the same as the function above. Yet, at the end we'll check, before printing, if the date is
    // greater than the d1 which is a parameter Date object. If it is greater than t1, we can print it. It it is less than d1
    // then, it means that employee is assigned to the instutition before d1, so we cannot print it.
    
    // and it also says we should print them in order from new to end so we should first print the employee with the greates aptDate
    // namely from NEWEST to OLDEST
    
    int i = permEmps.getSize()-1; // since we start checking from the greates appointment date
    
    bool doneWithTemps=!tempEmps.getSize(),doneWithPerms = !permEmps.getSize();
    set<int> mySet;
    
    while ( !doneWithTemps || !doneWithPerms ){
        
        
        PermanentEmployee* p1 = new PermanentEmployee();
        if(!doneWithPerms){ // if perm employees are not done, then we can set a value into it, otherwise we'll get index out of bounds exception
            p1 =permEmps.getEmployee(i);
        }
        
        if (doneWithTemps){
            if ( d1 < p1->getAptDate() ){
                cout << *p1 << endl;
            }
            i--;
            
            if (i < 0){
                doneWithPerms = 1; // it basically means break
            }
            continue;
        }
        
        TemporaryEmployee* maxEmp = new TemporaryEmployee(-1);
        

        int last_index = 0;
        for (int j=0; j < tempEmps.getSize(); j++){
            
            TemporaryEmployee* t1 = tempEmps.getEmployee(j);
            
            if ( (maxEmp->getEmp_num() == -1 || maxEmp->getAptDate() < t1->getAptDate() ) && !mySet.count(j)) {
                maxEmp = t1;
                last_index = j;
            }
            
        }
        
        if(doneWithPerms){
            if ( d1 < maxEmp->getAptDate()){
                cout << *maxEmp << endl;
            }
            mySet.insert(last_index);
            if( mySet.size() == tempEmps.getSize()){
                doneWithTemps = 1;
            }
            continue;
        }
        
        if ( p1->getAptDate() < maxEmp->getAptDate()  ){
            if ( d1 < maxEmp->getAptDate() ){
                cout << *maxEmp << endl;
                mySet.insert(last_index);
            }
        }else{
            if ( d1 < p1->getAptDate()){
                cout << *p1 << endl;
                i--;
            }
        }
        
        // if both employee of each list with the greatest aptDate is less than the date d1 we should break the loop
        if ( maxEmp->getAptDate() < d1 && p1->getAptDate() < d1){
            break;
        }
        
        if ( i < 0) {
            doneWithPerms = 1;
        }
        if (mySet.size() == tempEmps.getSize()){
            doneWithTemps = 1;
        }
    }
}

void printEmployeesInGivenYear(int year, CircularArrayLinkedList& tempEmps, DoubleDynamicLinkedList& permEmps){
    
    // this function will list the employees assigned to the institution in a given year from OLDEST to NEWEST
    int i=0; // since it is from oldest to newest, we should first look for the employee with the smallest aptDate in a given year.
    
    bool doneWithTemps=!tempEmps.getSize(),doneWithPerms = !permEmps.getSize();
    set<int> mySet;

    
    while ( !doneWithTemps || !doneWithPerms ){
        
        PermanentEmployee* p1 = new PermanentEmployee();
        if (!doneWithPerms){
            p1 = permEmps.getEmployee(i);
        }
        
        if (doneWithTemps){
            if ( p1->getAptDate().getYear() == year ){
                cout << *p1 << endl;
            }
            i++;

            if (i == permEmps.getSize()){
                doneWithPerms = 1; // it basically means break
            }
            continue;
        }
        
        TemporaryEmployee* minEmp = new TemporaryEmployee(-1);
    
        // find the employee with the smallest aptDate and set it as minEmp
        int last_index = 0;
        for (int j=0; j < tempEmps.getSize(); j++){
            
            TemporaryEmployee* t1 = tempEmps.getEmployee(j);
            
            if ( (minEmp->getEmp_num() == -1 || t1->getAptDate() < minEmp->getAptDate()) && !mySet.count(j)) {
                minEmp = t1;
                last_index = j;
            }
        }
        
        if(doneWithPerms){
            if ( minEmp->getAptDate().getYear() == year){
                cout << *minEmp << endl;
            }
            mySet.insert(last_index);
            if( mySet.size() == tempEmps.getSize()){
                doneWithTemps = 1;
            }
            continue;
        }
        
        // check both of the list's employees with the smallest aptDates, decide which of them is smaller, then check if the smallest one is
        // in the given year, if it is in given year, then, we can print it, if it is not, we should pass it as if we printed it.
        if (  minEmp->getAptDate() < p1->getAptDate() ){
            if ( minEmp->getAptDate().getYear() == year ){
                cout << *minEmp << endl;
            }
            mySet.insert(last_index); // even though this number is not in the given year, we should pass it as if we printed it,
                                      //otherwise it will be a infinite loop
        }else{
            if ( p1->getAptDate().getYear() == year ){
                cout << *p1 << endl;
            }
            i++; // we should pass this number since it is not in the given year even if we printed it or not.
        }
        
        if ( i == permEmps.getSize()) {
            doneWithPerms = 1;
        }
        if (mySet.size() == tempEmps.getSize()){
            doneWithTemps = 1;
        }
    }
}
void printEmployeesBornBeforeCertainDateInEmpnumOrder(Date& d1,CircularArrayLinkedList& tempEmps, DoubleDynamicLinkedList& permEmps){
    
    // in this function, our goal is to first find the employee with the minimum employee number, and print it if its birth date is less
    // than the date we're given
    
    int i=0;
    bool doneWithTemps=!tempEmps.getSize(),doneWithPerms = !permEmps.getSize();
    set<int> mySet;

    
    while ( !doneWithTemps || !doneWithPerms ){
        
        TemporaryEmployee* t1 = new TemporaryEmployee();
        if (!doneWithTemps){
            t1 = tempEmps.getEmployee(i);
        }
        
        //before starting the permanent Employee list we can first check if all the employees in permEmps list are printed, if they are, then we do not
        // need to find the minimum element of it anymore because all of the elements of thatt list have been already printed. So in such case,
        // we'll just keep printing the employees in tempEmps list.
        if (doneWithPerms){
            if ( t1->getBirth() < d1){
                cout << *t1 << endl;
            }
            i++;
            if ( i == tempEmps.getSize()){
                doneWithTemps = 1;
            }
            continue;
        }
        
        PermanentEmployee* minEmp = new PermanentEmployee(-1); // which means minEmp is not initialized yet from my perspective

        int last_index = 0;
        for (int j=0; j < permEmps.getSize(); j++){
            
            PermanentEmployee* p1 = permEmps.getEmployee(j);
            
            // if this employee's emp_num is less than the minimum emp_num then set it as min employee
            if ( (minEmp->getEmp_num() == -1 || p1->getEmp_num() < minEmp->getEmp_num()) && !mySet.count(j)) {
                minEmp = p1;
                last_index = j;
            }
        }
        
        //after finding the minimum element in permEmps
        if (doneWithTemps){
            if (minEmp->getBirth() < d1){
                cout << *minEmp << endl;
            }
            mySet.insert(last_index);
            if (mySet.size() == permEmps.getSize()){
                doneWithPerms = 1;
            }
            continue;
        }
        
        // if we are here, then, it means that we still have at least one employee from both of them, so we should check which one is smaller
        if (  minEmp->getEmp_num() < t1->getEmp_num() ){
            
            if ( minEmp->getBirth() < d1 ){
                cout << *minEmp << endl;
            }
            mySet.insert(last_index); // if we print it or not (in both cases) we should insert it to a set so that we will not check it again later.
            
        }else{
            if ( t1->getBirth() < d1){
                cout << *t1 << endl;
            }
            i++; // we can increase the index of temp employees even though we print it or not.
        }
        
        if ( i == tempEmps.getSize()) {
            doneWithTemps = 1;
        }
        if (mySet.size() == permEmps.getSize()){
            doneWithPerms = 1;
        }
    }
}

void printEmployeesInGivenMonth(int month, CircularArrayLinkedList& tempEmps, DoubleDynamicLinkedList& permEmps){
    
    // print all the employees born in a particular month in order by employee number
    // this function is the same as mergeAndPrintByEmployeeNum function which prints all employees
    // in the ascending order by employee number. Only difference is that we should check if that employee was born
    // in the given month.
    
    int i=0;
    bool doneWithTemps=!tempEmps.getSize(),doneWithPerms = !permEmps.getSize();
    set<int> mySet;
    
    while ( !doneWithTemps || !doneWithPerms ){
    
        TemporaryEmployee* t1 = new TemporaryEmployee();
        if ( !doneWithTemps ){
            // since temporary employees are ordered by emp_num. the first item will give the employee with the smallest emp_num
            t1 = tempEmps.getEmployee(i);
        }
        
        if (doneWithPerms){
            if ( t1->getBirth().getMonth() == month){
                cout << *t1 << endl;
            }
            i++;
            
            if (i == tempEmps.getSize() ){
                doneWithTemps = 1;
            }
            continue;
        }
        
        PermanentEmployee* minEmp = new PermanentEmployee(-1);
        
        // find the permanent employee with the smallest emp_num
        int last_index = 0;
        for (int j=0; j < permEmps.getSize(); j++){
            
            PermanentEmployee* p1 = permEmps.getEmployee(j);
        
            if ( (minEmp->getEmp_num() == -1 || p1->getEmp_num() < minEmp->getEmp_num()) && !mySet.count(j) ) {// if this employee's emp_num is less than the minimum emp_num then set it as min employee
                minEmp = p1;
                last_index = j;
            }
        }
        
        if(doneWithTemps){
            if ( minEmp->getBirth().getMonth() == month){
                cout << *minEmp << endl;
            }
            mySet.insert(last_index);
            if ( mySet.size() == permEmps.getSize() ){// that means we are now done with permanent Employees. So we'll only check temporary emps.
                doneWithPerms = 1;
            }
            continue;
        }
        
        //after finding the minimum element in permEmps we should compare it with a temporary emp with the least emp num in tempEmps list
        if (  minEmp->getEmp_num() < t1->getEmp_num() ){
            if ( minEmp->getBirth().getMonth() == month){
                cout << *minEmp << endl;
            }
            mySet.insert(last_index); // if we print it we should insert it to a set so that we will not print it again later.
            
        }else{
            if ( t1->getBirth().getMonth() == month){
                cout << *t1 << endl;
            }
            i++; // we can increase the index of temp employees since we print it.
        }
        
        if ( i == tempEmps.getSize() ){ // that means we are now done with temporary Employees. So we'll only check permanent emps.
            doneWithTemps = 1;
        }
        if ( mySet.size() == permEmps.getSize() ){// that means we are now done with permanent Employees. So we'll only check temporary emps.
            doneWithPerms = 1;
        }
    }
}

void printLastAssignedEmployeeWithCertainTitle(string title, CircularArrayLinkedList& tempEmps, DoubleDynamicLinkedList& permEmps){
    
    // this function will list the employees assigned to the institution in a given year from OLDEST to NEWEST
    // since it is from oldest to newest, we should first look for the employee with the smallest aptDate in a given
    
    Employee* lastAssigned = new Employee();
    
    // after this for loop, the employee with the greatest aptDate which is last assigned and also have the certain title will be assigned to
    // lastAssigned employee.
    for (int i = permEmps.getSize() - 1 ; i >= 0 ; i--){ // we're beginning from the end so we can break the loop whenever we find any emp.
        if (permEmps.getEmployee(i)->getTitle() == title){
            lastAssigned = permEmps.getEmployee(i);
            break; // since it is ordered, and we start from the end we can break the loop
        }
    }
    
    // now we'll check the other list which is tempEmps to see if we have any employee with the certain title and assigned most recently
    // than 'lastAssigned' employee.
    for (int i=0; i < tempEmps.getSize();i++){
        
        TemporaryEmployee* t1 = tempEmps.getEmployee(i);
        
        if(t1->getTitle() == title &&  lastAssigned->getAptDate() < t1->getAptDate()){
            lastAssigned = t1;
        }
    }
    // at the end, we can print the employee with the certain title and appointed most recently.
    cout << *lastAssigned << endl;
    
}


int main(){
    
    CircularArrayLinkedList tempEmps;
    DoubleDynamicLinkedList permEmps;
    
    string message = "--- Employee Recording System ---\n"
    "Please select for the following Menu Operation:\n"
    "1) Appointment of a new employee\n"
    "2) Appointment of a transferred employee\n"
    "3) Updating the title and the salary coefficient of an employee\n"
    "4) Deletion of an employee\n"
    "5) Listing the information of an employee\n"
    "6) Listing employees ordered by employee number\n"
    "7) Listing employees ordered by appointment date\n"
    "8) Listing employees appointed after a certain date\n"
    "9) Listing employees assigned in a given year\n"
    "10) Listing employees born before a certain date\n"
    "11) Listing employees born in a particular month\n"
    "12) Listing the information of the last assigned employee with a given title\n";
    cout << message;
    
    while(true){
        
        cout << "Please select a number from the menu: ";
        
        
        int n;
        cin >> n;
        
        if (n == -1)    break;
        
        bool emp_type, emp_found; // 0 for temp 1 for perm
        string name,surname,title,birth,aptDate;
        double salary_coef;
        int emp_number,len_of_srv;
        
        
        switch (n) {
            case 1: // appointment of a new employee who started working for the first time
            {
                cout << "Please type the employee number: ";
                cin >> emp_number;
                emp_found = false;
                
                for (int i=0; i < tempEmps.getSize(); i++){
                    if ( tempEmps.getEmployee(i)->getEmp_num() == emp_number ){
                        emp_found = true;
                        break;
                    }
                }
                for ( int i=0; i < permEmps.getSize(); i++){
                    if (permEmps.getEmployee(i)->getEmp_num() == emp_number ){
                        emp_found = true;
                        break;
                    }
                }
                
                if ( !emp_found ) { // which means we have a new employee
                    cout << "Type the employee type: ";
                    cin >> emp_type;
                    cout << "Type name: ";
                    cin >> name;
                    cout << "Type surname: ";
                    cin >> surname;
                    cout << "Type title: ";
                    cin >> title;
                    cout << "Type salary coefficient: ";
                    cin >> salary_coef;
                    cout << "Type birth date: ";
                    cin >> birth;
                    cout << "Type appointment date: ";
                    cin >> aptDate;
                    
                    if ( emp_type == 0) { // temp employee
                        TemporaryEmployee* myTempObj = new TemporaryEmployee(emp_number,emp_type,name,surname,title,salary_coef,Date(birth),Date(aptDate));
                        tempEmps.insert(myTempObj);
                    }
                    else{ // emp_type = 1 whic is a perm employee
                        PermanentEmployee* myPermObj = new PermanentEmployee(emp_number,emp_type,name,surname,title,salary_coef,Date(birth),Date(aptDate));
                        permEmps.insert(myPermObj);
                    }
                }
                cout << "\n";
                break;
            }
            case 2:
            {
                cout << "Please type the employee number: ";
                cin >> emp_number;
                emp_found = false;
                
                for (int i=0; i < tempEmps.getSize(); i++){
                    if ( tempEmps.getEmployee(i)->getEmp_num() == emp_number ){
                        emp_found = true;
                        break;
                    }
                }
                for ( int i=0; i < permEmps.getSize(); i++){
                    if (permEmps.getEmployee(i)->getEmp_num() == emp_number ){
                        emp_found = true;
                        break;
                    }
                }
                
                if ( !emp_found ) { // which means we have a new employee
                    cout << "Type the employee type: ";
                    cin >> emp_type;
                    cout << "Type name: ";
                    cin >> name;
                    cout << "Type surname: ";
                    cin >> surname;
                    cout << "Type title: ";
                    cin >> title;
                    cout << "Type salary coefficient: ";
                    cin >> salary_coef;
                    cout << "Type birth date: ";
                    cin >> birth;
                    cout << "Type appointment date: ";
                    cin >> aptDate;
                    cout << "Type length of service days: ";
                    cin >> len_of_srv;
                    
                    if ( emp_type == 0) { // temp employee
                       
                        TemporaryEmployee* myTempObj = new TemporaryEmployee(emp_number,emp_type,name,surname,title,salary_coef,Date(birth),Date(aptDate),len_of_srv);
                        tempEmps.insert(myTempObj);
                    }
                    else{ // emp_type = 1 whic is a perm employee
                        PermanentEmployee* myPermObj = new PermanentEmployee(emp_number,emp_type,name,surname,title,salary_coef,Date(birth),Date(aptDate),len_of_srv);
                        permEmps.insert(myPermObj);
                    }
                }
                cout << "\n";
                break;
            }
            case 3: //updating title and salary coefficient of an employee
            {
                
                cout << "Please type the employee number: ";
                cin >> emp_number;
                emp_found = false;
                
                for (int i=0; i < tempEmps.getSize(); i++){
                                    
                    if ( tempEmps.getEmployee(i)->getEmp_num() == emp_number ){
                        emp_found = true;
                        
                        // if there is an employee with this number, then we should first get
                        // the new title and salary coefficient from the user
                        cout << "Type title: ";
                        cin >> title;
                        cout << "Type salary coefficient: ";
                        cin >> salary_coef;
                    
                        
                        tempEmps.getEmployee(i)->setTitle(title);
                        tempEmps.getEmployee(i)->setSal_coef(salary_coef);
                        
                        break;
                    }
                }
                if (emp_found)  break; // if the employee is already found we don't need to check the list below
                
                for ( int i=0; i < permEmps.getSize(); i++){
                                    
                    if (permEmps.getEmployee(i)->getEmp_num() == emp_number ){
                        emp_found = true;
                        
                        // if there is an employee with this number, then we should first get
                        // the new title and salary coefficient from the user
                        cout << "Type title: ";
                        cin >> title;
                        cout << "Type salary coefficient: ";
                        cin >> salary_coef;
                        
                        permEmps.getEmployee(i)->setTitle(title);
                        permEmps.getEmployee(i)->setSal_coef(salary_coef);
                        
                        break;
                    }
                }
                cout << "\n";
                break;
            }
            case 4: // deletion of an existing employee
            {
                
                emp_found  = false;
                cout << "Please type the employee number: ";
                cin >> emp_number;
                
                for (int i=0; i < tempEmps.getSize(); i++){
                    if ( tempEmps.getEmployee(i)->getEmp_num() == emp_number ){
                        
                        tempEmps.remove(emp_number);
                        break;
                    }
                }
                if (emp_found)  break;
                
                for ( int i=0; i < permEmps.getSize(); i++){
                    if (permEmps.getEmployee(i)->getEmp_num() == emp_number ){
                        
                        permEmps.remove(emp_number);
                        break;
                    }
                }
                cout << "\n";
                break;
            }
            case 5: // printing the informations of an employee
            {
                emp_found = false;
                cout << "Please type the employee number: ";
                cin >> emp_number;
                
                for (int i=0; i < tempEmps.getSize(); i++){
                    if ( tempEmps.getEmployee(i)->getEmp_num() == emp_number ){
                        
                        TemporaryEmployee* t1 = tempEmps.getEmployee(i);
                        cout << *t1 << "\n";
                        emp_found = true;
                        break;
                    }
                }
                if (emp_found)  break;
                
                for ( int i=0; i < permEmps.getSize(); i++){
                    if (permEmps.getEmployee(i)->getEmp_num() == emp_number ){
                        
                        PermanentEmployee* p1 = permEmps.getEmployee(i);
                        cout << *p1 << "\n";
                        break;
                    }
                }
                cout << "\n";
                break;
            }
                
            case 6:{ // listing of all employees in the order of employee number
                onlyPrintbyEmployeeNumber(tempEmps, permEmps);
                cout << "\n";
                break;
            }
            case 7:{ // listing of all employees in the order of appointment date
                onlyPrintbyAppointmentDate(tempEmps, permEmps);
                cout << "\n";
                break;
            }
            case 8:{ // listing of all employees assigned to the institution after a certain date d1 ( from NEW to OLD )
                cout << "Please enter the date: ";
                string str;
                cin >> str;
                Date d1 = Date(str);
                
                printAfterAppointmentDate(d1, tempEmps, permEmps);
                cout << "\n";
                break;
            }
            case 9:{ // listing of all employees assigned to the institution in a given year
                cout << "Please enter the year: ";
                int year;
                cin >> year;
                
                printEmployeesInGivenYear(year, tempEmps, permEmps);
                cout << "\n";
                break;
            }
            case 10:{ // listing of all employees born before a certain date
                cout << "Please enter the date: ";
                string date;
                cin >> date;
                Date d1 = Date(date);
                
                printEmployeesBornBeforeCertainDateInEmpnumOrder(d1, tempEmps, permEmps);
                cout << "\n";
                break;
            }
            case 11:{//
                cout << "Please enter the month: ";
                int month;
                cin >> month;
                
                printEmployeesInGivenMonth(month, tempEmps, permEmps);
                cout << "\n";
                break;
            }
            case 12:{
                cout << "Please enter the title: ";
                string title;
                cin >> title;
                printLastAssignedEmployeeWithCertainTitle(title, tempEmps, permEmps);
                cout << "\n";
                break;

            }
            default:
                break;
        }
    }
}

