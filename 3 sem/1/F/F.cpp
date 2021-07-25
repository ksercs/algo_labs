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

const int MAXN = (int) 1e4 + 15;

int n, m, ans_V, ans_E;
VEC<VEC<int>> gr, r_gr;
int u[MAXN];
VEC<int> ts;

void DFS (int v) {
    u[v]= 1;
    for (int i = 0; i < gr[v].SZ; ++i) {
        int to = gr[v][i];
        if (!u[to]) {
            DFS (to);
        }
    }
    ts.PB(v);
}

void topological_sort() {
    for (int i = 1; i <= n; ++i) {
        if (!u[i]) {
            DFS (i);
        }
    }
    reverse (ts.begin(), ts.end());
}

void R_DFS(int v) {
    u[v] = ans_V;
    for (int i = 0; i < r_gr[v].SZ; ++i) {
        int to = r_gr[v][i];
        if (!u[to]) {
            R_DFS(to);
        }
    }
}

void in()
{
    //ifstream cin("F.in");
    cin >> n >> m;
    gr.resize(n + 5);
    r_gr.resize(n + 5);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        gr[a].PB(b);
        r_gr[b].PB(a);
    }
}

void solution()
{
    topological_sort();

    for (int i = 1; i <= n; ++i) {
        u[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        if (!u[ts[i]]) {
            ++ans_V;
            R_DFS(ts[i]);
        }
    }

    set<PII> ed;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < gr[i].SZ; ++j) {
            int to = gr[i][j];
            if (u[i] != u[to]) {
                ed.insert({u[i], u[to]});
                ed.insert({u[to], u[i]});
            }
        }
    }
    ans_E = ed.SZ / 2;
}

void out()
{
    //ofstream cout("F.out");
    cout << ans_E << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
