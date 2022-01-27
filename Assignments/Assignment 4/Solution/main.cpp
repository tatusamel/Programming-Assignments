#include "Trie.h"
#define MAX_SIZE 1000
using namespace std;


int main(int argc, char **argv){
    
    ifstream indata(argv[1]);
    ofstream outData(argv[2]);
        
    Trie* myTrie = new Trie(); // create the root of trie
    
    string str;
    while( getline(indata,str) ) {
        
        if (str[0] == 'i'){ // which means insert
            
            string key,value; // to store key annd value strings
            
            int i=7; // start with 7th index (remove 'insert(' part )
            while ( str[i] != ','){
                key += str[i];
                i++;
            }
            i++; // to pass ','
            while ( str[i] != ')'){
                value += str[i];
                i++;
            }
            
            myTrie->insert(key, value,outData);
            
        }
        else  if( str[0] == 's'){ // which means search
            
            string key;
            
            int i=7;
            while ( str[i] != ')'){
                key += str[i];
                i++;
            }
            
            myTrie->search(key,outData);
            
        }
        else if (str[0] == 'd'){ // which means delete
            
            string key;
            
            int i=7;
            while ( str[i] != ')'){
                key += str[i];
                i++;
            }
            
            myTrie->remove(myTrie, key,outData, 0);
        }
        else if ( str[0] == 'l') { // which means list
            
            vector<char> vt(MAX_SIZE);
            myTrie->list(myTrie, vt, 0,outData);
        }
    }
    
    delete myTrie;
    outData.close();

}

