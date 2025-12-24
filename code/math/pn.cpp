ll n, pr[maxn / 5], tot, pw[999], ans;
bool vis[maxn];
int phi[maxn], a[maxn];
vector<ll> h[100100];
inline void init() {
	phi[1] = 1;
	for (int i = 2; i <= N; ++i) {
		if (!vis[i]) {
			pr[++tot] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= tot && i * pr[j] <= N; ++j) {
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0) {
				phi[i * pr[j]] = phi[i] * pr[j];
				break;
			}
			phi[i * pr[j]] = phi[i] * (pr[j] - 1);
		}
	}
	for (int i = 1; i <= N / 2; ++i) {
		a[i] = (a[i - 1] + phi[i * 2]) % mod;
	}
	for (int i = 1; i <= N; ++i) {
		phi[i] = (phi[i] + phi[i - 1]) % mod;
	}
}
unordered_map<ll, ll> mp, M;
ll dfs(ll n) {
	if (n <= N) return phi[n];
	if (mp.find(n) != mp.end()) return mp[n];
	ll ans = (n % mod) * ((n + 1) % mod) % mod * inv2 % mod;
	for (ll i = 2, j; i <= n; i = j + 1) {
		j = n / (n / i);
		ans = (ans - (j - i + 1) % mod * dfs(n / i) % mod) % mod;
	}
	return mp[n] = ans;
}
ll calc(ll n) {
	if (n <= N / 2) return a[n];
	if (M.find(n) != M.end()) return M[n];
	return M[n] = (dfs(n) + calc(n / 2)) % mod;
}
inline ll G(ll n) {
	return (dfs(n) + calc(n / 2) * 2 % mod) % mod;
}
void dfs(int d, ll x, ll y) {
	if (pr[d] * pr[d] > n / x) {
		ans = (ans + y * G(n / x) % mod) % mod;
		return;
	}
	int k = 0;
	while (x <= n) {
		if (k != 1) {
			dfs(d + 1, x, y * h[d][k] % mod);
		}
		x *= pr[d];
		++k;
	}
}
void solve() {
	scanf("%lld", &n);
	for (int i = 1; i <= tot && pr[i] * pr[i] <= n; ++i) {
		int cnt = 0;
		ll x = n;
		while (x) {
			++cnt;
			x /= pr[i];
		}
		pw[0] = 1;
		for (int j = 1; j <= cnt + 3; ++j) {
			pw[j] = pw[j - 1] * pr[i] % mod;
		}
		ll p = 1;
		for (int j = 0; p <= n; ++j, p *= pr[i]) {
			if (j == 0) {
				h[i].pb(1);
			} else if (j == 1) {
				h[i].pb(0);
			} else {
				ll t = pr[i] ^ j;
				for (int k = 0; k < j; ++k) {
					ll g = pw[j - k - 1] * (pr[i] - 1) % mod;
					if (pr[i] == 2) {
						g = g * 3 % mod;
					}
					t = (t - g * h[i][k] % mod + mod) % mod;
				}
				h[i].pb(t);
			}
		}
	}
	dfs(1, 1, 1);
	printf("%lld\n", ans);
}