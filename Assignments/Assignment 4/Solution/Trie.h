
#pragma once
#define CHAR_SIZE 26
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Trie{
    
private:
    string englishWord;
    
public:
    
    Trie* children[CHAR_SIZE];
    
    Trie(){
        
        for(int i=0; i < CHAR_SIZE; i++){
            this->children[i] = nullptr;
        }
    };
    
    void insert(string&,string&,ofstream&);
    Trie* remove(Trie*,string&,ofstream&, int);
    void search(string&,ofstream&);
    int howManyChild();
    void list(Trie*,vector<char>&,int,ofstream&);
    
};


