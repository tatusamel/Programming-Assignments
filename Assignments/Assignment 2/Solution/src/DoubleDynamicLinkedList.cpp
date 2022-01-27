#include "DoubleDynamicLinkedList.h"

DoubleDynamicLinkedList::DoubleDynamicLinkedList(){
    size = 0;
    head = NULL;
}

void DoubleDynamicLinkedList::insert(PermanentEmployee* emp){
    
    DoublyNode* newNode = new DoublyNode();
    newNode->emp = emp;
    
    if ( head == NULL ) {
        head = newNode;
        head->next= NULL;
        head->prev = NULL;
        size++;
    }else{
        
        if ( head->emp->getAptDate() > emp->getAptDate()){
            newNode->next = head;
            head->prev = newNode;
            newNode->prev = NULL;
            head = newNode;
            size++;
            return;
        }
        
        DoublyNode* curr = head;
        while( curr->next != NULL && curr->next->emp->getAptDate() <= emp->getAptDate()){
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
        newNode->prev = curr;
        
        if (newNode->next != NULL){
            newNode->next->prev = newNode;
        }
        size++;
    }
}
void DoubleDynamicLinkedList::remove(int emp_num){
    
    DoublyNode* temp;
    DoublyNode* curr = head;
    
    if ( head == NULL) { // or this->getSize() == 0
        cout << "no employee to be deleted with the specific appointment date" << endl;
    }
    
    if ( head->emp->getEmp_num() == emp_num ){ // if head should be deleted
        temp = head;
        head = head->next;
        head->prev = NULL;
        free(temp);
        size--;
    }else{
        
        while ( curr->next != NULL && !(curr->next->emp->getEmp_num() == emp_num ) ){
            curr = curr->next;
        }
        
        if ( curr->next == NULL){
            cout << "No such value" << endl;
            return;
        }
        temp = curr->next;
        curr->next = temp->next;
        if( temp->next != NULL){
            temp->next->prev = curr;
        }
        free(temp);
        size--;
    }
}

PermanentEmployee* DoubleDynamicLinkedList::getEmployee(int index){
    
    DoublyNode* curr = head;
    int count = 0;
    
    if (index >= this->getSize()){
        cout << "index out of bound exception";
        exit(1);
    }
    
    while(curr->next != NULL){
        if ( count == index ){
            break;
        }
        curr = curr->next;
        count++;
    }
    return curr->emp;
    
}

DoublyNode* DoubleDynamicLinkedList::getTopNode(){
    return this->head;
}

int DoubleDynamicLinkedList::getSize() const{
    return this->size;
}

ostream& operator<<(ostream& stream, DoubleDynamicLinkedList& other){
    
    DoublyNode* curr = other.getTopNode();
    
    while ( curr->next != other.getTopNode() ){
        stream << curr->emp << "-";
        curr = curr->next;
    }
    stream << curr->emp << endl;
    
    return stream;
}
