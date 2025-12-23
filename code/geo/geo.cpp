struct node {
	ll x, y;
	node(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}
	
	inline ll len() {
		return x * x + y * y;
	}
	
	inline ldb dis() {
		return sqrtl(x * x + y * y);
	}
	
	// 极角排序用（从 x 轴负半轴（不含）开始进行逆时针排序）
	inline int reg() {
		if (x < 0 && y < 0) {
			return 1;
		} else if (x == 0 && y < 0) {
			return 2;
		} else if (x > 0 && y < 0) {
			return 3;
		} else if (x >= 0 && y == 0) {
			return 4;
		} else if (x > 0 && y > 0) {
			return 5;
		} else if (x == 0 && y > 0) {
			return 6;
		} else if (x < 0 && y > 0) {
			return 7;
		} else {
			return 8;
		}
	}
};

typedef vector<node> conv;

inline node operator + (const node &a, const node &b) {
	return node(a.x + b.x, a.y + b.y);
}

inline node operator - (const node &a, const node &b) {
	return node(a.x - b.x, a.y - b.y);
}

inline bool operator < (const node &a, const node &b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

inline bool operator == (const node &a, const node &b) {
	return a.x == b.x && a.y == b.y;
}

inline ll operator * (const node &a, const node &b) {
	return a.x * b.y - a.y * b.x;
}

inline ll dot(const node &a, const node &b) {
	return a.x * b.x + a.y * b.y;
}

// 检查是否为凸包
inline bool checkcon(conv a) {
	int n = (int)a.size(), p = 0;
	if ((a[1] - a[0]) * (a[2] - a[0]) < 0) {
		reverse(a.begin(), a.end());
	}
	for (int i = 1; i < n; ++i) {
		if (a[i] < a[p]) {
			p = i;
		}
	}
	rotate(a.begin(), a.begin() + p, a.end());
	for (int i = 1; i <= n - 2; ++i) {
		if ((a[i] - a[0]) * (a[i + 1] - a[i]) <= 0) {
			return 0;
		}
	}
	for (int i = 0; i < n; ++i) {
		int j = (i == n - 1 ? 0 : i + 1);
		int k = (j == n - 1 ? 0 : j + 1);
		if ((a[j] - a[i]) * (a[k] - a[j]) <= 0) {
			return 0;
		}
	}
	return 1;
}

// 建凸包
inline conv makecon(conv a) {
	int n = (int)a.size();
	sort(a.begin(), a.end());
	vector<int> stk(n + 1);
	int top = 0;
	for (int i = 0; i < n; ++i) {
		while (top >= 2 && (a[stk[top]] - a[stk[top - 1]]) * (a[i] - a[stk[top - 1]]) <= 0) {
			--top;
		}
		stk[++top] = i;
	}
	conv b;
	for (int i = 1; i < top; ++i) {
		b.pb(a[stk[i]]);
	}
	top = 0;
	for (int i = n - 1; ~i; --i) {
		while (top >= 2 && (a[stk[top]] - a[stk[top - 1]]) * (a[i] - a[stk[top - 1]]) <= 0) {
			--top;
		}
		stk[++top] = i;
	}
	for (int i = 1; i < top; ++i) {
		b.pb(a[stk[i]]);
	}
	return b;
}

// 凸包直径
inline ll diam(conv a) {
	int n = (int)a.size(), j = 2;
	if (n == 2) {
		return (a[0] - a[1]).len();
	}
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		ans = max(ans, (a[i] - a[(i + 1) % n]).len());
		while ((a[(i + 1) % n] - a[i]) * (a[j] - a[(i + 1) % n]) < (a[(i + 1) % n] - a[i]) * (a[(j + 1) % n] - a[(i + 1) % n])) {
			j = (j + 1) % n;
		}
		ans = max({ans, (a[i] - a[j]).len(), (a[(i + 1) % n] - a[j]).len()});
	}
	return ans;
}

// P 到 AB 所在直线距离
inline ldb pointdis(node a, node b, node p) {
	if (dot(p - a, b - a) <= 0) {
		return (p - a).dis();
	} else if (dot(p - b, a - b) <= 0) {
		return (p - b).dis();
	} else {
		return abs((p - a) * (p - b)) / (a - b).dis();
	}
}

// P 是否在线段 AB 上
inline bool onseg(node a, node b, node p) {
	if ((p - a) * (p - b) != 0) {
		return 0;
	} else {
		return dot(p - a, p - b) <= 0;
	}
}

// 线段 AB 和线段 CD 是否相交（含端点）
inline bool seginter(node a, node b, node c, node d) {
	auto sgn = [&](ll x) -> int {
		return x > 0 ? 1 : (x < 0 ? -1 : 0);
	};
	int o1 = sgn((b - a) * (c - a)), o2 = sgn((b - a) * (d - a)), o3 = sgn((d - c) * (a - c)), o4 = sgn((d - c) * (b - c));
	return ((o1 * o2 < 0 && o3 * o4 < 0) || onseg(a, b, c) || onseg(a, b, d) || onseg(c, d, a) || onseg(c, d, b));
}

// 线段 AB 到线段 CD 距离
inline ldb segdis(node a, node b, node c, node d) {
	return seginter(a, b, c, d) ? 0 : min({pointdis(a, b, c), pointdis(a, b, d), pointdis(c, d, a), pointdis(c, d, b)});
}