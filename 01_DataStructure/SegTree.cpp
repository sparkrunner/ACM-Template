#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> node;
    SegTree(int N) : n(N), node(N * 4 + 1, 0) {}
    void update(int l, int r, int p, int pos, int val) {
        if (l == r) {
            node[p] = max(node[p], val);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(l, mid, p * 2, pos, val);
        else update(mid + 1, r, p * 2 + 1, pos, val);
        node[p] = max(node[p * 2], node[p * 2 + 1]);
    }
    int ask(int l, int r, int p, int pos) {
        if (r <= pos) return node[p];
        int mid = (l + r) >> 1;
        if (pos <= mid) return ask(l, mid, p * 2, pos);
        return max(node[p * 2], ask(mid + 1, r, p * 2 + 1, pos));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        int K = (1 << k) - 1;

        unordered_map<int, int> pos;
        for (int i = 1; i <= n; ++i) {
            int x;
            cin >> x;
            pos[x] = i;
        }

        SegTree tr(n);
        for (int j = 0; j < m; ++j) {
            int b;
            cin >> b;
            if (pos.count(b ^ K)) {
                int p = pos[b ^ K];
                int tmp = (p > 1) ? tr.ask(1, n, 1, p - 1) : 0;
                tr.update(1, n, 1, p, tmp + 1);
            }
        }

        cout << tr.ask(1, n, 1, n) << '\n';
    }
    return 0;
}