const int maxn = (1 << 22) + 50;
const int mod = 998244353, G = 3;

inline void fix(int &x) {
	x += ((x >> 31) & mod);
}

inline int qpow(int b, int p) {
	int res = 1;
	while (p) {
		if (p & 1) {
			res = 1ULL * res * b % mod;
		}
		b = 1ULL * b * b % mod;
		p >>= 1;
	}
	return res;
}

typedef vector<int> poly;

int r[maxn];

inline void NTT(poly &a, int o) {
	int n = (int)a.size();
	for (int i = 0; i < n; ++i) {
		if (i < r[i]) {
			swap(a[i], a[r[i]]);
		}
	}
	static int pw[maxn];
	for (int k = 1; k < n; k <<= 1) {
		int wn = qpow(o ? G : qpow(G, mod - 2), (mod - 1) / (k << 1));
		pw[0] = 1;
		for (int i = 1; i < k; ++i) {
			pw[i] = 1ULL * pw[i - 1] * wn % mod;
		}
		for (int i = 0; i < n; i += (k << 1)) {
			for (int j = 0; j < k; ++j) {
				int x = a[i + j], y = 1ULL * a[i + j + k] * pw[j] % mod;
				fix(a[i + j] = x + y - mod);
				fix(a[i + j + k] = x - y);
			}
		}
	}
	if (!o) {
		int inv = qpow(n, mod - 2);
		for (int i = 0; i < n; ++i) {
			a[i] = 1ULL * a[i] * inv % mod;
		}
	}
}

inline poly operator * (poly a, poly b) {
	NTT(a, 1);
	NTT(b, 1);
	int n = (int)a.size();
	for (int i = 0; i < n; ++i) {
		a[i] = 1ULL * a[i] * b[i] % mod;
	}
	NTT(a, 0);
	return a;
}

inline poly mul(poly a, poly b) {
	int n = (int)a.size() - 1, m = (int)b.size() - 1, k = 0;
	if (min(n, m) <= 100) {
		poly res(n + m + 1);
		for (int i = 0; i <= n + m; ++i) {
			ull x = 0;
			for (int j = max(i - m, 0); j <= i && j <= n; ++j) {
				x += 1ULL * a[j] * b[i - j];
				if (!(j & 15)) {
					x %= mod;
				}
			}
			res[i] = x % mod;
		}
		return res;
	}
	while ((1 << k) <= n + m) {
		++k;
	}
	for (int i = 1; i < (1 << k); ++i) {
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (k - 1));
	}
	poly A(1 << k), B(1 << k);
	for (int i = 0; i <= n; ++i) {
		A[i] = a[i];
	}
	for (int i = 0; i <= m; ++i) {
		B[i] = b[i];
	}
	poly res = A * B;
	res.resize(n + m + 1);
	return res;
}

poly inv(poly &a, int m) {
	if (m == 1) {
		return poly(1, qpow(a[0], mod - 2));
	}
	poly b = inv(a, m >> 1), c(m), res(m);
	for (int i = 0; i < m; ++i) {
		c[i] = a[i];
		if (i < (m >> 1)) {
			res[i] = b[i] * 2 % mod;
		}
	}
	c = mul(c, mul(b, b));
	for (int i = 0; i < m; ++i) {
		fix(res[i] -= c[i]);
	}
	return res;
}

inline poly inv(poly a) {
	int n = (int)a.size() - 1;
	int t = __lg(n + 1);
	if ((1 << t) < n + 1) {
		++t;
	}
	poly b(1 << t);
	for (int i = 0; i <= n; ++i) {
		b[i] = a[i];
	}
	b = inv(b, 1 << t);
	b.resize(n + 1);
	return b;
}

inline poly der(poly a) {
	int n = (int)a.size() - 1;
	poly res(n);
	for (int i = 1; i <= n; ++i) {
		res[i - 1] = 1ULL * a[i] * i % mod;
	}
	return res;
}

inline poly itg(poly a) {
	int n = (int)a.size() - 1;
	poly res(n + 2), I(n + 2);
	I[1] = 1;
	for (int i = 2; i <= n + 1; ++i) {
		I[i] = 1ULL * (mod - mod / i) * I[mod % i] % mod;
	}
	for (int i = 1; i <= n + 1; ++i) {
		res[i] = 1ULL * a[i - 1] * I[i] % mod;
	}
	return res;
}

