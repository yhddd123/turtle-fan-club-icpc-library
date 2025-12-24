int h[maxn];bool vis[maxn];
void spfa(){
	queue<int> q;
	for(int i=1;i<=n;i++)h[i]=inf,vis[i]=0;
	h[s]=0,vis[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&h[v]>h[u]+e[i].c){
				h[v]=h[u]+e[i].c;
				if(!vis[v])vis[v]=1,q.push(v);
			}
		}
	}
}
int dis[maxn],pre[maxn],id[maxn];
bool dij(){
	priority_queue<pii> q;
	for(int i=1;i<=n;i++)dis[i]=inf,vis[i]=0;
	dis[s]=0;q.push({0,s});
	while(!q.empty()){
		int u=q.top().se;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to,val=e[i].c+h[u]-h[v];
			if(e[i].w&&dis[v]>dis[u]+val){
				dis[v]=dis[u]+val,pre[v]=u,id[v]=i;
				q.push({-dis[v],v});
			}
		}
	}
	return dis[t]!=inf;
}
void work(){
	spfa();
	while(dij()){
		for(int i=1;i<=n;i++)h[i]+=dis[i];
		int mn=inf;
		for(int u=t;u!=s;u=pre[u])mn=min(mn,e[id[u]].w);
		flow+=mn;
		for(int u=t;u!=s;u=pre[u]){
			e[id[u]].w-=mn,e[id[u]^1].w+=mn;
            ans+=e[id[u]].c*mn;
		}
	}
	printf("%lld %lld\n",flow,ans);
}