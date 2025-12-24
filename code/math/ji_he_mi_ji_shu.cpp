void fmt(int *a,int n,int w=1){
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))(a[s]+=a[s^(1<<i)]*w)%=mod;
	}
}
int ff[maxn+1][1<<maxn],gg[maxn+1][1<<maxn],hh[1<<maxn],ni[maxn+1];
void xormul(int *a,int *b,int *c,int n){
	for(int i=0;i<=n;i++){
		for(int s=0;s<(1<<n);s++)ff[i][s]=gg[i][s]=0;
	}
	for(int s=0;s<(1<<n);s++)ff[__builtin_popcount(s)][s]=a[s];
	for(int s=0;s<(1<<n);s++)gg[__builtin_popcount(s)][s]=b[s];
	for(int i=0;i<=n;i++)fmt(ff[i],n,1);
	for(int i=0;i<=n;i++)fmt(gg[i],n,1);
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<=n;i++){
			hh[i]=0;
			for(int j=0;j<=i;j++)(hh[i]+=ff[j][s]*gg[i-j][s])%=mod;
		}
		for(int i=0;i<=n;i++)ff[i][s]=hh[i];
	}
    /*ln
            for(int i=0;i<n;i++){
                hh[i]=ff[i+1][s]*(i+1)%mod;
                for(int j=1;j<=i;j++)(hh[i]+=mod-ff[j][s]*hh[i-j]%mod)%=mod;
            }
            for(int i=1;i<=n;i++)ff[i][s]=hh[i-1]*ni[i]%mod;
    */
    /*exp
            for(int i=0;i<n;i++){
                hh[i]=ff[i+1][s]*(i+1)%mod;
                for(int j=1;j<=i;j++)(hh[i]+=ff[j][s]*j%mod*hh[i-j]%mod*ni[i-j+1])%=mod;
            }
            for(int i=1;i<=n;i++)ff[i][s]=hh[i-1]*ni[i]%mod;
    */
	for(int i=0;i<=n;i++)fmt(ff[i],n,mod-1);
	for(int s=0;s<(1<<n);s++)c[s]=ff[__builtin_popcount(s)][s];
}