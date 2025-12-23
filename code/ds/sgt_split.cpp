int merge(int u,int v,int l,int r){
	if(!u||!v)return u|v;
	if(l==r){tree[u]+=tree[v];clr(v);return u;}
	lc[u]=merge(lc[u],lc[v],l,mid);
	rc[u]=merge(rc[u],rc[v],mid+1,r);
	tree[u]=tree[lc[u]]+tree[rc[u]];clr(v);
	return u;
}
int split(int nd,int l,int r,ll k){
	if(!nd)return 0;
	int u=newnode();
	if(k>tree[ls])rc[u]=split(rs,mid+1,r,k-tree[ls]);
	else rc[u]=rs,rs=0;
	if(k<tree[ls])lc[u]=split(ls,l,mid,k);
	tree[nd]=tree[ls]+tree[rs],tree[u]=tree[lc[u]]+tree[rc[u]];
	return u;
}