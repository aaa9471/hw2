#include <iostream>

using namespace std;

int row,col;
int m[row][col];

int main (){
    cin>>row>>col;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            m[i][j] = i+j;
        }
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cout<<m[i][j]<<" ";
        }
        cout<<endl;
    }
}