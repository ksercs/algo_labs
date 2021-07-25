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
#define PIL pair <int,LL>
#define LL long long

using namespace std;

const int MAXN = (int)1e4 + 15;
const int MAXK = 100 + 15;
const LL INF = LLONG_MAX;

int n, m, st, k;
VEC<VEC<PIL>> gr;
LL ans[MAXK][MAXN];

void in()
{
//    ifstream cin("D.in");
    cin >> n >> m >> k >> st;
    gr.resize(n + 5);
    for (int i = 0; i < m; ++i) {
        int a, b;
        LL c;
        cin >> a >> b >> c;
        gr[b].PB({a, c});
    }
}

void solution()
{
    ans[0][st] = 0;
    for (int i = 1; i <= n; ++i) {
        if (i != st) {
            ans[0][i] = INF;
        }
    }
    for (int t = 1; t <= k; ++t) {
        for (int v = 1; v <= n; ++v) {
            ans[t][v] = INF;
            for (auto u : gr[v]) {
                if (ans[t - 1][u.FF] != INF) {
                    ans[t][v] = min(ans[t][v], ans[t - 1][u.FF] + u.SS);
                }
            }
        }
    }
}

void out()
{
//    ofstream cout("D.out");
    for (int i = 1; i <= n; ++i) {
        cout << (ans[k][i] == INF ? -1 : ans[k][i]) << "\n";
    }
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
