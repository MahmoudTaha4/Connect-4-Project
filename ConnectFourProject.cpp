
#include <bits/stdc++.h>
using namespace std;
#define rows 6
#define cols 7
#define ll	long long

const int numberOfPlayers = 2;
char matrix[rows][cols];


void createMatrix();
void printnigMatrix();
void ChangeCurrPlayer(int& currPlayer);
void printCurrPlayerMessage(int& currPlayer, char playersSymbols[]);
void getInput (int& currColumn,int& currRow,int& currRow2);
bool addSymbolToMatrix(int currColumn,int currPlayer, char playersSymbols[]);
bool thereIsWinner(int currPlayer, char playersSymbols[],int currColumn,int currRow,int currRow2);
bool therIsWinnerAtRow(int currPlayer, char playersSymbols[],int currColumn);
bool therIsWinnerAtCol(int currPlayer, char playersSymbols[],int currColumn,int currRow);
bool therIsWinnerAtRightDia(int currPlayer, char playersSymbols[],int currColumn,int currRow2);
bool therIsWinnerAtLeftDia(int currPlayer, char playersSymbols[],int currColumn,int currRow);
void winnerMessage(int currPlayer, char playersSymbols[]);
bool noneWinner();
void tieMessage();

int main(){
    int currRow2;
    int currRow;
    int currColumn;
    int currPlayer = 0;
    char playersSymbols[numberOfPlayers] = {'O','X'};
    createMatrix();
    while(true){
        printnigMatrix();
        ChangeCurrPlayer(currPlayer);
        printCurrPlayerMessage(currPlayer,playersSymbols);
        getInput(currColumn,currRow,currRow2);
        while (!addSymbolToMatrix(currColumn,currPlayer,playersSymbols)){
            printCurrPlayerMessage(currPlayer,playersSymbols);
            getInput(currColumn,currRow,currRow2);
        }
        if(thereIsWinner(currPlayer,playersSymbols,currColumn,currRow,currRow2)){
            winnerMessage(currPlayer,playersSymbols);
            return 0;
        }
        if (noneWinner()){
            tieMessage();
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

void printnigMatrix(){
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

void getInput(int& currColumn,int& currRow,int& currRow2){
    cin >> currColumn;
    currColumn--;
    for (int i = 0;i < rows;i++){
        if (matrix[i][currColumn] == ' '){
            currRow = i;
            break;
        }
    }
    for (int i = rows-1;i >= 0;i--){
        if (matrix[i][currColumn] == ' '){
            currRow2 = i;
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

bool thereIsWinner(int currPlayer, char playersSymbols[],int currColumn,int currRow,int currRow2){
    bool checkRightDia = therIsWinnerAtRightDia(currPlayer,playersSymbols,currColumn,currRow2);
    bool checkRow =  therIsWinnerAtRow(currPlayer,playersSymbols,currColumn);
    bool checkCol =  therIsWinnerAtCol(currPlayer,playersSymbols,currColumn,currRow);
    bool checkleftDia = therIsWinnerAtLeftDia(currPlayer,playersSymbols,currColumn,currRow);
    return (checkRow || checkCol || checkRightDia || checkleftDia);
}

bool therIsWinnerAtRow(int currPlayer, char playersSymbols[],int currColumn){
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

bool therIsWinnerAtCol(int currPlayer, char playersSymbols[],int currColumn,int currRow){
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

bool therIsWinnerAtRightDia(int currPlayer, char playersSymbols[],int currColumn,int currRow2){
    int ans = 1;
    for (int i = currRow2; i < rows-1; i++){ 
        if (matrix[i][currColumn] != ' '){
            if (matrix[i][currColumn] == matrix[i+1][currColumn-1]){
                ans++;
                if (ans >= 4){
                    return true;
                }
            }
            else {
                ans = 1;
            }
        }
        if (currColumn != 0){
            currColumn--;
        }
    }
    return false;
}

bool therIsWinnerAtLeftDia(int currPlayer, char playersSymbols[],int currColumn,int currRow){
    int ans = 1;
    if (currColumn >= currRow){
        currColumn -= currRow;
        currRow -= currRow;
    }
    else{
        currRow -= currColumn;
        currColumn -= currColumn;
    }
    for (int i = currRow; i < rows-1; i++){ 
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
        if (currColumn != 6){
            currColumn++;
        }
    }
    return false;
}

void winnerMessage(int currPlayer, char playersSymbols[]){
    cout << playersSymbols[currPlayer] << "' is Winner" << endl;
}

bool noneWinner(){
    ll sum = 0;
    for (int i = 0; i < rows;i++){
        for (int j = 0; j < cols;j++){
            if (matrix[i][j] != ' '){
                sum++;
            }
            else {
                return false;
            } 
        }
    }
    if (sum == 42){
        return true;
    }
    return false;
}

void tieMessage(){
    cout << "Tie";
}
  