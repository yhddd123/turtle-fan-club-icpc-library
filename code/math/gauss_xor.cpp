const int maxn = 5050;

int n, m, b[maxn], ans[maxn];
bitset<maxn> a[maxn];

void solve() {
	n = read();
	m = read();
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n + 1; ++j) {
			int x = read();
			if (x) {
				a[i].set(j);
			}
		}
	}
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
	for (int i = 1; i <= n; ++i) {
		pc('0' + ans[i]);
		pc(" \n"[i == n]);
	}
}