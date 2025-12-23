void fwtor(int *a,int n,int fl=1){
    for(int l=2;l<=n;l<<=1){
        int k=l>>1;
        for(int i=0;i<n;i+=l){
            for(int j=i;j<i+k;j++)(a[j+k]+=a[j]*fl)%=mod;
        }
    }
}
void fwtand(int *a,int n,int fl=1){
    for(int l=2;l<=n;l<<=1){
        int k=l>>1;
        for(int i=0;i<n;i+=l){
            for(int j=i;j<i+k;j++)(a[j]+=a[j+k]*fl)%=mod;
        }
    }
}
void fwtxor(int *a,int n,int fl=1){
    for(int l=2;l<=n;l<<=1){
        int k=l>>1;
        for(int i=0;i<n;i+=l){
            for(int j=i;j<i+k;j++){
                int u=a[j],v=a[j+k];
                a[j]=(u+v)*fl%mod,a[j+k]=(u+mod-v)*fl%mod;
            }
        }
    }
}