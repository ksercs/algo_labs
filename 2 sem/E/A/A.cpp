#include <bits/stdc++.h>

using namespace std;

long long a[10000005], b[10000005], c[10000005];
long long n, x, y, m, z, t, sum;

int main()
{
    int mod1 = (1<<16), mod2 = (1<<30);
    freopen ("sum0.in", "r", stdin);
    freopen ("sum0.out", "w", stdout);
    cin >> n >> x >> y >> a[0] >> m >> z >> t >> b[0];
    c[0] = a[0];
    for (int i = 1; i < n; i += 1) {
        a[i] = (a[i-1]*x + y) % mod1;
        c[i] = c[i-1] + a[i];
    }
    for (int i = 1; i < 2*m; i += 1) {
        b[i] = (b[i-1]*z + t) % mod2;
    }
    for (int i = 1; i < 2*m; i += 2) {
        b[i-1] %= n;
        b[i] %= n;
        int f = min(b[i], b[i-1]),
            s = max(b[i], b[i-1]);
        sum += c[s];
        if (f > 0)
            sum -= c[f-1];
    }
    cout << sum;
    return 0;
}
