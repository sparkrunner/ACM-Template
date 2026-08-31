#include <bits/stdc++.h>

using namespace std;

template<typename T, int MAXN = 100010>
class FHQTreap {
    struct Node {
        int l, r;
        T val;
        int pri;
        int siz;
    } tr[MAXN];
    int cnt;
    int root;
    inline void push_up(int p) {
        tr[p].siz = tr[tr[p].l].siz + tr[tr[p].r].siz + 1;
    }
    inline int new_node(T val) {
        cnt++;
        tr[cnt].val = val;
        tr[cnt].pri = rand();
        tr[cnt].siz = 1;
        tr[cnt].l = tr[cnt].r = 0;
        return cnt;
    }
    void split(int p, T val, int &x, int &y) {
        if (!p) {
            x = y = 0;
            return ;
        }
        if (tr[p].val <= val) {
            x = p;
            split(tr[p].r, val, tr[p].r, y);
            push_up(x);
        } else {
            y = p;
            split(tr[p].l, val, x, tr[p].l);
            push_up(y);
        }
    }
    int merge(int x, int y) {
        
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}