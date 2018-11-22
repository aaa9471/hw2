#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include<queue>

int row,col;
using namespace std;
int map [1000][1000] ={};

class Node
{
    public:
    Node(int x,int y,int z){i=x,j=y,lenth = z;};
    ~Node(){;};
    int geti(){return i;};
    int getj(){return j;};
    int getl(){return lenth;};

    private:
    int i,j,lenth;
};

void BFS(int i,int j){
    queue<Node> que;
    que.push(Node(i,j,0));
    while(!que.empty()){
        Node u = que.front(); que.pop();
        int a = u.geti(),b = u.getj(),l = u.getl();
        //cout<<a<<" "<<b<<" "<<l<<endl;
        map[a][b] = l;
        if (b<col && map[a][b+1]>map[a][b]+1){
            que.push(Node(a,b+1,l+1));
        }
        if (b>0 && map[a][b-1]>map[a][b]+1){
            que.push(Node(a,b-1,l+1));
        }
        if (a<row && map[a+1][b]>map[a][b]+1){
            que.push(Node(a+1,b,l+1));
        }
        if (a>0 && map[a-1][b]>map[a][b]+1){
            que.push(Node(a-1,b,l+1));
        }
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

    fin.close();
    ofstream fout;
    fout.open(output,ios::out);
    if(!fout){
        cout<<"out error\n";
        return 0;
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            fout<<map[i][j]<<" \n"[j==col-1];
        }
    }
    fout.close();
    return 0;

}