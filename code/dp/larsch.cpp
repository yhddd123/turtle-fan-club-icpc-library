struct ds{
    int l,r,ans;
    ds(){l=1,r=0;}
    ll que(int ql,int qr){
        while(r<qr)r++;
        while(l>ql)l--;
        while(r>qr)r--;
        while(l<ql)l++;
        return ans;
    }
}a[2];
void upd(int j,int i,int op){
	int nw=dp[j-1]+a[op].que(j,i)+w;
	if(nw<dp[i])dp[i]=nw,p[i]=j;
}
void sovle(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	for(int i=p[l];i<=p[r];i++)upd(i,mid,0);
	sovle(l,mid);
	for(int i=l;i<=mid;i++)upd(i,r,1);
	sovle(mid+1,r);
}