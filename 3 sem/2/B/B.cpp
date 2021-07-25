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
#define PLI pair <LL,int>
#define LL long long

using namespace std;

const int MAXN = 4 * int(1e4) + 5;
const LL INF = LLONG_MAX;

int n, m, st, fn;
LL w[MAXN];
int u[MAXN];

set<PLI> way;
VEC<PLI> ed[MAXN];

void dijkstra(int v)
{
    u[v] = 1;
    way.erase(way.begin());
    for (int i = 0; i < ed[v].SZ; ++i) {
        LL cost = ed[v][i].FF;
        int to = ed[v][i].SS;
        LL tmp = w[v] + cost;
        if (!u[to] && w[to] > tmp) {
            way.erase({w[to], to});
            way.insert({tmp, to});
            w[to] = tmp;
        }
    }
    if (!way.empty()) {
        dijkstra((*way.begin()).SS);
    }
}

void in()
{
    //ifstream cin ("B.in");
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        LL cost;
        cin >> a >> b >> cost;
        ed[a].PB({cost, b});
        ed[b].PB({cost, a});
    }
}

void solution()
{
    st = 1;
    w[st] = 0;
    way.insert({0, 1});
    for (int i = 2; i <= n; ++i) {
        way.insert({INF, i});
        w[i] = INF;
    }
    dijkstra(st);
}

void out()
{
    cin.tie(0);
    //ofstream cout ("B.out");
    for (int i = 1; i <= n; ++i) {
        cout << w[i] << " ";
    }
    cout << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}

