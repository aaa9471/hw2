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
int row0 = 0,col0 = 0;
int row,col,battery;
int i_start,j_start;//the start position
using namespace std;
vector<pair<int,int>> ans;
int situation[4] = {0};// 0:right, 1:up, 2:left, 3:down


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
    void plustime(){
        if(t == 0){
            if(i>i_start)situation[3]--;
            if(i<i_start)situation[1]--;
            if(j>j_start)situation[0]--;
            if(j<j_start)situation[2]--;
        }
        t+=1;

    };
    void len(int l){lenth = l;};
    private:
    int i,j,lenth,t;
};

//array<array<Node,1000>,1000> map ;
Node map[1010][1010];
bool vis[1001][1010];

int  BFS(int i,int j){
    int x=0;
    queue<Node> que;
    que.push(Node(i,j,0));
    while(!que.empty()){
        Node u = que.front(); que.pop();
        int a = u.geti(),b = u.getj(),l = u.getl();
        vis[a][b] = true;
        if(2*l>battery+2)return 0;
        if(b>j_start)situation[0]++;
        if(a<i_start)situation[1]++;
        if(b<j_start)situation[2]++;
        if(a>i_start)situation[3]++;
        //cout<<a<<" "<<b<<" "<<l<<endl;
        if(map[a][b].getl()>l)map[a][b].len(l);
        if (b<col-1 && !vis[a][b+1] && map[a][b+1].getl()>map[a][b].getl()+1){
            vis[a][b+1] = true;
            que.push(Node(a,b+1,l+1));
        }
        if (b>0 && !vis[a][b-1] && map[a][b-1].getl()>map[a][b].getl()+1){
            vis[a-1][b] = true;
            que.push(Node(a,b-1,l+1));
        }
        if (a<row-1 && !vis[a+1][b] && map[a+1][b].getl()>map[a][b].getl()+1){
            vis[a+1][b] = true;
            que.push(Node(a+1,b,l+1));
        }
        if (a>0 && !vis[a-1][b] && map[a-1][b].getl()>map[a][b].getl()+1){
            vis[a-1][b] = true;
            que.push(Node(a-1,b,l+1));
        }
    }
    return 1;

}
int up,down,rt,lt;
int mint(int i, int j,int bat){
    int w = (i<=row0||map[i-1][j].getl()>=bat||map[i-1][j].getl() == -1)?infty:map[i-1][j].gett();
    int a = (j<=col0||map[i][j-1].getl()>=bat||map[i][j-1].getl() == -1)?infty:map[i][j-1].gett();
    int s = (i>=row-1||map[i+1][j].getl()>=bat||map[i+1][j].getl() == -1)?infty:map[i+1][j].gett();
    int d = (j>=col-1||map[i][j+1].getl()>=bat||map[i][j+1].getl() == -1)?infty:map[i][j+1].gett();
    int m = (w<s)?w:s;
    int n = a<d?a:d;
    //cout<<j<<" "<<col<<endl;
    up = w,down = s, rt = d, lt = a;
    return m<n?m:n;
}

