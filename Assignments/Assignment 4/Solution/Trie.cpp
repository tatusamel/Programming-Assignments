#include "Trie.h"

void Trie::insert(string& key,string& value, ofstream& outData)
{
    // start from the root node
    Trie* curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        
        // this will give the index of every character of string 'key'
        // index is determined by the ASCII table, but index starts from 0 as
        // the 0th element represents 'a' and 25th element represents 'z' in english alphabet
        int x = key[i] - 'a';
        
        // create a new node if the path doesn't exist
        if (curr->children[x] == nullptr) {
            curr->children[x] = new Trie();
        }
 
        // go to the next node
        curr = curr->children[x];
    }
    // if there is no corresponding english word, just add it
    if (curr->englishWord == ""){
        curr->englishWord = value;
        outData << '"' << key << '"' << " was added\n";
    }else if(curr->englishWord == value){
        outData << '"' << key << '"' <<  " already exist\n";
    }else{
        curr->englishWord = value;
        outData << '"' << key << '"' <<  " was updated\n";
        
    }
  
}

void Trie::search(string& key, ofstream& outData){
    
    Trie* curr = this;
    
    // this won't happen according to the assignment
    if ( curr == nullptr){
        return;
    }
    
    for (int i=0; i < key.length() ; i++){
        
        int x = key[i] - 'a';
        curr =  curr->children[x];
        
        // if the character is not in the specific level, then return false
        if (curr == nullptr){
            
            if ( i == 0 ){
                outData << '"' << "no record" << '"' << '\n';
            }else{
                outData << '"' << "incorrect Dothraki word" << '"' << '\n';
            }
            return;
        }
    }
    // at the end check if the last character is a leaf
    if ( curr->englishWord == ""){
        outData << '"' << "not enough Dothraki word" << '"' << '\n';
    }else{
        outData << '"' << "The English equivalent is "  << curr->englishWord << '"' << '\n';
    }
}

int Trie::howManyChild(){
    // to find if a trie has any child or not
    
    int count = 0;
    for (int i=0; i < CHAR_SIZE; i++){
        if ( this->children[i] ){
            count++;
        }
    }
    return count;
    
}
bool shouldBeDeleted = 1;
Trie* Trie::remove(Trie* root ,string& key, ofstream& outData,int depth = 0){
    // to remove a specific word from trie using recursion
        
    // this won't happen according to the assignment
    if ( root == nullptr ){
        return NULL;
    }
    
    // if it is the last character of the key
    if ( depth == key.size()){
        // we don't do key.size()-1 because we should also count the
        // root which does not represent any char
        
        if ( root->englishWord == "" ){
            outData << '"' << "not enough Dothraki word" << '"' << '\n';
        }else{
            // set the english word of the node empty string, so it will not be counted as the end of the word
            root->englishWord = "";
            outData << '"' << key << '"' << " deletion is successful\n";
        }
        
        // if it is not prefix of any other word, the trie can be deleted
        if ( !root->howManyChild() ){
            delete (root);
            root = NULL;
        }
        return root;
    }
    
    int index = key[depth] - 'a';
    // first check if the letter exists in specific level
    if ( root->children[index] == nullptr){
        
        if (depth == 0){
            outData << '"' << "no record" << '"' << '\n';
        }else{
            outData << '"' << "incorrect Dothraki word" << '"' << '\n';
        }
        return root;
    }
    // if the letter exists, go 1 step deeper recursively
    root->children[index] = remove(root->children[index], key,outData, depth+1);
    
    // if root does not have any child and it is not another word's
    // leaf, delete it
    if ( !root->howManyChild() && root->englishWord == ""){
        delete (root);
        root = NULL;
    }
    
    return root;
    
}

void Trie::list(Trie* root, vector<char>& key, int depth, ofstream& outData){
    
    // to print the trie recursively
    
    if ( root == nullptr ){
        return;
    }
    
    // if it is the end of the word
    if ( root->englishWord != "" ){
        // add '\0' so that it will ignore all the characters after this when printing out
        key[depth] = '\0';
        
        
        // this will check if dash is put or not since it will be put only 1 times
        bool dashIsPut = 0;
        // print the word
        for (int i=0; i < key.size(); i++ ){
            if (key[i] == '\0') break;
            
            if ( key[i] == '\t' ){
                outData << '\t';
            }else{
                if (!dashIsPut){
                    outData << '-' << key[i];
                    dashIsPut = 1;
                }
                else{
                    outData << key[i];
                }
            }
            
            
        }
        outData << '(' << root->englishWord << ')' << '\n';
    }
    
    // if it is not the top root and if it has more than 1 children
    if ( root != this && root->howManyChild() > 1 ){
        
        // check if it is printed before because it is the end of a word
        if ( root->englishWord == "" ) {
            
            bool isDashPut = 0;
            // print the word
            for ( int i = 0; i < depth; i++ ){
                
                if ( key[i] == '\t' ){
                    outData << '\t';
                }else{
                    if (!isDashPut){
                        outData << '-' << key[i];
                        isDashPut = 1;
                    }else{
                        outData << key[i];
                    }
                }
                
            }
            outData << '\n';
            
        }
        auto it = key.begin();
        key.insert(it, '\t');
        depth++;
    }
    
    // traverse through the trie and see if the trie has any child,
    // and for every child do the same step recursively
    for (int i=0; i < CHAR_SIZE; i++){
        
        // if it contains the specific letter
        if ( root->children[i] ){
            
            key[depth] = i + 'a';
            list(root->children[i], key, depth+1, outData);
        }
    }
}
