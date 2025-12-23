int n,q,k=3;
vector<int> e[maxn];
int siz[maxn],son[maxn],fa[maxn];
int dfn[maxn],st[18][maxn],tim;
void dfs(int u){
	siz[u]=1;
	st[0][dfn[u]=++tim]=fa[u];
	vector<int> tmp;
	for(int v:e[u])if(v!=fa[u]){
		fa[v]=u;dfs(v);siz[u]+=siz[v];
		tmp.pb(v);
	}
	e[u]=tmp;
	sort(e[u].begin(),e[u].end(),[&](int u,int v){return siz[u]>siz[v];});
	if(e[u].size())son[u]=e[u][0];	
}
int id[maxn],idx;
void downid(int u,int d){
	if(!d){
		if(!id[u])id[u]=++idx;
		return ;
	}
	for(int v:e[u])downid(v,d-1);
}
void dfsid(int u){
	vector<int> path;
	for(int x=u;x;x=son[x])path.pb(x);
	for(int i=0;i<=k;i++){
		for(int u:path)downid(u,i);
	}
	reverse(path.begin(),path.end());
	for(int u:path){
		for(int v:e[u])if(v!=son[u])dfsid(v);
	}
}
void merge(vector<pii> &u,vector<pii> v){
	for(auto p:v)u.pb(p);
}
void reinit(vector<pii> &u){
	sort(u.begin(),u.end());
	vector<pii> nw;
	for(auto[l,r]:u){
		if(nw.size()&&nw.back().se+1==l)nw.back().se=r;
		else nw.pb({l,r});
	}
	u=nw;
}
vector<pii> sub[maxn],kson[maxn][maxk],bro[maxn][maxk];
void dfsup(int u){
	sub[u]={{id[u],id[u]}},kson[u][0]={{id[u],id[u]}};
	for(int v:e[u]){
		dfsup(v);
		merge(sub[u],sub[v]);
		for(int i=0;i<=k;i++)bro[v][i]=kson[u][i];
		for(int i=1;i<=k;i++)merge(kson[u][i],kson[v][i-1]),reinit(kson[u][i]);
	}
	if(e[u].size()){
		vector<pii> tmp[maxk];
		for(int ii=e[u].size()-1;~ii;ii--){
			int v=e[u][ii];
			for(int i=1;i<=k;i++)merge(bro[v][i],tmp[i]),reinit(bro[v][i]);
			for(int i=1;i<=k;i++)merge(tmp[i],kson[v][i-1]),reinit(tmp[i]);
		}
	}
	reinit(sub[u]);
}
vector<pii> kans[maxn][maxk],kdis[maxn][maxk];
void dfsdw(int u){
	for(int i=0;i<=k;i++){
		kans[u][i]=kans[fa[u]][i];
		merge(kans[u][i],kson[u][i]);
		reinit(kans[u][i]);
	}
	for(int i=0;i<=k;i++){
		for(int j=0;j<=i;j++)merge(kdis[u][i],kson[u][j]);
		for(int j=1,x=u;j<=k&&x;x=fa[x],j++){
			for(int k=0;k<=i-j;k++)merge(kdis[u][i],bro[x][k]);
		}
		reinit(kdis[u][i]);
	}
	for(int v:e[u])dfsdw(v);
}
vector<pii> getsub(int u){return sub[u];}
vector<pii> gettp(int u,int tp,int k){
	vector<pii> a=kans[u][k],b=kans[tp][k],nw;
	for(int i=0,l=0;i<a.size();i++){
		while(l<b.size()&&b[l].se<a[i].fi)l++;
		int r=l;while(r<b.size()&&b[r].se<=a[i].se)r++;
		if(l==r)nw.pb(a[i]);
		else{
			int lst=a[i].fi;
			for(int j=l;j<r;j++){
				if(lst<b[j].fi)nw.pb({lst,b[j].fi-1});
				lst=b[j].se+1;
			}
			if(lst<=a[i].se)nw.pb({lst,a[i].se});
		}
		l=r;
	}
	reinit(nw);
	return nw;
}
vector<pii> getpath(int u,int v,int k){
	int tp=lca(u,v);
	vector<pii> a=kdis[tp][k];
	merge(a,gettp(u,tp,k));
	merge(a,gettp(v,tp,k));
	reinit(a);
	return a;
}
void work(){
	dfs(1);
	lca_init();
	dfsid(1);
	dfsup(1);
	dfsdw(1);
}