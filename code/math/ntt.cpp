int gg=3,invg=ksm(gg);
int to[maxn<<3];
vector<int> ntt(vector<int> a,int flag){
    int n=a.size();
    for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
    for(int len=2;len<=n;len<<=1){
        int bas=ksm(flag==1?gg:invg,(mod-1)/len),l=len>>1;
        for(int i=0;i<n;i+=len){
            int mul=1;
            for(int j=i;j<i+l;j++){
                int val=mul*a[j+l]%mod;
                inc(a[j+l]=a[j],mod-val);
                inc(a[j],val);
                mul=mul*bas%mod;
            }
        }
    }
    if(flag==-1){
        int inv=ksm(n);
        for(int i=0;i<n;i++)a[i]=a[i]*inv%mod;
    }
    return a;
}
vector<int> mul(vector<int> a,vector<int> b){
    int n=a.size()-1,m=b.size()-1;int k=1;
    while(k<n+m+1)k<<=1;
    vector<int> f(k),g(k);
    for(int i=0;i<=n;i++)f[i]=a[i];
    for(int i=0;i<=m;i++)g[i]=b[i];
    for(int i=0;i<k;i++)to[i]=(to[i>>1]>>1)|((i&1)?(k>>1):0);
    f=ntt(f,1),g=ntt(g,1);
    for(int i=0;i<k;i++)f[i]=f[i]*g[i]%mod;
    f=ntt(f,-1);f.resize(n+m+1);
    return f;
}