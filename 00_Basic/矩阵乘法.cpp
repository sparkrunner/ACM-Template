constexpr int MOD = 2009;

struct mat {
    int n;
    vector<vector<int>> v;
    mat(int n_) : n(n_), v(n_, vector<int>(n_)) {}
    mat operator*(const mat &o) {
        mat res(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    res.v[i][j] = (res.v[i][j] + 1LL * v[i][k] * o.v[k][j] % MOD) % MOD;
                }
            }
        }
        return res;
    }
};

mat power(mat a, int b) {
    mat res(a.n);
    for (int i = 0; i < a.n; i++) res.v[i][i] = 1;
    for (; b; b >>= 1, a = a * a) {
        if (b & 1) {
            res = res * a;
        }
    }
    return res;
}