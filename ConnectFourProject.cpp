#include <bits/stdc++.h>
using namespace std;

#define ll	long long

int main(){
    char matrix[6][7];
    for (int i = 0; i < 6;i++){
        for (int j = 0; j < 7;j++){
            matrix[i][j] = ' ';
        }
    }
    for (int i = 0; i < 6;i++){
        for (int j = 0; j < 7;j++){
            cout << "|" <<  matrix[i][j] << "|";
        }
        cout << endl;
    }
}
