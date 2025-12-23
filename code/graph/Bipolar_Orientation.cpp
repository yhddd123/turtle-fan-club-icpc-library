int n,m,s,t;
pii g[maxn];
int lw[maxn],dfn[maxn],idx,fa[maxn];
vector<int> id;
bool vis[maxn];
bool dfs(int u){
	dfn[u]=lw[u]=++idx;vis[u]=1;
	bool fl=u==t;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			fa[v]=u;fl|=dfs(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
	if(fl)id.pb(u);
	return fl;
}
queue<int> q;
int d[maxn];
vector<int> a[maxn];
int st[maxn],tp,rnk[maxn];
void dfs1(int u){
	if(vis[u])return ;vis[u]=1;
	st[++tp]=u;
	for(int v:a[dfn[u]])dfs1(v);
}
void work(){
	n=read();m=read();s=read();t=read();
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
		g[i]={u,v};
	}
	idx=0;id.clear();
	for(int i=1;i<=n;i++)vis[i]=0;
	fa[s]=0;dfs(s);
	for(int i=1;i<=n;i++)d[i]=0;
	for(int i:id)d[i]++;
	for(int i=1;i<=n;i++)d[fa[i]]++;
	for(int i=1;i<=n;i++)if(!d[i])q.push(i);
	for(int i=1;i<=n;i++)a[i].clear();
	while(!q.empty()){
		int u=q.front();q.pop();
		a[lw[u]].pb(u),a[dfn[fa[u]]].pb(u);
		d[fa[u]]--;
		if(!d[fa[u]])q.push(fa[u]);
	}
	tp=0;
	for(int i=1;i<=n;i++)vis[i]=0;
	while(id.size())dfs1(id.back()),id.pop_back();
	if(st[1]!=s||st[tp]!=t){puts("No");return ;}
    check();
}