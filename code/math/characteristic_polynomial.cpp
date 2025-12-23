int f[maxn][maxn];
void work(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)a[i][j]=read();
    }
    for(int i=1;i<n;i++){
        int p=-1;for(int j=i+1;j<=n;j++)if(a[j][i])p=j;
        if(p==-1)continue;
        for(int j=1;j<=n;j++)swap(a[p][j],a[i+1][j]);
        for(int j=1;j<=n;j++)swap(a[j][p],a[j][i+1]);
        for(int j=i+2;j<=n;j++){
            int val=a[j][i]*ksm(a[i+1][i])%mod;
            for(int k=1;k<=n;k++)(a[j][k]+=mod-val*a[i+1][k]%mod)%=mod;
            for(int k=1;k<=n;k++)(a[k][i+1]+=val*a[k][j])%=mod;
        }
    }
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int k=0;k<i;k++)(f[i][k+1]+=f[i-1][k])%=mod,(f[i][k]+=mod-a[i][i]*f[i-1][k]%mod)%=mod;
        for(int j=1;j<i;j++){
            int val=a[j][i];for(int k=j+1;k<=i;k++)val=val*a[k][k-1]%mod;
            for(int k=0;k<=j-1;k++)(f[i][k]+=mod-val*f[j-1][k]%mod)%=mod;
        }
    }
    for(int i=0;i<=n;i++)printf("%lld ",f[n][i]);
}