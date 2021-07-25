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

const int MAXN = int(1e5) + 5;
const LL INF = LLONG_MAX;

int n, m, a, b, c;
LL ans;
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
//    ifstream cin ("F.in");
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        LL cost;
        cin >> a >> b >> cost;
        ed[a].PB({cost, b});
        ed[b].PB({cost, a});
    }
    cin >> a >> b >> c;
}

void solution(int st)
{
    for (int i = 1; i <= n; ++i) {
        u[i] = 0;
    }
    w[st] = 0;
    way.insert({0, st});
    for (int i = 1; i <= n; ++i) {
        if (i != st) {
            way.insert({INF, i});
            w[i] = INF;
        }
    }
    dijkstra(st);
}

void out()
{
    cin.tie(0);
//    ofstream cout ("F.out");
    cout << ans << "\n";
}

int main()
{
    ans = LLONG_MAX;
    in();
    solution(a);
    LL ab = w[b];
    LL ac = w[c];
//    cout << ab << " " << ac << " ";
    solution(b);
    LL bc = w[c];
//    cout << bc << "\n";
//    solution(c);
//    LL ab = w[b];
//    LL ac = w[c];
    if (ab != INF && bc != INF) {
        ans = min(ans, ab + bc);
    }
    if (ac!= INF && bc != INF) {
        ans = min(ans, ac + bc);
    }
    if (ac!= INF && ab != INF) {
        ans = min(ans, ac + ab);
    }
    if (ans == INF) {
        ans = -1;
    }
    out();
    return 0;
}