inline poly ln(poly a) {
	int n = (int)a.size() - 1;
	poly res = itg(mul(der(a), inv(a)));
	res.resize(n + 1);
	return res;
}

poly exp(poly &a, int m) {
	if (m == 1) {
		poly res(1, 1);
		return res;
	}
	poly b = exp(a, m >> 1);
	b.resize(m);
	poly c = ln(b), d(m);
	for (int i = 0; i < m; ++i) {
		fix(d[i] = a[i] - c[i]);
	}
	fix(d[0] += 1 - mod);
	b.resize(m >> 1);
	poly res = mul(b, d);
	res.resize(m);
	return res;
}

inline poly exp(poly a) {
	int n = (int)a.size() - 1;
	int t = __lg(n + 1);
	if ((1 << t) < n + 1) {
		++t;
	}
	poly b(1 << t);
	for (int i = 0; i <= n; ++i) {
		b[i] = a[i];
	}
	b = exp(b, 1 << t);
	b.resize(n + 1);
	return b;
}

inline poly pmod(poly a, poly b) {
	int n = (int)a.size() - 1, m = (int)b.size() - 1;
	if (n < m) {
		return a;
	}
	poly c = a, d = b;
	reverse(c.begin(), c.end());
	c.resize(n - m + 1);
	reverse(d.begin(), d.end());
	d.resize(n - m + 1);
	poly q = mul(c, inv(d));
	q.resize(n - m + 1);
	reverse(q.begin(), q.end());
	q = mul(q, b);
	poly res(m);
	for (int i = 0; i < m; ++i) {
		fix(res[i] = a[i] - q[i]);
	}
	return res;
}

inline poly multipoint(poly a, poly b) {
	int n = (int)a.size() - 1, m = (int)b.size() - 1;
	vector<poly> F(1 << (__lg(m + 1) + 2));
	auto dfs = [&](auto &self, int rt, int l, int r) -> void {
		if (l == r) {
			F[rt] = poly(2);
			fix(F[rt][0] = -b[l]);
			F[rt][1] = 1;
			return;
		}
		int mid = (l + r) >> 1;
		self(self, rt << 1, l, mid);
		self(self, rt << 1 | 1, mid + 1, r);
		F[rt] = mul(F[rt << 1], F[rt << 1 | 1]);
	};
	dfs(dfs, 1, 0, m);
	for (int i = 1; i < (int)F.size(); ++i) {
		reverse(F[i].begin(), F[i].end());
	}
	reverse(a.begin(), a.end());
	F[1].resize(n);
	poly q = mul(a, inv(F[1])), ans(m + 1);
	q.resize(n);
	auto dfs2 = [&](auto &self, int rt, int l, int r, poly A) -> void {
		if ((int)A.size() > r - l + 1) {
			A.erase(A.begin(), A.end() - (r - l + 1));
		}
		if (l == r) {
			ans[l] = (a[n] + 1ULL * A[0] * b[l]) % mod;
			return;
		}
		int mid = (l + r) >> 1;
		poly a = mul(A, F[rt << 1 | 1]);
		a.resize(A.size());
		self(self, rt << 1, l, mid, a);
		a = mul(A, F[rt << 1]);
		a.resize(A.size());
		self(self, rt << 1 | 1, mid + 1, r, a);
	};
	dfs2(dfs2, 1, 0, m, q);
	return ans;
}

inline int recur(int m, poly a, poly b) {
	int n = (int)a.size();
	if (m < n) {
		return a[m];
	}
	poly f(n + 1), g(2);
	g[1] = f[n] = 1;
	for (int i = 0; i < n; ++i) {
		fix(f[i] = -b[n - i]);
	}
	auto dfs = [&](auto &self, int k) -> poly {
		if (k < n) {
			poly res(k + 1);
			res[k] = 1;
			return res;
		}
		auto res = self(self, k >> 1);
		res = mul(res, res);
		if (k & 1) {
			res.insert(res.begin(), 0);
		}
		res = pmod(res, f);
		return res;
	};
	auto res = dfs(dfs, m);
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		fix(ans += 1ULL * a[i] * res[i] % mod - mod);
	}
	return ans;
}