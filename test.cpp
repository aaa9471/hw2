#include <iostream>

using namespace std;

int m[2][2] = {0};


int main (){
    int a =1,b,c;
    for(int i=0;i<2;i++){
        for(int j =0;j<2;j++){
            cin>>m[i][j];
        }
    }
    cout<<"L";
    b = m[2][0];
    cout<<b;
    return 0;
}