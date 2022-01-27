#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;

#define MAX_RULE 100 // maximum number of rules
#define MAX_STATES 50 // maximum number of states

bool isSymbolUsed;
ofstream outData;

// this is a structure to store the rules
struct rule{
    string startingState, resultingState;
    char inputSymbol,symbolPopped, symbolPushed;
    
    rule(){}
    
    rule(string startingState, char inputSymbol, char symbolPopped, string resultingState, char symbolPushed){
        this->startingState = startingState;
        this->resultingState = resultingState;
        this->inputSymbol = inputSymbol;
        this->symbolPopped = symbolPopped;
        this->symbolPushed = symbolPushed;
    }
    
};
// overloaded << to print a rule
ostream& operator<<(ostream& stream, rule& other){
    stream << other.startingState << "," << other.inputSymbol << "," << other.symbolPopped << " => " << other.resultingState << ","
    << other.symbolPushed;
    
    return stream;
}

// to print the stack in reverse order, from bottom to top
void printStack(stack<char> myStack){
    
    if (myStack.empty()){
        return;
    }
    
    char ch = myStack.top();
    myStack.pop();
    
    printStack(myStack);
    
    if (myStack.size() == 0){
        outData << ch;
    }else{
        outData << ',' << ch;
    }
    
    myStack.push(ch);
        
}

string doOperation(stack<char>& myStack, string stState, vector<rule>& rules, char mySymbol){
    
    bool flag = false;
    string resultingState;
    rule* stocked;// this is for the state that takes input 'e'
    
    bool found = false;
    for( int i =0; i < rules.size(); i++){
        if ( rules[i].startingState == stState ){
            found  = true;
        }
    }
    if (!found){
        isSymbolUsed = true;
        return stState;
    }
    
     for( int i=0; i < rules.size(); i++){
        
        // we found the rule
        if ( rules[i].startingState == stState && rules[i].inputSymbol == mySymbol){
            flag = true; // to check if we found any rule that fits
            resultingState = rules[i].resultingState;

            // pop step
            if ( rules[i].symbolPopped == 'e' ) {
                // then no symbol is popped
            }
            else if ( rules[i].symbolPopped == myStack.top()){
                myStack.pop();
            }
            else { // the symbol which will be popped is not found try the other cases too
                flag = false;
                continue;
            }
            
            // push step
            if ( rules[i].symbolPushed == 'e'){
                // do nothing
            }
            else{
                myStack.push(rules[i].symbolPushed);
            }
            
            outData << rules[i] << " [STACK]:";
            printStack(myStack);
            outData << "\n";
            return resultingState;
        }
        
        if ( rules[i].startingState == stState && rules[i].inputSymbol == 'e'){
            stocked = &rules[i];
        }
    }
    // at the end if we couldn't find any rule that fits best we'll take the rule that takes
    // input 'e' and starts with the Starting State
    if ( stocked != nullptr){
        isSymbolUsed = false;
        return doOperation(myStack, stState, rules, 'e');
    }
    return resultingState;
}

