z[1] = n;
for (int i = 2, l = 0, r = 0; i <= n; ++i) {
	if (i <= r) {
		z[i] = min(z[i - l + 1], r - i + 1);
	}
	while (i + z[i] <= n && s[z[i] + 1] == s[i + z[i]]) {
		++z[i];
	}
	if (i + z[i] - 1 > r) {
		l = i;
		r = i + z[i] - 1;
	}
}