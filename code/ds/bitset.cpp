#define ull unsigned long long
ull pw[65];
struct bs{
	vector<ull> a;
	int len,n;
	void init(int _n){
		n=_n,len=(n+63)/64;a.resize(len+1,0);
	}
	void set0(int x){a[x>>6]&=~pw[x&63];}
	void set1(int x){a[x>>6]|=pw[x&63];}
	bool operator[](int x){return (a[x>>6]>>(x&63))&1;}
	bs operator<<(int x)const{
		bs res;res.init(n);
		int y=x>>6,z=x&63;
		ull lst=0;
		for(int i=0;i+y<res.len;i++){
			res.a[i+y]=lst|(a[i]<<z);
			if(z)lst=a[i]>>(64ll-z);
		}
		return res;
	}
}f;