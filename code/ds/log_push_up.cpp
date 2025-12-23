int mn[maxn<<2],ans[maxn<<2];
int query(int nd,int l,int r,int w){
	if(w<mn[nd])return (r-l+1)*w;
	if(l==r)return mn[nd];
	if(mn[ls]<=w)return query(ls,l,mid,w)+ans[rs];
	else return (mid-l+1)*w+query(rs,mid+1,r,w);
}
void up(int nd,int l,int r){
	mn[nd]=min(mn[ls],mn[rs]);
	ans[rs]=query(rs,mid+1,r,mn[ls]);
}
void build(int nd,int l,int r){
	if(l==r){
		mn[nd]=a[l];
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	up(nd,l,r);
}
int query(int nd,int l,int r,int ql,int qr,int &w){
	if(l>=ql&&r<=qr){
		int res=query(nd,l,r,w);
		w=min(w,mn[nd]);
		return res;
	}
	int res=0;
	if(ql<=mid)res+=query(ls,l,mid,ql,qr,w);
	if(qr>mid)res+=query(rs,mid+1,r,ql,qr,w);
	return res;
}