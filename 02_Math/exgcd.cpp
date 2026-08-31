#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = double;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll a, b, c, x1, x2, y1, y2;
    cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
    if (x1 > x2 || y1 > y2) {
        cout << "0\n";
        return 0;
    }
    c = -c;
    if (!a && !b) {
        if (c) {
            cout << "0\n";
            return 0;
        }
        cout << (x2 - x1 + 1) * (y2 - y1 + 1) << '\n';
        return 0;
    }
    if (a < 0 && b < 0) {
        a = -a;
        b = -b;
        c = -c;
    } else if (a < 0) {
        swap(x1, x2);
        x1 = -x1;
        x2 = -x2;
        a = -a;
    } else if (b < 0) {
        swap(y1, y2);
        y1 = -y1;
        y2 = -y2;
        b = -b;
    }
    ll x0, y0, g;
    g = exgcd(a, b, x0, y0);
    if (c % g) {
        cout << "0\n";
        return 0;
    }
    c /= g;
    x0 *= c;
    y0 *= c;
    if (!a) {
        if (y0 >= y1 && y0 <= y2) {
            cout << x2 - x1 + 1 << '\n';
        } else {
            cout << "0\n";
        }
        return 0;
    }
    if (!b) {
        if (x0 >= x1 && x0 <= x2) {
            cout << y2 - y1 + 1 << '\n';
        } else {
            cout << "0\n";
        }
        return 0;
    }
    ll A = a / g, B = b / g;
    db t1 = ceil(db(x1 - x0) / B);
    db t2 = floor(db(x2 - x0) / B);
    db t3 = ceil(db(y0 - y2) / A);
    db t4 = floor(db(y0 - y1) / A);
    db L = max({t1, t3});
    db R = min({t2, t4});
    ll l = (ll)L;
    ll r = (ll)R;
    ll ans = 0;
    if (l <= r) ans = r - l + 1;
    cout << max(0ll, ans) << '\n';
    return 0;
}