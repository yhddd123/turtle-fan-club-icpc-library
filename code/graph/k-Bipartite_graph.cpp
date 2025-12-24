mt19937 rnd(1);
int id[maxn];
int st[maxn*maxn],tp;
int to[maxn<<1];
bool vis[maxn<<1];
int que[maxn*maxn],tl;
vector<vector<int>> color(vector<vector<int>> e){
    vector<vector<int>> ans;
    int n=e.size()-1,d=e[1].size();
    for(int i=1;i<=n;i++)id[i]=i;
    for(int i=1;i<=n;i++){
        for(int j=0;j<d;j++)e[i][j]+=n;
    }
    while(d){
        vector<int> res;
        shuffle(id+1,id+n+1,rnd);
        for(int i=1;i<=2*n;i++)to[i]=0;
        for(int i=1;i<=n;i++){
            int x=id[i],y=0;st[++tp]=x;
            while(!y||to[y]){
                while(!y||y==to[x])y=e[x][rnd()%d];
                st[++tp]=y,x=to[y],st[++tp]=x;
            }
            tp--;
            while(tp){
                if(vis[st[tp]]){
                    while(tl&&que[tl]!=st[tp])vis[que[tl]]=0,tl--;
                    vis[que[tl]]=0,tl--;
                }
                vis[st[tp]]=1,que[++tl]=st[tp];
                tp--;
            }
            for(int j=1;j<=tl;j++)vis[que[j]]=0;
            while(tl){
                to[que[tl-1]]=que[tl],to[que[tl]]=que[tl-1];
                tl-=2;
            }
        }
        for(int i=1;i<=n;i++){
        	res.pb(to[i]-n);
        	for(int j=0;j<d;j++)if(e[i][j]==to[i]){swap(e[i][j],e[i][d-1]);break;}
        }
    	ans.pb(res);
        d--;
    }
    return ans;
}