
#include <bits/stdc++.h>
using namespace std;
#define rows 6
#define cols 7
#define ll	long long

const int numberOfPlayers = 2;
char matrix[rows][cols];


void createMatrix();
void printMatrix();
void ChangeCurrPlayer(int& currPlayer);
void printCurrPlayerMessage(int& currPlayer, char playersSymbols[]);
void getInput (int& currColumn,int& currRow);
bool addSymbolToMatrix(int currColumn,int currPlayer, char playersSymbols[]);
bool thereIsWinner(int currColumn,int currRow);
bool thereIsWinnerAtRow(int currColumn);
bool thereIsWinnerAtCol(int currColumn,int currRow);
bool thereIsWinnerAtRightDia(int currColumn,int currRow);
bool thereIsWinnerAtLeftDia(int currColumn,int currRow);
void winnerMessage(int currPlayer, char playersSymbols[]);
bool thereIsTie();
void tieMessage();

int main(){
    int currRow;
    int currColumn;
    int currPlayer = 0;
    char playersSymbols[numberOfPlayers] = {'O','X'};
    createMatrix();
    while(true){
        printMatrix();
        ChangeCurrPlayer(currPlayer);
        printCurrPlayerMessage(currPlayer,playersSymbols);
        getInput(currColumn,currRow);
        while (!addSymbolToMatrix(currColumn,currPlayer,playersSymbols)){
            printCurrPlayerMessage(currPlayer,playersSymbols);
            getInput(currColumn,currRow);
        }
        if(thereIsWinner(currColumn,currRow)){
            winnerMessage(currPlayer,playersSymbols);
            return 0;
        }
        if (thereIsTie()){
            tieMessage();
            return 0;
        }
    }
}

void createMatrix(){
    for (int i = 0; i < rows;i++){
        for (int j = 0; j < cols;j++){
            matrix[i][j] = ' ';
        }
    }
}

void printMatrix(){
    cout << " 1  2  3  4  5  6  7 " << endl ;
    for (int i = 0; i < rows;i++){
        for (int j = 0; j < cols;j++){
            cout << "|" <<  matrix[i][j] << "|";
        }
        cout << endl;
    }
}

void ChangeCurrPlayer(int& currPlayer){
    currPlayer++;
    currPlayer %= numberOfPlayers;
}

void printCurrPlayerMessage(int& currPlayer,char playersSymbols[]){
    cout << playersSymbols[currPlayer] << "'s Turn - pick a column (1-7) :";
}

void getInput(int& currColumn,int& currRow){
    cin >> currColumn;
    currColumn--;
    for (int i = rows-1;i >= 0;i--){
        if (matrix[i][currColumn] == ' '){
            currRow = i;
            break;
        }
    }
}

bool addSymbolToMatrix(int currColumn,int currPlayer, char playersSymbols[]){
    for (int i = rows-1; i >= 0;i--){
        if (currColumn >= 7 || currColumn < 0){
            return false;
        }
        if (matrix[i][currColumn] == ' '){
            matrix[i][currColumn] = playersSymbols[currPlayer];
            return true;
        }
    }
    return false;
}

bool thereIsWinner(int currColumn,int currRow){
    bool checkRightDia = thereIsWinnerAtRightDia(currColumn,currRow);
    bool checkRow =  thereIsWinnerAtRow(currColumn);
    bool checkCol =  thereIsWinnerAtCol(currColumn,currRow);
    bool checkleftDia = thereIsWinnerAtLeftDia(currColumn,currRow);
    return (checkRow || checkCol || checkRightDia || checkleftDia);
}

bool thereIsWinnerAtRow(int currColumn){
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
    return false;
}

bool thereIsWinnerAtCol(int currColumn,int currRow){
    int ans = 1;
    for (int i = cols - 1; i > 0; i--){
        if (matrix[currRow][i] != ' '){
            if (matrix[currRow][i] == matrix[currRow][i-1]){
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
    return false;
}

bool thereIsWinnerAtRightDia(int currColumn,int currRow){
    int ans = 1;
    for (;currColumn < cols - 1 && currRow > 0; currColumn++,currRow--);
    for (; currRow < rows - 1 && currColumn > 0;currColumn--,currRow++){ 
        if (matrix[currRow][currColumn] != ' '){
            if (matrix[currRow][currColumn] == matrix[currRow+1][currColumn-1]){
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
    return false;
}

bool thereIsWinnerAtLeftDia(int currColumn,int currRow){
    int ans = 1;
    if (currColumn >= currRow){
        currColumn -= currRow;
        currRow -= currRow;
    }
    else{
        currRow -= currColumn;
        currColumn -= currColumn;
    }
    for (;currRow < rows - 1 && currColumn < 7; currColumn++,currRow++){ 
        if (matrix[currRow][currColumn] != ' '){
            if (matrix[currRow][currColumn] == matrix[currRow+1][currColumn+1]){
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
    return false;
}

void winnerMessage(int currPlayer, char playersSymbols[]){
    cout << playersSymbols[currPlayer] << "' is Winner" << endl;
}

bool thereIsTie(){
    for (int i = 0; i < cols;i++){
        if (matrix[0][i] == ' '){
            return false;
        }
    }
    return true;
}

void tieMessage(){
    cout << "Tie" << endl;
}
  