for (int i = 1; i <= n; ++i) {
	s[i * 2 - 1] = '#';
	s[i * 2] = t[i];
}
s[n * 2 + 1] = '#';
int ans = 0;
for (int i = 1, mid = 0, r = 0; i <= n * 2 + 1; ++i) {
	if (i <= r) {
		f[i] = min(f[mid * 2 - i], r - i + 1);
	}
	while (i + f[i] <= n * 2 + 1 && i - f[i] >= 1 && s[i + f[i]] == s[i - f[i]]) {
		++f[i];
	}
	if (i + f[i] - 1 > r) {
		mid = i;
		r = i + f[i] - 1;
	}
	ans = max(ans, f[i] - 1);
}