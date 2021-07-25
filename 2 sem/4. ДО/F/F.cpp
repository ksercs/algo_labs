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
#include <string.h>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define LL long long

using namespace std;

const int MAXN = (int)1e5 + 15;

LL n, m, u, v, res;
LL f[21][MAXN], a[MAXN];

LL getAns (int i, int j)
{
    LL k = log2(j - i + 1);
    //cout << "K : " << k << "\n";
    return a[f[k][j - (1 << k) + 1]] < a[f[k][i]] ? f[k][j - (1 << k) + 1] : f[k][i];
}

void in()
{
    ifstream cin("sparse.in");
    cin >> n >> m >> a[1];
    cin >> u >> v;
}

void solution()
{
    for (int i = 1; i <= n; ++i) {
            f[0][i] = i;
    }
    for (int i = 2; i <= n; ++i) {
        a[i] = (23 * a[i-1] + 21563) % 16714589;
        //cout << f[0][i] << " ";
    }
    for (int i = 1; (1 << i) <= n; ++i) {
        for (int j = 1;  j + (1 << i) - 1 <= n; ++j) {
            if (a[f[i - 1][j]] < a[f[i - 1][j + (1 << i - 1)]])
                f[i][j] = f[i-1][j];
			else
                f[i][j] = f[i-1][j + (1 << i - 1)];
        }
    }
    /*for (int i = 1; (1 << i) <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << f[i][j] << " ";
        }
        cout << "\n";
    }*/
    for (int g = 1; g < m; ++g) {
        res = a[getAns(min(v,u), max(v,u))];
        //cout << u << " " << v << "\n";
        u = ((17 * u + 751 + res + 2*g) % n) + 1;
        v = ((13 * v + 593 + res + 5*g) % n) + 1;
    }
    res = a[getAns(min(v,u), max(v,u))];
}

void out()
{
    ofstream cout("sparse.out");
    cout << u << " " << v << " " << res << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
