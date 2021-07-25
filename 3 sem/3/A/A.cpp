#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <set>
#include <map>
#include <utility>
#include <queue>
#include <climits>
#include <string.h>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define LL uint64_t

using namespace std;

const int MAX_N = (int) 1e5 + 15;
const LL MOD = (LL)1e9 + 7;

string s;
LL st[MAX_N];
LL h[MAX_N];

LL getHash(size_t L, size_t R) {
    return ((h[R] + MOD) - (L > 0 ? h[L - 1] : 0)) % MOD;
}

int main()
{
    ifstream cin("A.in");
    ofstream cout("A.out");
    cin >> s;
    LL p = 1003;
    st[0] = 1;
    h[0] = st[0] * s[0];
    for (size_t i = 1; i < s.SZ; ++i) {
        st[i] = (st[i - 1] * p) % MOD;
        h[i] = (h[i - 1] + (st[i] * s[i]) % MOD) % MOD;
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
//        cout << getHash(a - 1, b - 1)  << "\n";
//        cout << (getHash(c - 1, d - 1)) % MOD << "\n";
        if (c - d == a - b && getHash(c - 1, d - 1) == ((getHash(a - 1, b - 1) * st[abs(c - a)]) % MOD)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
