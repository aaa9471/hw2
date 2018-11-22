#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include<queue>

int row,col;
using namespace std;
int map [1000][1000] ={};
void BFS(int i,int j){
    queue<pair<int,int>> que;
    bool vis[row][col] = {0};
    que.push(make_pair(i,j));
    vis[i][j] = true;
    while(!que.empty()){
        int u = que.front(); que.pop();
        for()
    }

}

int main (int argc,char* argv[]){
    int  ans = 0,battery;
    int i_start,j_start;//the start position
    char road;
    ifstream fin;
    string str1 = "\\floor.data";
    string str2 = "\\final.path";
    string input = argv[1]+str1;
    string output = argv[1]+str2;
    //if file open fail
    fin.open(input, ios::in);
        if (!fin){
        cout<<"in error"<<endl;
        return 0;
    }
    //input map size bat
    fin>>row>>col>>battery;
    //build map
    // -1 wall 3000000 road 0 r
    for(int i = 0 ;i<row;i++){
        for(int j = 0;j<col;j++){
            fin>>road;
            if (road == '1') map[i][j] = -1;
            else if (road == '0')map[i][j] = 3000000;
            else if (road == 'R'){
                map[i][j] = 0;
                i_start = i;
                j_start = j;
            }
        }
    }
    BFS(i_start,j_start);


}