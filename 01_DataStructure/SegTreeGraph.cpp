#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;

/*
 * 节点编号规则（n为真实点数量）：
 * 真实点：1 ~ n
 * 入树（汇总树，子→父0权）：n+1 ~ n+4n （偏移量 n）
 * 出树（分发树，父→子0权）：5n+1 ~ 5n+4n （偏移量 5n）
 * 总节点数约 9n
 */
struct SegTreeGraph {
    int n;
    vector<vector<pair<int, ll>>> adj;

    SegTreeGraph(int _n) : n(_n) {
        adj.resize(9 * n + 10);
        build_in(1, 1, n);
        build_out(1, 1, n);
    }

    // 建入树：子节点 -> 父节点，边权0
    void build_in(int rt, int l, int r) {
        if (l == r) {
            adj[l].emplace_back(n + rt, 0); // 真实点连入树叶子
            return;
        }
        int mid = (l + r) >> 1;
        int ls = rt << 1, rs = rt << 1 | 1;
        build_in(ls, l, mid);
        build_in(rs, mid + 1, r);
        adj[n + ls].emplace_back(n + rt, 0);
        adj[n + rs].emplace_back(n + rt, 0);
    }

    // 建出树：父节点 -> 子节点，边权0
    void build_out(int rt, int l, int r) {
        if (l == r) {
            adj[5 * n + rt].emplace_back(l, 0); // 出树叶子连真实点
            return;
        }
        int mid = (l + r) >> 1;
        int ls = rt << 1, rs = rt << 1 | 1;
        build_out(ls, l, mid);
        build_out(rs, mid + 1, r);
        adj[5 * n + rt].emplace_back(5 * n + ls, 0);
        adj[5 * n + rt].emplace_back(5 * n + rs, 0);
    }

    // 单点 u 向 区间 [ql, qr] 连权值为 w 的边
    void add_point_to_range(int u, int ql, int qr, ll w, int rt = 1, int l = 1, int r = -1) {
        if (r == -1) r = n;
        if (ql <= l && r <= qr) {
            adj[u].emplace_back(5 * n + rt, w);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid) add_point_to_range(u, ql, qr, w, rt<<1, l, mid);
        if (qr > mid) add_point_to_range(u, ql, qr, w, rt<<1|1, mid+1, r);
    }

    // 区间 [ql, qr] 向 单点 v 连权值为 w 的边
    void add_range_to_point(int ql, int qr, int v, ll w, int rt = 1, int l = 1, int r = -1) {
        if (r == -1) r = n;
        if (ql <= l && r <= qr) {
            adj[n + rt].emplace_back(v, w);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid) add_range_to_point(ql, qr, v, w, rt<<1, l, mid);
        if (qr > mid) add_range_to_point(ql, qr, v, w, rt<<1|1, mid+1, r);
    }

    // 区间 [l1,r1] 向 区间 [l2,r2] 连权值为 w 的边
    void add_range_to_range(int l1, int r1, int l2, int r2, ll w) {
        vector<int> from_nodes;
        // 收集左区间对应的入树节点
        function<void(int, int, int)> get_in = [&](int rt, int l, int r) {
            if (l1 <= l && r <= r1) {
                from_nodes.push_back(n + rt);
                return;
            }
            int mid = (l + r) >> 1;
            if (l1 <= mid) get_in(rt<<1, l, mid);
            if (r1 > mid) get_in(rt<<1|1, mid+1, r);
        };
        get_in(1, 1, n);

        // 每个入树节点向出树的右区间连边
        for (int u : from_nodes) {
            function<void(int, int, int)> link_out = [&](int rt, int l, int r) {
                if (l2 <= l && r <= r2) {
                    adj[u].emplace_back(5 * n + rt, w);
                    return;
                }
                int mid = (l + r) >> 1;
                if (l2 <= mid) link_out(rt<<1, l, mid);
                if (r2 > mid) link_out(rt<<1|1, mid+1, r);
            };
            link_out(1, 1, n);
        }
    }

    // 单源最短路 Dijkstra
    vector<ll> dijkstra(int s) {
        vector<ll> dis(9 * n + 10, INF);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        dis[s] = 0;
        pq.emplace(0, s);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dis[u]) continue;
            for (auto [v, w] : adj[u]) {
                if (dis[v] > d + w) {
                    dis[v] = d + w;
                    pq.emplace(dis[v], v);
                }
            }
        }
        return dis;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s;
    cin >> n >> m >> s;
    SegTreeGraph g(n);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int u, v;
            ll w;
            cin >> u >> v >> w;
            g.adj[u].emplace_back(v, w);
        } else if (op == 2) {
            int u, l, r;
            ll w;
            cin >> u >> l >> r >> w;
            g.add_point_to_range(u, l, r, w);
        } else {
            int u, l, r;
            ll w;
            cin >> u >> l >> r >> w;
            g.add_range_to_point(l, r, u, w);
        }
    }
    auto dis = g.dijkstra(s);
    for (int i = 1; i <= n; i++) {
        if (dis[i] == INF) cout << "-1 ";
        else cout << dis[i] << ' ';
    }
    return 0;
}