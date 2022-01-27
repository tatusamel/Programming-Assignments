#pragma once
#include "Employee.h"

struct DoublyNode{
    PermanentEmployee* emp;
    DoublyNode* next;
    DoublyNode* prev;
    
    DoublyNode(){
        this->next = NULL;
        this->prev = NULL;
    }
    DoublyNode(PermanentEmployee* emp){
        this->emp = emp;
        this->next = NULL;
        this->prev = NULL;
    }
};

class DoubleDynamicLinkedList
{
    
private:
    int size;
    DoublyNode* head;

public:
    DoubleDynamicLinkedList();
    void insert(PermanentEmployee* emp);
    void remove(int emp_num);
    int getSize() const;
    PermanentEmployee* getEmployee(int index);
    DoublyNode* getTopNode();
    
    friend ostream& operator<<(ostream& stream, DoubleDynamicLinkedList& other); // don't forget to put friend

};

