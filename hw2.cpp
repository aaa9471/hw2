#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include<queue>
#include<array>

int row,col,battery;
using namespace std;

class Node
{
    public:
    Node(){i=0,j=0,lenth=0,time = 0;};
    Node(int x,int y,int z,int t){i=x,j=y,lenth = z,time = t;};
    Node(int x,int y,int z){i=x,j=y,lenth = z,time = 0;};
    ~Node(){;};
    int geti(){return i;};
    int getj(){return j;};
    int getl(){return lenth;};
    int gett(){return time;};
    void len(int l){lenth = l;};
    private:
    int i,j,lenth,time;
};

//array<array<Node,1000>,1000> map ;
Node map[1000][1000];
int  BFS(int i,int j){
    queue<Node> que;
    que.push(Node(i,j,0));
    while(!que.empty()){
        Node u = que.front(); que.pop();
        int a = u.geti(),b = u.getj(),l = u.getl();
        if(2*l>battery)return 0;
        //cout<<a<<" "<<b<<" "<<l<<endl;
        map[a][b].len(l);
        if (b<col-1 && map[a][b+1].getl()>map[a][b].getl()+1){
            que.push(Node(a,b+1,l+1));
        }
        if (b>0 && map[a][b-1].getl()>map[a][b].getl()+1){
            que.push(Node(a,b-1,l+1));
        }
        if (a<row-1 && map[a+1][b].getl()>map[a][b].getl()+1){
            que.push(Node(a+1,b,l+1));
        }
        if (a>0 && map[a-1][b].getl()>map[a][b].getl()+1){
            que.push(Node(a-1,b,l+1));
        }
    }
    return 1;

}
/*
class Ans
{
    public:
    Ans(int a,int b){i=a,j=b;};
    ~Ans(){;};
    int i_get(){return i;};
    int j_get(){return j;};
    
    private:
    int i,j;
};

int vis[1000][1000] ={0};
pair<int,int> max1(int i,int j){
    int vw = vis[i-1][j],vs = vis[i+1][j],vd = vis[i][j+1], va = vis[i][j-1];
    int mw = map[i-1][j],ms = map[i+1][j],md = map[i][j+1], ma = map[i][j-1];

}

vector<Ans> ans;
void clean (int i,int j,int bat){
    if (2*bat<battery){
        if(j<col-1 && map[i][j+1]>=map[i][j-1]&&map[i][j+1]>=map[i+1][j]&&map[i][j+1]>=map[i-1][j]){
            clean(i,j+1,bat-1);
        }        
        else if (i>0 && map[i-1][j]>map[i][j+1]&&map[i-1][j]>=map[i][j-1]&&map[i-1][j]>=map[i+1][j]&&){
            clean(i-1,j,bat-1);
        }
        else if (j>0 && map[i][j-1]>map[i][j+1]&&map[i][j-1]>map[i-1][j]&&map[i][j-1]>=map[i+1][j]&&){
            clean(i,j-1,bat-1);
        }
        else if (i<row-1 && map[i+1][j]>map[i][j+1]&&map[i+1][j]>map[i][j-1]&&map[i+1][j]>map[i-1][j]&&){
            clean(i+1,j,bat-1);
        }
    }
    else {
        if(j<col-1 && bat>=map[i][j+1]>=map[i][j-1]&&map[i][j+1]>=map[i+1][j]&&map[i][j+1]>=map[i-1][j]){
            clean(i,j+1,bat-1);
        }        
        else if (i>0 && bat>=map[i-1][j]>map[i][j+1]&&map[i-1][j]>=map[i][j-1]&&map[i-1][j]>=map[i+1][j]&&){
            clean(i-1,j,bat-1);
        }
        else if (j>0 && bat>=map[i][j-1]>map[i][j+1]&&map[i][j-1]>map[i-1][j]&&map[i][j-1]>=map[i+1][j]&&){
            clean(i,j-1,bat-1);
        }
        else if (i<row-1 && bat>=map[i+1][j]>map[i][j+1]&&map[i+1][j]>map[i][j-1]&&map[i+1][j]>map[i-1][j]&&){
            clean(i+1,j,bat-1);
        }
    }
}
*/
int main (int argc,char* argv[]){
    int  ans = 0;
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
            if (road == '1') map[i][j] = Node(i,j,-1,0);
            else if (road == '0')map[i][j] = Node(i,j,3000000,0);
            else if (road == 'R'){
                map[i][j] = Node(i,j,0,0);
                i_start = i;
                j_start = j;
            }
        }
    }
    //road lenth
    if(!BFS(i_start,j_start)){
        fin.close();
        ofstream fout;
        fout.open(output,ios::out);
        fout<<"the machine cannot clean the room\n";
        cout<<"the machine cannot clean the room\n";
        fout.close();
        return 0;
    }

    //clean(i_start,j_start,battery);

    fin.close();
    ofstream fout;
    fout.open(output,ios::out);
    if(!fout){
        cout<<"out error\n";
        return 0;
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            fout<<map[i][j].getl()<<" \n"[j==col-1];
        }
    }
    fout.close();
    return 0;

}