int main(int argc, char** argv) {
    
    ifstream stream1(argv[1]);
    outData.open(argv[3]);
    
    vector<string> states; // to store the states
    string startState; // to store start state
    vector<string> finalStates; // to resulting states
    
    vector<char> alphabetsFromInput; // to store the characters that may be coming from input
    vector<char> alphabetsInStack; // to store the characters that may go in to the stack
    vector<rule> rules; // to store the rules
        
    
    // this is the part of input taking
    string line;
    while( getline(stream1, line) && !line.empty() ){
        
        if(line[0] == 'Q'){
            
            int i=2; // since first the character is a letter and : symbol, they're passed
            while ( i < line.length()){
                
                if ( line[i] == 'q' || line[i] == 's'){
                    string myString;
                    while ( line[i] != ',' && line[i] != ' '){
                        myString += line[i];
                        i++;
                    }
                    states.push_back( myString );
                    i++;
                    continue;
                }
                else if ( line[i] == ' '){
                    i ++;
                }
                else if ( line[i] == '='){
                    i += 3;
                }
                else if ( line[i] == '('){
                    i++; // to pass '('
                    while ( line[i] != ')'){
                        startState += line[i];
                        i++;
                    }
                    i += 2; // to pass both ')' and ','
                }
                else if ( line[i] == '['){
                    i++;
                    string finalState;
                    while (line[i] != ']'){
                        finalState += line[i];
                        i++;
                    }
                    finalStates.push_back(finalState);
                    i += 2; // to pass both ']' and ','
                }
            }
        }
        else if(line[0] == 'A'){
            
            int i = 2;
            while ( i < line.length()){
                
                if ( line[i] != ',')
                    alphabetsFromInput.push_back(line[i]);
                i++;
            }
            alphabetsFromInput.push_back('e'); // 'e' should be added to the alphabet
        }
        else if(line[0] == 'Z'){
            int i = 2;
            while ( i < line.length()){
                
                if ( line[i] != ',')
                    alphabetsInStack.push_back(line[i]);
                i++;
            }
            alphabetsInStack.push_back('e'); // 'e' should be added to the alphabet
        }
        else if(line[0] == 'T'){
            
            // since there'll always be 5 chars, we can make it without using while loop
            int i=2;
            string startState;
            while (line[i] != ','){
                startState += line[i];
                i++;
            }
            i++; // to pass ','
            char inputSymbol = line[i];
            i+=2; // to pass ','
            char symbolPopped = line[i];
            i+=2;
            
            string resultState;
            while (line[i] != ',') {
                resultState += line[i];
                i++;
            }
            i++;
            char symbolPushed = line[i];
            
            // checking part
            bool isValid1=false, isValid2=false, isValid3=false, isValid4 = false,isValid5 = false;
            for ( string s: states){
                if ( s == startState ){
                    isValid1 = true;
                }
            }
            // check if there is an error for the input symbol
            for (char c: alphabetsFromInput){
                if ( c == inputSymbol ){
                    isValid2 = true;
                }
            }
            // check if there is an error for the symbol which will be popped
            for( char c: alphabetsInStack){
                if ( c == symbolPopped ){
                    isValid3 = true;
                }
            }
            for( string s: states){
                if ( s == resultState ){
                    isValid4 = true;
                }
            }
            for ( char c: alphabetsInStack){
                if ( c == symbolPushed ){
                    isValid5 = true;
                }
            }
            if (!(isValid1 && isValid2 && isValid3 && isValid4 && isValid5)){
                outData << "Error [1]:DPDA description is invalid!\n";
                exit(1);
            }
            
            rule myRule = rule(startState, inputSymbol, symbolPopped, resultState, symbolPushed);
            rules.push_back(myRule);
        }
    }
    
    ifstream stream2(argv[2]);
    
    while ( getline(stream2, line) ){
        
        stack<char> myStack;
        
        // if the line is empty or it has '\r' which means it is empty again.
        // see if the start state is also the final state. If it is, print ACCEPT, otherwise print REJECT
        if ( line.empty() || line == "\r"){
            bool flag = false;
            for ( int i=0; i<finalStates.size(); i++){
                if ( startState == finalStates[i] ){
                    flag = true;
                }
            }
            if (flag)   outData << "ACCEPT" << "\n\n";
            else   outData << "REJECT" << "\n\n";
            continue;
        }
        // if the line doesn't have '\r' at the end, add '\r'
        if (line[line.length()-1] != '\r'){
            line += '\r';
        }
        
        bool first_done = 0; // to check if the first operation is done
        
        string currState;
        int i =0;
        while ( i < line.length() ){
            
            // to check if the symbol is used
            isSymbolUsed = true;
            
            if ( line[i] == ','){
                i++;
                continue;
            }
            
            char mySymbol = line[i]; // the symbol is taken
            
            // this is just for starting state
            if ( !first_done ){
                // find the first state amongst the rules
                for( int j=0; j < rules.size(); j++){
                    
                    if (rules[j].startingState == startState){
                        first_done = true;
                        
                        if ( rules[j].inputSymbol == 'e' || rules[j].inputSymbol == mySymbol){
                            
                            // if the first symbol is equal to the input symbol
                            if (mySymbol == rules[j].inputSymbol){
                                i++;
                            }
                            // if it is not equal to the input symbol, then don't go forward because we'll use the input
                            // for the later rules
                            
                            // popping step
                            if ( rules[j].symbolPopped == 'e' ){
                                // do nothing
                            }
                            else if ( rules[j].symbolPopped == myStack.top() ){
                                myStack.pop();
                            }
                            
                            //pushing step
                            if ( rules[j].symbolPushed == 'e' ){
                                // do nothing
                            }
                            else{
                                myStack.push(rules[j].symbolPushed);
                            }
                            
                            outData << rules[j] << " [STACK]:";
                            printStack(myStack);
                            outData << "\n";
                            currState = rules[j].resultingState;
                        }
                        break;
                    }
                }
                continue;
            }
            currState = doOperation(myStack, currState, rules, mySymbol);
            if (isSymbolUsed){
                i++;
            }else{
                // check if this input character is the last element of the inputs
                if ( i == line.length() - 1){
                    break;
                }
            }
        }
        bool flag = false;
        for (int i=0; i < finalStates.size(); i++){
            if ( finalStates[i] == currState && (myStack.size() == 0 || myStack.top() == '$')){
                flag = true;
                outData << "ACCEPT" << "\n\n" ;
                break;
            }
        }
        if ( flag == false ){
            outData << "REJECT" << "\n\n";
        }
    }
}
