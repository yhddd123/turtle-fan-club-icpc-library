vector<int> f,g;
void cdqni(int l,int r){
    if(r-l+1<=64){
        for(int i=l;i<=r;i++){
            for(int j=l;j<i;j++)inc(g[i],1ll*g[j]*f[i-j]%mod);
            g[i]=1ll*(mod-g[i])*g[0]%mod;
        }
        return ;
    }
    if(l==r){g[l]=1ll*(mod-g[l])*g[0]%mod;return ;}
    int mid=l+r>>1;
    cdqni(l,mid);
    vector<int> ff(mid-l+1),gg(r-l+1);
    for(int i=l;i<=mid;i++)ff[i-l]=g[i];
    for(int i=0;i<=r-l;i++)gg[i]=f[i];
    ff=poly::mul(ff,gg);
    for(int i=mid+1;i<=r;i++)inc(g[i],ff[i-l]);
    cdqni(mid+1,r);
}
vector<int> ni(vector<int> a){
    int n=a.size()-1;
    f.resize(n+1),g.resize(n+1);
    for(int i=0;i<=n;i++)f[i]=a[i],g[i]=0;
    g[0]=ksm(f[0]);for(int i=1;i<=n;i++)inc(g[i],1ll*g[0]*f[i]%mod);
    cdqni(1,n);
    return g;
}
void cdqln(int l,int r){
    if(r-l+1<=64){
        for(int i=l;i<=r;i++){
            for(int j=l;j<i;j++)inc(g[i],1ll*g[j]*j%mod*f[i-j]%mod);
            g[i]=1ll*::ni[i]*(1ll*f[i]*i%mod-g[i]+mod)%mod;
        }
        return ;
    }
    if(l==r){g[l]=1ll*::ni[l]*(1ll*f[l]*l%mod-g[l]+mod)%mod;return ;}
    int mid=l+r>>1;
    cdqln(l,mid);
    vector<int> ff(mid-l+1),gg(r-l+1);
    for(int i=l;i<=mid;i++)ff[i-l]=1ll*g[i]*i%mod;
    for(int i=0;i<=r-l;i++)gg[i]=f[i];
    ff=poly::mul(ff,gg);
    for(int i=mid+1;i<=r;i++)inc(g[i],ff[i-l]);
    cdqln(mid+1,r);
}
vector<int> ln(vector<int> a){
    int n=a.size()-1;
    f.resize(n+1);g.resize(n+1);
    for(int i=0;i<=n;i++)f[i]=a[i],g[i]=0;
    f[0]=1,g[0]=0;cdqln(1,n);
    return g;
}
void cdqexp(int l,int r){
    if(r-l+1<=64){
        for(int i=l;i<=r;i++){
            for(int j=l;j<i;j++)inc(g[i],1ll*g[j]*f[i-j]%mod);
            g[i]=1ll*::ni[i]*g[i]%mod;
        }
        return ;
    }
    if(l==r){g[l]=1ll*::ni[l]*g[l]%mod;return ;}
    int mid=l+r>>1;
    cdqexp(l,mid);
    vector<int> ff(mid-l+1),gg(r-l+1);
    for(int i=l;i<=mid;i++)ff[i-l]=g[i];
    for(int i=0;i<=r-l;i++)gg[i]=f[i];
    ff=poly::mul(ff,gg);
    for(int i=mid+1;i<=r;i++)inc(g[i],ff[i-l]);
    cdqexp(mid+1,r);
}
vector<int> exp(vector<int> a){
    int n=a.size()-1;
    f.resize(n+1);g.resize(n+1);
    for(int i=0;i<=n;i++)f[i]=1l*a[i]*i%mod,g[i]=0;
    f[0]=0,g[0]=1;cdqexp(0,n);
    return g;
}