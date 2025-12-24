inline int det() {
	int ans = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; ++j) {
			if (a[j][i]) {
				if (j != i) {
					swap(a[j], a[i]);
					fix(ans = -ans);
				}
				break;
			}
		}
		if (!a[i][i]) return 0;
		ans = 1LL * ans * a[i][i] % mod;
		int t = qpow(a[i][i], mod - 2);
		for (int j = i; j <= n; ++j) {
			a[i][j] = 1LL * a[i][j] * t % mod;
		}
		for (int j = 1; j <= n; ++j) {
			if (i == j) continue;
			for (int k = i + 1; k <= n; ++k) {
				fix(a[j][k] -= 1LL * a[j][i] * a[i][k] % mod);
			}
		}
	}
	return ans;
}