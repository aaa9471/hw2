#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include<queue>
#include<array>
#include<cstdio>
#define infty 3000000

int dirty = 0,clear = 0;
int row,col,battery;
int i_start,j_start;//the start position
using namespace std;
vector<pair<int,int>> ans;
class Node
{
    public:
    Node(){i=0,j=0,lenth=infty,t = infty;};
    Node(int x,int y,int z,int ti){i=x,j=y,lenth = z,t = ti;};
    Node(int x,int y,int z){i=x,j=y,lenth = z,t = 0;};
    ~Node(){;};
    int geti(){return i;};
    int getj(){return j;};
    int getl(){return lenth;};
    int gett(){return t;};
    void plustime(){t+=1;};
    void len(int l){lenth = l;};
    private:
    int i,j,lenth,t;
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
int up,down,rt,lt;
int mint(int i, int j,int bat){
    int w = (map[i-1][j].getl()>bat||i<=0)?infty:map[i-1][j].gett();
    int a = (map[i][j-1].getl()>bat||j<=0)?infty:map[i][j-1].gett();
    int s = (map[i+1][j].getl()>bat||i>=row-1)?infty:map[i+1][j].gett();
    int d = (j>=col-1||map[i][j+1].getl()>bat)?infty:map[i][j+1].gett();
    int m = (w<s)?w:s;
    int n = a<d?a:d;
    //cout<<j<<" "<<col<<endl;
    up = w,down = s, rt = d, lt = a;
    return m<n?m:n;
}

int maxl(int i,int j,int bat){
    int w =(i>0)? map[i-1][j].getl():0,a =(j>0)? map[i][j-1].getl():0;
    int s =(i<row-1)? map[i+1][j].getl():0,d =(j<col-1)? map[i][j+1].getl():0;
    w = (w<bat)?w:0;
    a = (a<bat)?a:0;
    s = (s<bat)?s:0;
    d = (d<bat)?d:0;

    int m = (w>s)?w:s, n = (a>d)?a:d;
    return m>n?m:n;
}
int x=0;
void clean (int i,int j,int bat,int dir){
    Node *w = &map[i-1][j],*a = &map[i][j-1], *s = &map[i+1][j], *d = &map[i][j+1];
    //cout<<map[13][8].gett()<<endl;
    cout<<i<<","<<j<<","<<bat<<clear<<endl;
    /*
    if(i == 11 && j == 7){
        cout<<mint(i,j,bat)<<" "<<maxl(i,j,bat)<<endl;
        cout<<w->getl()<<" "<<w->gett()<<endl;
        printf("%d %d %d %d\n",up,down,rt,lt);
    }
    

    //if(maxl(i,j,bat)<map[i][j].getl()&&maxl(i,j,bat)<bat)bat = map[i][j].getl();
    if(clear==82&& bat == 0){
        x+=1;
        //cout<<x<<endl;
    }
    */
    if(clear >= dirty&&bat == 0){
        /*
        for(int m =0 ;m<row;m++){
            for(int n =0;n<col;n++){
                if(map[m][n].gett()<10)cout<<map[m][n].gett();
                else if(map[m][n].gett()!=infty)cout<<9;
                else cout<<"w";
            }
            cout<<endl;
        }
        */
        return;
    }
    else if (j<col &&bat>d->getl()&& d->gett() == mint(i,j,bat) && d->getl() == maxl(i,j,bat)){
        //cout<<i<<" "<<j<<" "<<d.gett()<<" "<<mint(i,j)<<endl;
        ans.push_back(make_pair(i,j+1));
        if(d->gett() == 0)clear+=1;
        d->plustime();
        //cout<<d.gett();
        clean(i,j+1,bat-1,6);
    }
    else if (i>0&&bat>w->getl()&&w->gett()==mint(i,j,bat) && w->getl() == maxl(i,j,bat)){
        ans.push_back(make_pair(i-1,j));
        if(!w->gett())clear+=1;
        w->plustime();
        clean(i-1,j,bat-1,8);
    }
    else if (j>0&&bat>a->getl()&&a->gett()==mint(i,j,bat)&& a->getl() == maxl(i,j,bat)){
        ans.push_back(make_pair(i,j-1));
        if(!a->gett())clear+=1;
        a->plustime();
        clean(i,j-1,bat-1,4);
    }
    else if (i<row&&bat>s->getl()&&s->gett() == mint(i,j,bat)&&s->getl()<=maxl(i,j,bat)){
        ans.push_back(make_pair(i+1,j));
        if(!s->gett())clear+=1;
        s->plustime();
        //cout<<s.geti()<<" "<<s.getj()<<" "<<s.gett()<<map[4][6].getl()<<endl;
        
        clean(i+1,j,bat-1,2);
    }
    else if (bat == 0&& i == i_start&& j == j_start){
        switch(dir){
            case 6:
                ans.push_back(make_pair(i,j-1));
                clean(i,j-1,battery-1,4);
                if(!a->gett())clear+=1;
                a->plustime();
                break;
            case 8:
                ans.push_back(make_pair(i+1,j));
                if(!s->gett())clear+=1;
                s->plustime();
                clean(i+1,j,battery-1,2);
                break;
            case 4:
                ans.push_back(make_pair(i,j+1));
                if(!d->gett())clear+=1;
                d->plustime();
                clean(i,j+1,battery-1,6);
                break;
            case 2:
                ans.push_back(make_pair(i-1,j));
                if(!w->gett())clear+=1;
                w->plustime();
                clean(i-1,j,battery-1,8);
                break;
            default:
                return;
        }

    }
    else if (j>0&&bat>a->getl()&&a->gett()==mint(i,j,bat)&& a->getl() <= maxl(i,j,bat)){
        ans.push_back(make_pair(i,j-1));
        if(!a->gett())clear+=1;
        a->plustime();
        clean(i,j-1,bat-1,4);
    }    
    else if (i>0&&bat>w->getl()&&w->gett()==mint(i,j,bat) && w->getl() <= maxl(i,j,bat)){
        ans.push_back(make_pair(i-1,j));
        if(!w->gett())clear+=1;
        w->plustime();
        clean(i-1,j,bat-1,8);
    }
    else if (j<col &&bat>d->getl()&& d->gett() == mint(i,j,bat) && d->getl() <= maxl(i,j,bat)){
        //cout<<i<<" "<<j<<" "<<d.gett()<<" "<<mint(i,j)<<endl;
        ans.push_back(make_pair(i,j+1));
        if(!d->gett())clear+=1;
        d->plustime();
        //cout<<d.gett();
        clean(i,j+1,bat-1,6);
    }
    else {
        cout<<mint(i,j,bat)<<" "<<maxl(i,j,bat)<<endl;
        cout<<w->getl()<<" "<<w->gett()<<endl;
        printf("%d %d %d %d\n",up,down,rt,lt);
        cout<<"r"<<endl;
        cout<<bat<<endl;
        cout<<clear<<"/"<<dirty<<endl;
        return;
    }
    return ;


}

int main (int argc,char* argv[]){
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
    dirty = 0;
    clear = 0;
    for(int i = 0 ;i<row;i++){
        for(int j = 0;j<col;j++){
            fin>>road;
            if (road == '1') map[i][j] = Node(i,j,-1,infty);
            else if (road == '0'){
                map[i][j] = Node(i,j,infty,0);
                dirty += 1;
            }
            else if (road == 'R'){
                map[i][j] = Node(i,j,0,1);
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
    clean(i_start,j_start,battery,0);
    cout<<clear<<"/"<<dirty<<endl;
    fin.close();
    ofstream fout;
    fout.open(output,ios::out);
    if(!fout){
        cout<<"out error\n";
        return 0;
    }
    /*
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            fout<<map[i][j].getl()<<" \n"[j==col-1];
        }
    }*/
    int sz = ans.size();
    fout<<sz<<endl;
    for(auto it = ans.begin();it != ans.end();it++){
        fout<<it->first<<" "<<it->second<<endl;
    }
    fout.close();
    return 0;

}