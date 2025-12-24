const int maxn = 1000100;
const int logn = 22;
int n, m, sa[maxn], id[maxn], old[maxn << 1], h[maxn], cnt[maxn];
char s[maxn];
pii p[maxn];
struct SA {
	int f[logn][maxn], rk[maxn];
	char t[maxn];
	inline int qmin(int l, int r) {
		int k = __lg(r - l + 1);
		return min(f[k][l], f[k][r - (1 << k) + 1]);
	}
	inline int lcp(int x, int y) {
		if (x == y) {
			return n - x + 1;
		}
		if (t[x] != t[y]) {
			return 0;
		}
		if (t[x + 1] != t[y + 1]) {
			return 1;
		}
		if (t[x + 2] != t[y + 2]) {
			return 2;
		}
		x = rk[x];
		y = rk[y];
		if (x > y) {
			swap(x, y);
		}
		return qmin(x + 1, y);
	}
	inline void build() {
		int m = 127;
		for (int i = 1; i <= m; ++i) {
			cnt[i] = 0;
		}
		for (int i = 1; i <= n; ++i) {
			rk[i] = s[i];
			t[i] = s[i];
			++cnt[rk[i]];
		}
		for (int i = 1; i <= m; ++i) {
			cnt[i] += cnt[i - 1];
		}
		for (int i = n; i; --i) {
			sa[cnt[rk[i]]--] = i;
		}
		for (int w = 1;; w <<= 1) {
			int tot = 0;
			for (int i = n - w + 1; i <= n; ++i) {
				id[++tot] = i;
			}
			for (int i = 1; i <= n; ++i) {
				old[i] = rk[i];
				if (sa[i] > w) {
					id[++tot] = sa[i] - w;
				}
			}
			for (int i = 1; i <= m; ++i) {
				cnt[i] = 0;
			}
			for (int i = 1; i <= n; ++i) {
				++cnt[rk[id[i]]];
			}
			for (int i = 1; i <= m; ++i) {
				cnt[i] += cnt[i - 1];
			}
			for (int i = n; i; --i) {
				sa[cnt[rk[id[i]]]--] = id[i];
			}
			int p = 0;
			for (int i = 1; i <= n; ++i) {
				if (old[sa[i]] == old[sa[i - 1]] && old[sa[i] + w] == old[sa[i - 1] + w]) {
					rk[sa[i]] = p;
				} else {
					rk[sa[i]] = ++p;
				}
			}
			if (p == n) {
				break;
			}
			m = p;
		}
		h[1] = 0;
		for (int i = 1, k = 0; i <= n; ++i) {
			if (rk[i] == 1) {
				continue;
			}
			if (k) {
				--k;
			}
			while (i + k <= n && sa[rk[i] - 1] + k <= n && s[i + k] == s[sa[rk[i] - 1] + k]) {
				++k;
			}
			h[rk[i]] = k;
		}
		for (int i = 1; i <= n; ++i) {
			f[0][i] = h[i];
		}
		for (int j = 1; (1 << j) <= n; ++j) {
			for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
				f[j][i] = min(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
			}
		}
	}
} A, B;
inline int lcp(int x, int y) {
	return A.lcp(x, y);
}
inline int lcs(int x, int y) {
	return B.lcp(n - x + 1, n - y + 1);
}
struct node {
	int l, r, k;
	node(int a = 0, int b = 0, int c = 0) : l(a), r(b), k(c) {}
} a[maxn << 1], b[maxn << 1];
void runs() {
	n = reads(s + 1);
	A.build();
	reverse(s + 1, s + n + 1);
	B.build();
	int m = 0;
	for (int k = 1; k * 2 <= n; ++k) {
		int tot = 0;
		for (int i = k + 1; i + k - 1 <= n; i += k) {
			int l = max(i - k, i - lcs(i - 1, i + k - 1)), r = min(i - 1, i + lcp(i, i + k) - k);
			if (l <= r) {
				if (!tot) {
					p[++tot] = mkp(l, r);
				} else {
					if (p[tot].scd == l - 1) {
						p[tot].scd = r;
					} else {
						p[++tot] = mkp(l, r);
					}
				}
			}
		}
		for (int i = 1; i <= tot; ++i) {
			int l = p[i].fst, r = p[i].scd;
			a[++m] = node(l, r + k * 2 - 1, k);
		}
	}
	sort(a + 1, a + m + 1, [&](const node &a, const node &b) {
		return a.l < b.l || (a.l == b.l && (a.r < b.r || (a.r == b.r && a.k < b.k)));
	});
	int tot = 0;
	for (int i = 1; i <= m; ++i) {
		if (!tot || !(a[i].l == b[tot].l && a[i].r == b[tot].r)) {
			b[++tot] = a[i];
		}
	}
}