
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

int checkSides(vector<vector<int>>& vt, int t, int x, int y,int bSize, vector<pair<int,int>>& vt2){
    
    // this function is created to check how many number is connected to each other.
    
    // count the number of squares that has the same value as main square
    int count = 0;
    // a vector that keeps track of the positions of the checked squares so that we don't need to check
    // the same elements again and again and avoid a endless recursion
    vt2.push_back(pair<int,int> (x,y));
    count++; // for itself
    
    // this normally checks for all the squares along a square, I initially though we'll check all the squares but then I realized, it asks for only 4 square to check, so I didn't delete it, and put a
    // condition instead.
    for (int i=-1; i <= 1; i++ ){
        for (int j=-1; j <= 1 ; j++){
            
            // this will check if that square has already been checked
            bool checked_before = false;
            
            // if the square we're checking is not in the just above or just below position or
            // in the same row, then continue
            if ( ! ((i==-1&&j==0) || (i==1 && j==0) || (i == 0)) ) continue;
            // if the coordinates exceeds the bargains
            if (x+i < 0 || y+j < 0 || x+i >= bSize || y+j >= bSize) continue;

            
            //checking if this square is checked before
            for (auto itr = vt2.begin(); itr != vt2.end(); ++itr ){
                if ( (*itr).first == (x+i) && (*itr).second == (y+j) ){
                    checked_before = true; // if the square is checked before, set it true
                    break;
                }
            }
            
            // if the squre is not checked before and the square we're checking has
            // the same value as the main square
            if (!checked_before && vt[x+i][y+j] == t){
                // do the same steps for that square as well
                count += checkSides(vt, t, x+i, y+j,bSize,vt2);
            }
        }
    }
    return count;
}
void changeNumbers(vector<vector<int>>& vt, int t, int x,int y, int bSize){
    
    // this function is created to change the numbers that are connected to each other
    // with the same value
    
    for (int i=-1; i <= 1; i++ ){
        for (int j=-1; j <= 1 ; j++){
            
            // if it exceeds the bargains then continue
            if (x+i < 0 || y+j < 0 || x+i >= bSize || y+j >= bSize) continue;
            
            // if the square we're checking is not in the just above or just below position or
            // in the same row, then continue
            if ( ! ((i==-1&&j==0) || (i==1 && j==0) || (i == 0)) ) continue;
            
            // if the square has the same value as the main square and it's not the square itself
            if ( vt[x+i][y+j] == t && !(i == 0 && j == 0) ){
                vt[x+i][y+j] = 0; // set it as 0
                changeNumbers(vt, t, x+i, y+j,bSize); // do the same steps for that square as well
            }
        }
    }
}
int bomb(vector<vector<int>>& vt, int x, int y, int bSize){
    
    // this function is created for part2 to change the values to 0 when required.
    
    // count is created to count the points that a balloon has when it is bombed
    // myValue keeps track of the value that is inside main balloon
    int count = 0, myValue = vt[x][y];
    
    for (int i = 0 ; i < bSize; i++){
        for (int j= 0 ; j < bSize ; j++){
            // if the squares are in the same row or same column or in the same diagonal and
            // has the same value with the same square (balloon)
            if ( ( (i==x) || (j==y) || (abs(x-i) == abs(y-j)) ) && vt[i][j] == myValue ){
                vt[i][j] = 0; // change it to 0
                count+=myValue;
            }
        }
    }
    return count;
}
void printBoard(vector<vector<int>>& vt, int bSize, ofstream& outData){
    // to print the board
    for(int i=0; i < bSize; i++){
       for(int j=0; j<bSize; j++){
           outData << vt[i][j] << " ";
       }
       outData << "\n";
   }
}

int main(int argc, char** argv) {
    
    ifstream file_1(argv[1]); //
    ofstream outData;
    
    outData.open(argv[3]);

    // creating the board
    int bSize;
    file_1 >> bSize;
    vector<vector<int>> vt( bSize , vector<int> (bSize,0));
    
    // getting the numbers from console
    string line;
    int x,y,t;
    
    while (getline(file_1, line) && !line.empty()){
        istringstream iss(line);
        vector<pair<int,int>> vt2; // to store the index pairs that is checked before
        
        if(iss >> t >> x >> y){
            
            vt[x][y] = t;
            while(checkSides(vt, t, x, y, bSize, vt2) >= 3){
                changeNumbers(vt, t, x, y, bSize);
                vt[x][y] = t+1;
                vt2.clear();
                t++;
            }
        }
    }
    outData << "PART 1:" << endl;
    printBoard(vt,bSize, outData);
    outData << endl;
    
    ifstream file_2(argv[2]);
    file_2 >> bSize;
    vector<vector<int>> vt3(bSize, vector<int> (bSize) );
        
    int i = 0, sum = 0,a;
    getline(file_2, line); // to remove /r
    while (getline(file_2, line) && !line.empty()){
        istringstream iss(line);
        for (int j=0; j<bSize && i < bSize; j++){
            iss >> a;
            vt3[i][j] = a;
        }
        
        if(iss >> x >> y && i >= bSize){
            sum += bomb(vt3, x, y, bSize);
        }
        
        i++;
    }
    outData << "PART 2:" << endl;
    printBoard(vt3,bSize, outData);
    outData << "Final Point: " << sum << "p" << endl;
    
    outData.close();
    
    return 0;
}
