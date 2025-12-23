vector<int> e[maxn],g[maxn];
int dfn[maxn],idx,lw[maxn];
int st[maxn],tp;
void tar(int u){
    dfn[u]=lw[u]=++idx;st[++tp]=u;
    for(int v:e[u]){
        if(!dfn[v]){
            tar(v);
            lw[u]=min(lw[u],lw[v]);
            if(lw[v]>=dfn[u]){
                g[++num].push_back(st[tp]);
                while(st[tp--]!=v){
                    g[num].push_back(st[tp]);
                }
                g[num].push_back(u);
            }
        }
        else lw[u]=min(lw[u],dfn[v]);
    }
}