
#include "CircularArrayLinkedList.h"
#define MAX_SIZE 20
using namespace std;

struct Node nodes[MAX_SIZE];

CircularArrayLinkedList::CircularArrayLinkedList(){
    head = -1;
    free = 0;
    size = 0;
    for (int i=0;i < MAX_SIZE-1 ; i++){
        nodes[i].next = i+1;
    }
    nodes[MAX_SIZE-1].next = 0; // since it is circular
}

void CircularArrayLinkedList::insert(TemporaryEmployee* emp){
    
    if (free == head){ // xxxx
        cout << "no enough space" << endl;
        return;
    }
    
    if (head == -1){
        head = 0;
        nodes[head].emp = emp;
        free = nodes[free].next;
        nodes[head].next = head;
        size++;
    }
    else {
        
        int oldFree = free;
        free = nodes[free].next;
        
        if ( emp->getEmp_num() < nodes[head].emp->getEmp_num() ){ // the case that it is less than first element
            nodes[oldFree].next = head;
            nodes[oldFree].emp = emp;
            
            int curr = head;
            while ( nodes[curr].next != head ){
                curr = nodes[curr].next;
            }
            nodes[curr].next = oldFree;
            head = oldFree;
            size++;
            return;
        }
        
        int curr = head;
        while ( nodes[curr].next != head && nodes[nodes[curr].next].emp->getEmp_num() <= emp->getEmp_num() ){
            curr = nodes[curr].next;
        }
        
        nodes[oldFree].emp = emp;
        nodes[oldFree].next = nodes[curr].next;
        nodes[curr].next = oldFree;
        size++;
    }
}
void CircularArrayLinkedList::remove(int empNum){
    
    empNum = (empNum + 20) % 20; // because it is circular, we have to take modulo of it.
    
    if (head == -1){
        cout << "list is empty" << endl;
        return;
    }
    
    if ( empNum == nodes[head].emp->getEmp_num() ) { // if we want to delete the head
        
        // we should go to the tail first
        int curr = head;
        while ( nodes[curr].next != head ){
            curr = nodes[curr].next;
        }
        // now curr is the last element in the list
        nodes[curr].next = nodes[head].next;
        
        // now we should update free
        nodes[head].next = free;
        free = head;
        
        if (this->getSize() == 1){
            head = -1;
        }else{
            // then update the head
            head = nodes[curr].next;
        }
        size--;
        return;
    }
    
    int curr = head;
    while ( nodes[curr].next != head && nodes[nodes[curr].next].emp->getEmp_num() != empNum){
        curr = nodes[curr].next;
    }
    
    // if we get back to the head which means that
    //there is no element in the list with the specified number
    if ( nodes[curr].next == head ){
        cout << "No element in the list with the specified employee number"  << endl;
    }
    
    // otherwise curr is the previous node index of the node that we want to remove
    
    
    int temp = nodes[nodes[curr].next].next; // temp is the next incoming element that after the element thatt we delete
    
    nodes[nodes[curr].next].next = free;
    free = nodes[curr].next;
    
    nodes[curr].next = temp;
    size--;
    
}


TemporaryEmployee* CircularArrayLinkedList::getEmployee(int index){
    

    int curr = head;
    int count = 0;
    
    if ( index >= this->getSize() ){
        cout << "index out of bound exception";
        exit(1);
    }
    
    while ( nodes[curr].next != head ){
        if ( count == index ){
            break;
        }
        curr = nodes[curr].next;
        count++;
    }
    return nodes[curr].emp;
}
int CircularArrayLinkedList::getSize(){
    return this->size;
}

int CircularArrayLinkedList::getTop(){
    return this->head;
}

ostream& operator<<(ostream& stream, CircularArrayLinkedList& other) {
    
    if (other.getSize() == 0){ // it can also be said other.getsize == 0
        cout << "no element" << endl;
        return stream;
    }
    
    int curr = other.getTop();
    while ( nodes[curr].next != other.getTop() ){
        stream << nodes[curr].emp << "-";
        curr = nodes[curr].next;
    }
    stream << nodes[curr].emp; // for the last number
    
    return stream;
}
