void fwt(int *a,int n,int fl=1){
    for(int l=2;l<=n;l<<=1){
        int k=l>>1;
        for(int i=0;i<n;i+=l){
            for(int j=i;j<i+k;j++){
            // or
                // (a[j+k]+=a[j]*fl)%=mod;
            // and
                // (a[j]+=a[j+k]*fl)%=mod;
            // xor
                // int u=a[j],v=a[j+k];
                // a[j]=(u+v)*fl%mod,a[j+k]=(u+mod-v)*fl%mod;
        }
    }
}