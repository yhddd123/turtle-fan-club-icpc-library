int B,bas,h0,n;
struct hsh_table{
}mp;
int bsgs(int v){
    int mul=v;
    for(int i=0;i<=mod/B;i++){
        if(mp.find(mul))return i*B+mp[mul];
        mul=1ll*mul*bas%mod;
    }
}
/*
mod=ba+c
log(a)=log(-c)-log(b)=log(mod-1)+log(c)-log(b)
log(a)=log(a-c)-log(b+1)
min(c,a-c)<=a/2
*/
int h[maxn];
int sovle(int a){
    int b=mod/a,c=mod%a;
    if(a<=n)return h[a];
    if(c<a-c)return inc(inc(h0,sovle(c)),(mod-1-h[b]));
    else return inc(sovle(a-c),mod-1-h[b+1]);
}
bool vis[maxn];
int pre[maxn],cnt;
int a[maxn],b[maxn];
void init(){
    n=sqrt(mod)+1;B=sqrt(1ll*mod*n/log2(n));
    int mul=1;for(int i=0;i<B;i++){
        mp[mul]=i;
        mul=1ll*mul*g%mod;
    }
    bas=ksm(ksm(g,B));
    h0=bsgs(mod-1);
    h[1]=0;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            h[i]=bsgs(i);
            pre[++cnt]=i;
        }
        for(int j=1;j<=cnt&&1ll*i*pre[j]<=n;j++){
            vis[i*pre[j]]=0;
            h[i*pre[j]]=(h[i]+h[pre[j]])%(mod-1);
            if(i%pre[j]==0)break;
        }
    }
}