#include <iostream>
#include <fstream>

#define LL int_fast64_t

using namespace std;

const int MAXM = (int) 2*1e7 + 5, MAXN = (int)1e7 + 2, MODA = (1 << 16), MODB = (1 << 30);

LL n, m, ans;
LL a[MAXN], b[MAXM], dp[MAXN];

int main()
{
    ios_base:: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ifstream cin("sum0.in");
    ofstream cout("sum0.out");
    LL x, y, z, t;
    cin >> n >> x >> y >> a[0];
    cin >> m >> z >> t >> b[0];
    dp[0] = a[0];
    for (int i = 1; i < n; ++i) {
        a[i] = ((x * a[i-1] + y)&0xFFFF);
        dp[i] = dp[i - 1] + a[i];
    }
    int mm = 2*m;
    int m1 = mm + 3;
    for (int i = 1; i <= m1 ; ++i) {
        b[i] = ((z * b[i-1] + t)&0x3FFFFFFF);
        b[i-1] %= n;
        if (!(i%2) && b[i-1] < b[i-2])
            swap(b[i-2], b[i-1]);
    }
    for (int i = 1; i < mm; i += 2) {
        ans += dp[b[i]] - dp[b[i-1]-1];
    }
    cout << ans << "\n";
    return 0;
}
