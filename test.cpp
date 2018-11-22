#include <iostream>

using namespace std;

int m[1000][1000] = {0};


int main (){
    for(int i = 0;i<1000;i++){
        for(int j=0;j<1000;j++){
            cout<<m[i][j];
        }
    }
}