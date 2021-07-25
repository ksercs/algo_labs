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

const int MAXN = 2000 + 15;
const LL INF = LLONG_MAX;

struct edge {
    int a;
    int b;
    LL cost;

    edge() {}
    edge(int _a, int _b, LL _c) {
        a = _a;
        b = _b;
        cost = _c;
    }
};

int n, m, st;
VEC <edge> gr;
LL ans[MAXN];
int u[MAXN];

void in()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
//    ifstream cin("E.in");
    cin >> n >> m >> st;
    gr.resize(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        LL cost;
        cin >> a >> b >> cost;
        gr[i] = edge(a, b, cost);
    }
}

void solution()
{
    for (int i = 1; i <= n; ++i) {
        ans[i] = INF;
    }
    ans[st] = 0;
    for (int i = 0; i < 5 * n; ++i) {
        for (int j = 0; j < m; ++j) {
            int a = gr[j].a;
            int b = gr[j].b;
            LL cost = gr[j].cost;
            if (ans[a] < INF) {
                LL new_cost = ans[a] + cost;
                if (ans[b] > new_cost || u[a]) {
                    ans[b] = new_cost;
                    if (i >= n) {
                        u[b] = 1;
                    }
                }
            }
        }
    }
}

void out()
{
//    ofstream cout("E.out");
    for (int i = 1; i <= n; ++i) {
        if (ans[i] == INF) {
            cout << "*\n";
        } else if (u[i] == 1) {
            cout << "-\n";
        } else {
            cout << ans[i] << "\n";
        }
    }
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
