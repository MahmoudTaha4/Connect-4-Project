
#include <bits/stdc++.h>
using namespace std;
#define rows 6
#define cols 7
#define ll	long long

const int numberOfPlayers = 2;
char matrix[rows][cols];


void createMatrix();
void printnigMatrix();
void ChangeCurrPlay(int& currPlayer);
void printCurrPlayerMessage(int& currPlayer, char playersSymbols[]);
void getInput (int& currColumn,int& startPlace);
bool addSymbolToMatrix(int currColumn,int currPlayer, char playersSymbols[]);
bool thereIsWinner(int currPlayer, char playersSymbols[],int currColumn,int startPlace);
void winnerMessage(int currPlayer, char playersSymbols[]);

int main(){
    int startPlace;
    int currColumn;
    int currPlayer = 0;
    char playersSymbols[numberOfPlayers] = {'O','X'};
    createMatrix();
    while(true){
        printnigMatrix();
        ChangeCurrPlay(currPlayer);
        printCurrPlayerMessage(currPlayer,playersSymbols);
        getInput(currColumn,startPlace);
        while (!addSymbolToMatrix(currColumn,currPlayer,playersSymbols)){
            printCurrPlayerMessage(currPlayer,playersSymbols);
            getInput(currColumn,startPlace);
        }
        if(thereIsWinner(currPlayer,playersSymbols,currColumn,startPlace)){
            winnerMessage(currPlayer,playersSymbols);
            return 0;
        }
    }
    cout << "Tie";
}

void createMatrix(){
    for (int i = 0; i < rows;i++){
        for (int j = 0; j < cols;j++){
            matrix[i][j] = ' ';
        }
    }
}

void printnigMatrix(){
    for (int i = 0; i < rows;i++){
        for (int j = 0; j < cols;j++){
            cout << "|" <<  matrix[i][j] << "|";
        }
        cout << endl;
    }
}

void ChangeCurrPlay(int& currPlayer){
    currPlayer++;
    currPlayer %= numberOfPlayers;
}

void printCurrPlayerMessage(int& currPlayer,char playersSymbols[]){
    cout << endl << playersSymbols[currPlayer] << "'s Turn - pick a column (1-7) :";
}

void getInput(int& currColumn,int& startPlace){
    cin >> currColumn;
    currColumn--;
    for (int i = 0;i < rows;i++){
        if (matrix[i][currColumn] == ' '){
            startPlace = i;
        }
    }
}

bool addSymbolToMatrix(int currColumn,int currPlayer, char playersSymbols[]){
    for (int i = rows-1; i >= 0;i--){
        if (currColumn >= 7 || currColumn <= 0){
            return false;
        }
        if (matrix[i][currColumn] == ' '){
            matrix[i][currColumn] = playersSymbols[currPlayer];
            return true;
        }
    }
    return false;
}

bool thereIsWinner(int currPlayer, char playersSymbols[],int currColumn,int startPlace){
    int ans = 1;
    for (int i = rows - 1; i > 0; i--){
        if (matrix[i][currColumn] != ' '){
            if (matrix[i][currColumn] == matrix[i - 1][currColumn]){
                ans++;
                if (ans >= 4){
                    return true;
                }
            }
            else {
                ans = 1;
            }
        }
    }
    ans = 1;
    for (int i = rows - 1; i > 0; i--){
        if (matrix[startPlace][i] != ' '){
            if (matrix[startPlace][i] == matrix[startPlace][i-1]){
                ans++;
                if (ans >= 4){
                    return true;
                }
            }
            else {
                ans = 1;
            }
        }
    }
    ans = 1;
    if (currColumn >= startPlace){
        currColumn -= startPlace;
        startPlace -= startPlace;
    }
    else{
        startPlace -= currColumn;
        currColumn -= currColumn;
    }
    for (int i = startPlace; i < rows-1; i++){ 
        if (matrix[i][currColumn] != ' '){
            if (matrix[i][currColumn] == matrix[i+1][currColumn+1]){
                ans++;
                if (ans >= 4){
                    return true;
                }
            }
            else {
                ans = 1;
            }
        }
        currColumn++;
    }
    for (int i = rows-1; i >= startPlace; i--){ 
        if (matrix[i][currColumn] != ' '){
            if (matrix[i][currColumn] == matrix[i-1][currColumn+1]){
                ans++;
                if (ans >= 4){
                    return true;
                }
            }
            else {
                ans = 1;
            }
        }
        currColumn++;
    }
    return false;
}

void winnerMessage(int currPlayer, char playersSymbols[]){
    cout << playersSymbols[currPlayer] << "' is Winner";
}
  