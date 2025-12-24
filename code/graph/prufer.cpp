void fa2prufer() {
	for (int i = 1; i < n; ++i) {
		scanf("%lld", &f[i]);
		++du[f[i]];
	}
	for (int i = 1, j = 1; i <= n - 2; ++i, ++j) {
		while (du[j]) {
			++j;
		}
		p[i] = f[j];
		while (i <= n - 2 && !--du[p[i]] && p[i] < j) {
			p[i + 1] = f[p[i]];
			++i;
		}
	}
}

void prufer2fa() {
	for (int i = 1; i <= n - 2; ++i) {
		scanf("%lld", &p[i]);
		++du[p[i]];
	}
	p[n - 1] = n;
	for (int i = 1, j = 1; i < n; ++i, ++j) {
		while (du[j]) {
			++j;
		}
		f[j] = p[i];
		while (i < n && !--du[p[i]] && p[i] < j) {
			f[p[i]] = p[i + 1];
			++i;
		}
	}
}