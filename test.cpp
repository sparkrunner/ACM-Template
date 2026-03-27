#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    int case_num = 0;
    while (cin >> n && n != 0) {
        case_num++;
        map<string, int> name_to_id;
        for (int i = 0; i < n; ++i) {
            string currency;
            cin >> currency;
            name_to_id[currency] = i;
        }
        double dist[35][35] = {0.0};
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 1.0;
        }
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            string ci, cj;
            double rate;
            cin >> ci >> rate >> cj;
            int u = name_to_id[ci];
            int v = name_to_id[cj];
            dist[u][v] = rate;
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] * dist[k][j] > dist[i][j]) {
                        dist[i][j] = dist[i][k] * dist[k][j];
                    }
                }
            }
        }
        bool has_arbitrage = false;
        for (int i = 0; i < n; ++i) {
            if (dist[i][i] > 1.0) {
                has_arbitrage = true;
                break;
            }
        }
        cout << "Case " << case_num << ": " << (has_arbitrage ? "Yes" : "No") << endl;
    }

    return 0;
}