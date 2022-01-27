#pragma once
#include "Employee.h"
using namespace std;

struct Node{
    TemporaryEmployee* emp;
    int next;
};

class CircularArrayLinkedList{
private:
    int head,free,size;
        
public:
    
    CircularArrayLinkedList();
    
    // we'll later define all those functions
    
    // function to insert a node to the end of the circular linked list
    void insert(TemporaryEmployee* emp);
    
    // function to delete a node with the fiven index i
    void remove(int empNum);
    
    int getSize();
    
    int getTop();
    
    TemporaryEmployee* getEmployee(int index);
    
    friend ostream& operator<<(ostream& stream, CircularArrayLinkedList& other);
    
};
