struct hsh_table{
	int head[maxn],tot;
	struct nd{
		int nxt;ull key;int val;
	}e[maxn];
	inline int hsh(ull u){return u%maxn;}
	inline int &operator[](ull key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return e[i].val;
		}
		e[++tot]={head[u],key,0};head[u]=tot;
		return e[tot].val;
	}
}mp;