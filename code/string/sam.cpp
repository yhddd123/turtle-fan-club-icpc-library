struct SAM {
	int lst, tot, fa[maxn], ch[maxn][26], len[maxn];
	
	inline void init() {
		lst = tot = 1;
	}
	
	inline void insert(int k, int c) {
		int u = ++tot, p = lst;
		sz[u] = 1;
		lst = u;
		len[u] = k;
		for (; p && !ch[p][c]; p = fa[p]) {
			ch[p][c] = u;
		}
		if (!p) {
			fa[u] = 1;
			return;
		}
		int q = ch[p][c];
		if (len[q] == len[p] + 1) {
			fa[u] = q;
			return;
		}
		int nq = ++tot;
		len[nq] = len[p] + 1;
		fa[nq] = fa[q];
		memcpy(ch[nq], ch[q], sizeof(ch[q]));
		fa[u] = fa[q] = nq;
		for (; p && ch[p][c] == q; p = fa[p]) {
			ch[p][c] = nq;
		}
	}
} sam;