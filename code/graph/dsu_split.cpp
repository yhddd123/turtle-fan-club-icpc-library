set<int> e[maxn],id[maxn<<1];
int fa[maxn],idx;
ll del[maxn*3];
struct node{
	int u,fa;
	set<int>::iterator it;
};
void add(int u,int v){
	e[u].insert(v),e[v].insert(u);
	int uu=fa[u],vv=fa[v];
	sum+=1ll*id[uu].size()*id[vv].size();
	if(id[uu].size()<id[vv].size())swap(u,v),swap(uu,vv);
	for(int i:id[vv])fa[i]=uu,id[uu].insert(i);id[vv].clear();
}
void del(int u,int v){
	e[u].erase(v),e[v].erase(u);
	vector<int> pos[2];
	queue<node> que[2];
	pos[0].pb(u),pos[1].pb(v);
	if(e[u].size())que[0].push({u,0,e[u].begin()});
	if(e[v].size())que[1].push({v,0,e[v].begin()});
	while(que[0].size()&&que[1].size()){
		int o=pos[1].size()<pos[0].size();
		auto[u,fa,it]=que[o].front();que[o].pop();
		int v=(*it);
		if(v!=fa){
			pos[o].pb(v);
			if(e[v].size())que[o].push({v,u,e[v].begin()});
		}
		it++;
		if(it==e[u].end())continue;
		if((*it)==fa)it++;
		if(it==e[u].end())continue;
		que[o].push({u,fa,it});
	}
	if(!que[0].size()&&(que[1].size()||pos[0].size()<pos[1].size())){
		swap(u,v),swap(pos[0],pos[1]);
	}
	del[qq]+=1ll*pos[1].size()*(id[fa[u]].size()-pos[1].size());
	++idx;
	for(int i:pos[1])id[fa[u]].erase(i),id[idx].insert(i),fa[i]=idx;
}