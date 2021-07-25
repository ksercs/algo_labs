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
#define LL long long

using namespace std;

const int MAXN = 2 * (int)1e5 + 15;
const LL INF = (LL)1e9 + 15;

VEC<VEC<PII>> gr;
LL ans[MAXN];
int u[MAXN];
queue <int> q;

int n, m;

void BFS() {
    while (!q.empty()) {
        int v = q.front();
//        cout << "V : " << v << "\n";
        u[v] = 0;
        for (int i = 0; i < gr[v].SZ; ++i) {
            auto to = gr[v][i];
//            cout << "TO : " << to.FF << " " << to.SS << "\n";
            LL cost = ans[v] + ans[to.FF];
            if (cost < ans[to.SS]) {
                ans[to.SS] = cost;
                if (!u[to.SS]) {
                    q.push(to.SS);
                    u[to.SS] = 1;
                }
            }
        }
        q.pop();
    }
}

void in()
{
    ifstream cin("dwarf.in");
    cin >> n >> m;
    gr.resize(n + 5);
    for (int i = 1; i <= n; ++i) {
        cin >> ans[i];
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        gr[b].PB({c, a});
        gr[c].PB({b, a});
        if (!u[b]) {
            u[b] = 1;
            q.push(b);
        }
        if (!u[c]) {
            u[c] = 1;
            q.push(c);
        }
    }
}

void solution()
{
//    cout << "Q SZ : " << q.SZ << "\n";
    BFS();
}

void out()
{
    ofstream cout("dwarf.out");
    cout << ans[1] << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