int maxl(int i,int j,int bat){
    int w =(i>row0)? map[i-1][j].getl():0,a =(j>col0)? map[i][j-1].getl():0;
    int s =(i<row-1)? map[i+1][j].getl():0,d =(j<col-1)? map[i][j+1].getl():0;
    w = (w<bat&&map[i-1][j].getl() != -1)?w:0;
    a = (a<bat&&map[i][j-1].getl() != -1)?a:0;
    s = (s<bat&&map[i+1][j].getl() != -1)?s:0;
    d = (d<bat&&map[i][j+1].getl() != -1)?d:0;
    //up = w,down = s, rt = d, lt = a;
    int m = (w>s)?w:s, n = (a>d)?a:d;
    return m>n?m:n;
}
int x=0;
void clean (int i,int j,int bat,int dir){
    Node *w = &map[i-1][j],*a = &map[i][j-1], *s = &map[i+1][j], *d = &map[i][j+1];
    //cout<<map[13][8].gett()<<endl;
    //cout<<i<<","<<j<<","<<bat<<clear<<endl;
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
    else if (i>row0&&bat>w->getl()&&w->gett()==mint(i,j,bat) && w->getl() == maxl(i,j,bat)){
        ans.push_back(make_pair(i-1,j));
        if(!w->gett())clear+=1;
        w->plustime();
        clean(i-1,j,bat-1,8);
    }
    else if (j>col0&&bat>a->getl()&&a->gett()==mint(i,j,bat)&& a->getl() == maxl(i,j,bat)){
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
    else if (j>col0&&bat>a->getl()&&a->gett()==mint(i,j,bat)&& a->getl() <= maxl(i,j,bat)){
        ans.push_back(make_pair(i,j-1));
        if(!a->gett())clear+=1;
        a->plustime();
        clean(i,j-1,bat-1,4);
    }    
    else if (i>row0&&bat>w->getl()&&w->gett()==mint(i,j,bat) && w->getl() <= maxl(i,j,bat)){
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

int maxsituation(){
    int a = situation[0]>situation[1]?situation[0]:situation[1];
    int b = situation[2]>situation[3]?situation[2]:situation[3];
    return a>b?a:b;
}

void check(){
    int a=0,b=0,c=0,d=0;
    for(int i=col0;i<col;i++){
        if(map[row0][i].gett() <= 9)a = 1; 
        if(map[row-1][i].gett() <= 9 )b = 1;
    }
    for(int i=row0;i<row;i++){
        if(map[i][col0].gett() <= 9)c = 1; 
        if(map[i][col-1].gett() <= 9)d = 1;
    }
    //cout<<b<<endl;
    row0 =(i_start>row0 &&a==0)?row0+1:row0;
    row = (i_start<row-1&&b==0)?row-1:row;
    col0 =(j_start>col0 &&c==0)?col0+1:col0;
    col = (j_start<col-1&&d==0)?col-1:col;
    return;
}

void Clean(int i,int j){
    int dir = 0,bat = battery;
    int err = 0,alclear = 0;
    while (clear <dirty||bat>0){
        //cout<<ans.size()<<endl;        
        //printf("%d %d %d %d %d %d\n",i,j,bat,map[i][j].getl(),row0,col0);
        Node *w = &map[i-1][j],*a = &map[i][j-1], *s = &map[i+1][j], *d = &map[i][j+1];
        if(situation[0] == situation[0]){
            if (j<col-1&&bat>d->getl()&& d->gett() == mint(i,j,bat) && d->getl() == maxl(i,j,bat)){
                ans.push_back(make_pair(i,j+1));
                if(d->gett() == 0)clear+=1;
                d->plustime();
                i =i;
                j++;
                bat--;
                dir = 6;
            }
            else if (i>row0&&bat>w->getl()&&w->gett()==mint(i,j,bat) && w->getl() == maxl(i,j,bat)){
                ans.push_back(make_pair(i-1,j));
                if(!w->gett())clear+=1;
                w->plustime();
                i--;
                bat--;
                dir = 8;
            }
            else if (j>col0&&bat>a->getl()&&a->gett()==mint(i,j,bat)&& a->getl() == maxl(i,j,bat)){
                ans.push_back(make_pair(i,j-1));
                if(!a->gett())clear+=1;
                a->plustime();
                j--;
                bat--;
                dir = 4;
            }
            else if (i<row-1&&bat>s->getl()&&s->gett() == mint(i,j,bat)&&s->getl()<=maxl(i,j,bat)){
                ans.push_back(make_pair(i+1,j));
                if(!s->gett())clear+=1;
                s->plustime();
                //cout<<s.geti()<<" "<<s.getj()<<" "<<s.gett()<<map[4][6].getl()<<endl;
                i++;
                bat--;
                dir = 2;
            }
            else if (i == i_start&& j == j_start){
                //check();
                //cout<<row<<" "<<col<<endl;
                if(clear>alclear)alclear = clear;
                else err++;
                //if(clear >= 500000)break;
                switch(dir){
                    case 6:
                        ans.push_back(make_pair(i,j-1));
                        if(!a->gett())clear+=1;
                        a->plustime();
                        j--;
                        bat = battery-1;
                        dir =4;
                        break;
                    case 8:
                        ans.push_back(make_pair(i+1,j));
                        if(!s->gett())clear+=1;
                        s->plustime();
                        i++;
                        bat = battery -1;
                        dir = 2;
                        break;
                    case 4:
                        ans.push_back(make_pair(i,j+1));
                        if(!d->gett())clear+=1;
                        d->plustime();
                        j++;
                        bat = battery-1;
                        dir = 6;
                        break;
                    case 2:
                        ans.push_back(make_pair(i-1,j));
                        if(!w->gett())clear+=1;
                        w->plustime();
                        i--;
                        bat = battery -1;
                        dir = 8;
                        break;
                    default:
                        return;
                }

            }
            else if (j>col0&&bat>a->getl()&&a->gett()==mint(i,j,bat)&& a->getl() <= maxl(i,j,bat)){
                ans.push_back(make_pair(i,j-1));
                if(!a->gett())clear+=1;
                a->plustime();
                j--;
                bat--;
                dir = 4;
            }    
            else if (i>row0&&bat>w->getl()&&w->gett()==mint(i,j,bat) && w->getl() <= maxl(i,j,bat)){
                ans.push_back(make_pair(i-1,j));
                if(!w->gett())clear+=1;
                w->plustime();
                i--;
                bat--;
                dir = 8;
            }
            else if (j<col-1 &&bat>d->getl()&& d->gett() == mint(i,j,bat) && d->getl() <= maxl(i,j,bat)){
                //cout<<i<<" "<<j<<" "<<d.gett()<<" "<<mint(i,j)<<endl;
                ans.push_back(make_pair(i,j+1));
                if(!d->gett())clear+=1;
                d->plustime();
                //cout<<d.gett();
                j++;
                bat --;
                dir = 6;
            }
            else {
                cout<<mint(i,j,bat)<<" "<<maxl(i,j,bat)<<endl;
                cout<<w->getl()<<" "<<w->gett()<<endl;
                cout<<a->getl()<<" "<<a->gett()<<endl;
                cout<<s->getl()<<" "<<s->gett()<<endl;
                cout<<d->getl()<<" "<<d->gett()<<endl; 
                cout<<i<<" "<<j<<endl;
                cout<<i_start<<" "<<j_start<<endl;
                printf("%d %d %d %d\n",up,lt,down,rt);
                cout<<"r"<<endl;
                cout<<row<<" "<<col<<endl;
                cout<<bat<<endl;
                cout<<clear<<"/"<<dirty<<endl;
                return;
            }
        }
        else if (situation[1] == maxsituation()){
            if (i == i_start&& j == j_start){
                if(clear>alclear)alclear = clear;
                else err++;
                if(err == 1000)break;
                switch(dir){
                    case 6:
                        ans.push_back(make_pair(i,j-1));
                        if(!a->gett())clear+=1;
                        a->plustime();
                        j--;
                        bat = battery-1;
                        dir =4;
                        break;
                    case 8:
                        ans.push_back(make_pair(i+1,j));
                        if(!s->gett())clear+=1;
                        s->plustime();
                        i++;
                        bat = battery -1;
                        dir = 2;
                        break;
                    case 4:
                        ans.push_back(make_pair(i,j+1));
                        if(!d->gett())clear+=1;
                        d->plustime();
                        j++;
                        bat = battery-1;
                        dir = 6;
                        break;
                    case 2:
                        ans.push_back(make_pair(i-1,j));
                        if(!w->gett())clear+=1;
                        w->plustime();
                        i--;
                        bat = battery -1;
                        dir = 8;
                        break;
                    default:
                        ans.push_back(make_pair(i,j-1));
                        if(!a->gett())clear+=1;
                        a->plustime();
                        j--;
                        bat = battery-1;
                        dir =4;
                        break;
                }

            }
            else if (i>row0&&bat>w->getl()&&w->gett()==mint(i,j,bat) && w->getl() == maxl(i,j,bat)){
                ans.push_back(make_pair(i-1,j));
                if(!w->gett())clear+=1;
                w->plustime();
                i--;
                bat--;
                dir = 8;
            }
            else if (j>col0&&bat>a->getl()&&a->gett()==mint(i,j,bat)&& a->getl() == maxl(i,j,bat)){
                ans.push_back(make_pair(i,j-1));
                if(!a->gett())clear+=1;
                a->plustime();
                j--;
                bat--;
                dir = 4;
            }
            else if (i<row&&bat>s->getl()&&s->gett() == mint(i,j,bat)&&s->getl() == maxl(i,j,bat)){
                ans.push_back(make_pair(i+1,j));
                if(!s->gett())clear+=1;
                s->plustime();
                i++;
                bat--;
                dir = 2;
            }
            else if (j<col &&bat>d->getl()&& d->gett() == mint(i,j,bat) && d->getl() <= maxl(i,j,bat)){
                ans.push_back(make_pair(i,j+1));
                if(d->gett() == 0)clear+=1;
                d->plustime();
                i =i;
                j++;
                bat--;
                dir = 6;
            }
            else if (i<row&&bat>s->getl()&&s->gett() == mint(i,j,bat)&&s->getl() <= maxl(i,j,bat)){
                ans.push_back(make_pair(i+1,j));
                if(!s->gett())clear+=1;
                s->plustime();
                i++;
                bat--;
                dir = 2;
            }
            else if (j>col0&&bat>a->getl()&&a->gett()==mint(i,j,bat)&& a->getl() <= maxl(i,j,bat)){
                ans.push_back(make_pair(i,j-1));
                if(!a->gett())clear+=1;
                a->plustime();
                j--;
                bat--;
                dir = 4;
            }    
            else if (i>row0&&bat>w->getl()&&w->gett()==mint(i,j,bat) && w->getl() <= maxl(i,j,bat)){
                ans.push_back(make_pair(i-1,j));
                if(!w->gett())clear+=1;
                w->plustime();
                i--;
                bat--;
                dir = 8;
            }
            else {
                cout<<mint(i,j,bat)<<" "<<maxl(i,j,bat)<<endl;
                cout<<w->getl()<<" "<<w->gett()<<endl;
                cout<<a->getl()<<" "<<a->gett()<<endl;
                cout<<s->getl()<<" "<<s->gett()<<endl;
                cout<<d->getl()<<" "<<d->gett()<<endl; 
                cout<<map[i_start][j_start].gett()<<endl;
                printf("%d %d %d %d\n",up,lt,down,rt);
                cout<<"r"<<endl;
                cout<<bat<<endl;
                cout<<clear<<"/"<<dirty<<endl;
                return;
            }
        }
        else if (situation[2] == maxsituation()){
            if (i == i_start&& j == j_start){
                if(clear>alclear)alclear = clear;
                else err++;
                if(err == 1000)break;
                switch(dir){
                    case 6:
                        ans.push_back(make_pair(i,j-1));
                        if(!a->gett())clear+=1;
                        a->plustime();
                        j--;
                        bat = battery-1;
                        dir =4;
                        break;
                    case 8:
                        ans.push_back(make_pair(i+1,j));
                        if(!s->gett())clear+=1;
                        s->plustime();
                        i++;
                        bat = battery -1;
                        dir = 2;
                        break;
                    case 4:
                        ans.push_back(make_pair(i,j+1));
                        if(!d->gett())clear+=1;
                        d->plustime();
                        j++;
                        bat = battery-1;
                        dir = 6;
                        break;
                    case 2:
                        ans.push_back(make_pair(i-1,j));
                        if(!w->gett())clear+=1;
                        w->plustime();
                        i--;
                        bat = battery -1;
                        dir = 8;
                        break;
                    default:
                        ans.push_back(make_pair(i,j-1));
                        if(!a->gett())clear+=1;
                        a->plustime();
                        j--;
                        bat = battery-1;
                        dir =4;
                        break;
                }

            }
            else if (j>col0&&bat>a->getl()&&a->gett()==mint(i,j,bat)&& a->getl() == maxl(i,j,bat)){
                ans.push_back(make_pair(i,j-1));
                if(!a->gett())clear+=1;
                a->plustime();
                j--;
                bat--;
                dir = 4;
            }
            else if (i<row&&bat>s->getl()&&s->gett() == mint(i,j,bat)&&s->getl() == maxl(i,j,bat)){
                ans.push_back(make_pair(i+1,j));
                if(!s->gett())clear+=1;
                s->plustime();
                i++;
                bat--;
                dir = 2;
            }
            else if (j<col &&bat>d->getl()&& d->gett() == mint(i,j,bat) && d->getl() == maxl(i,j,bat)){
                ans.push_back(make_pair(i,j+1));
                if(d->gett() == 0)clear+=1;
                d->plustime();
                i =i;
                j++;
                bat--;
                dir = 6;
            }
            else if (i>row0&&bat>w->getl()&&w->gett()==mint(i,j,bat) && w->getl() <= maxl(i,j,bat)){
                ans.push_back(make_pair(i-1,j));
                if(!w->gett())clear+=1;
                w->plustime();
                i--;
                bat--;
                dir = 8;
            }
            else if (j<col &&bat>d->getl()&& d->gett() == mint(i,j,bat) && d->getl() <= maxl(i,j,bat)){
                ans.push_back(make_pair(i,j+1));
                if(d->gett() == 0)clear+=1;
                d->plustime();
                i =i;
                j++;
                bat--;
                dir = 6;
            }
            else if (i<row&&bat>s->getl()&&s->gett() == mint(i,j,bat)&&s->getl() == maxl(i,j,bat)){
                ans.push_back(make_pair(i+1,j));
                if(!s->gett())clear+=1;
                s->plustime();
                i++;
                bat--;
                dir = 2;
            }
            else {
                cout<<mint(i,j,bat)<<" "<<maxl(i,j,bat)<<endl;
                cout<<w->getl()<<" "<<w->gett()<<endl;
                cout<<a->getl()<<" "<<a->gett()<<endl;
                cout<<s->getl()<<" "<<s->gett()<<endl;
                cout<<d->getl()<<" "<<d->gett()<<endl; 
                cout<<map[i_start][j_start].gett()<<endl;
                printf("%d %d %d %d\n",up,lt,down,rt);
                cout<<"r"<<endl;
                cout<<bat<<endl;
                cout<<clear<<"/"<<dirty<<endl;
                return;
            }
        }
        else {
            if (i == i_start&& j == j_start){
                if(clear>alclear)alclear = clear;
                else err++;
                if(err == 1000)break;
                switch(dir){
                    case 6:
                        ans.push_back(make_pair(i,j-1));
                        if(!a->gett())clear+=1;
                        a->plustime();
                        j--;
                        bat = battery-1;
                        dir =4;
                        break;
                    case 8:
                        ans.push_back(make_pair(i+1,j));
                        if(!s->gett())clear+=1;
                        s->plustime();
                        i++;
                        bat = battery -1;
                        dir = 2;
                        break;
                    case 4:
                        ans.push_back(make_pair(i,j+1));
                        if(!d->gett())clear+=1;
                        d->plustime();
                        j++;
                        bat = battery-1;
                        dir = 6;
                        break;
                    case 2:
                        ans.push_back(make_pair(i-1,j));
                        if(!w->gett())clear+=1;
                        w->plustime();
                        i--;
                        bat = battery -1;
                        dir = 8;
                        break;
                    default:
                        ans.push_back(make_pair(i,j-1));
                        if(!a->gett())clear+=1;
                        a->plustime();
                        j--;
                        bat = battery-1;
                        dir =4;
                        break;
                }

            }

            else if (i<row&&bat>s->getl()&&s->gett() == mint(i,j,bat)&&s->getl() == maxl(i,j,bat)){
                ans.push_back(make_pair(i+1,j));
                if(!s->gett())clear+=1;
                s->plustime();
                i++;
                bat--;
                dir = 2;
            }
            else if (j<col &&bat>d->getl()&& d->gett() == mint(i,j,bat) && d->getl() == maxl(i,j,bat)){
                ans.push_back(make_pair(i,j+1));
                if(d->gett() == 0)clear+=1;
                d->plustime();
                i =i;
                j++;
                bat--;
                dir = 6;
            }
            else if (i>row0&&bat>w->getl()&&w->gett()==mint(i,j,bat) && w->getl() == maxl(i,j,bat)){
                ans.push_back(make_pair(i-1,j));
                if(!w->gett())clear+=1;
                w->plustime();
                i--;
                bat--;
                dir = 8;
            }
            else if (j>col0&&bat>a->getl()&&a->gett()==mint(i,j,bat)&& a->getl() <= maxl(i,j,bat)){
                ans.push_back(make_pair(i,j-1));
                if(!a->gett())clear+=1;
                a->plustime();
                j--;
                bat--;
                dir = 4;
            }    
            else if (i>row0&&bat>w->getl()&&w->gett()==mint(i,j,bat) && w->getl() <= maxl(i,j,bat)){
                ans.push_back(make_pair(i-1,j));
                if(!w->gett())clear+=1;
                w->plustime();
                i--;
                bat--;
                dir = 8;
            }
            else if (j<col &&bat>d->getl()&& d->gett() == mint(i,j,bat) && d->getl() <= maxl(i,j,bat)){
                ans.push_back(make_pair(i,j+1));
                if(d->gett() == 0)clear+=1;
                d->plustime();
                i =i;
                j++;
                bat--;
                dir = 6;
            }
            else if (i<row&&bat>s->getl()&&s->gett() == mint(i,j,bat)&&s->getl() <= maxl(i,j,bat)){
                ans.push_back(make_pair(i+1,j));
                if(!s->gett())clear+=1;
                s->plustime();
                i++;
                bat--;
                dir = 2;
            }
            else {
                cout<<mint(i,j,bat)<<" "<<maxl(i,j,bat)<<endl;
                cout<<w->getl()<<" "<<w->gett()<<endl;
                cout<<a->getl()<<" "<<a->gett()<<endl;
                cout<<s->getl()<<" "<<s->gett()<<endl;
                cout<<d->getl()<<" "<<d->gett()<<endl; 
                cout<<map[i_start][j_start].gett()<<endl;
                printf("%d %d %d %d\n",up,lt,down,rt);
                cout<<"r"<<endl;
                cout<<bat<<endl;
                cout<<clear<<"/"<<dirty<<endl;
                return;
            }
        
        }
    }

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
                map[i][j] = Node(i,j,1,1);
                i_start = i;
                j_start = j;
            }
            if(road == '1') vis[i][j] = true;
            else if (road == '0')vis[i][j] = false;
            else if (road == 'R')vis[i][j] = false;
        }
    }
    //road lenth
    int rrow = row;
    int rcol = col;
    if(!BFS(i_start,j_start)){
        fin.close();
        ofstream fout;
        fout.open(output,ios::out);
        fout<<"the machine cannot clean the room\n";
        cout<<"the machine cannot clean the room\n";
        fout.close();
        return 0;
    }
    //clean(i_start,j_start,battery,0);
    Clean(i_start,j_start);
    cout<<clear<<"/"<<dirty<<endl;
    fin.close();
    ofstream fout;
    fout.open(output,ios::out);
    if(!fout){
        cout<<"out error\n";
        return 0;
    }
    
    for(int i=0;i<rrow;i++){
        for(int j=0;j<rcol;j++){
            int a = map[i][j].gett();
            a = (a>9)?9:a;
            fout<< a<<" \n"[j==col-1];
        } 
    }
    int sz = ans.size();
    /*
    fout<<sz<<endl;
    for(auto it = ans.begin();it != ans.end();it++){
        fout<<it->first<<" "<<it->second<<endl;
    }
    */
    fout.close();
    return 0;

}