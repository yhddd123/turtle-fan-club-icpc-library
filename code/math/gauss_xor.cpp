const int maxn = 5050;
int n, m, b[maxn], ans[maxn];
bitset<maxn> a[maxn];
void solve() {
	mems(b, -1);
	for (int i = 1, r = 1; i <= n; ++i) {
		int p = -1;
		for (int j = r; j <= m; ++j) {
			if (a[j].test(i)) {
				p = j;
				break;
			}
		}
		if (p == -1) {
			continue;
		}
		if (p != r) {
			swap(a[p], a[r]);
		}
		for (int j = 1; j <= m; ++j) {
			if (j != r && a[j].test(i)) {
				a[j] ^= a[r];
			}
		}
		++r;
	}
	for (int i = 1; i <= m; ++i) {
		if (a[i].any()) {
			ans[a[i]._Find_first()] = a[i].test(n + 1);
		}
	}
}