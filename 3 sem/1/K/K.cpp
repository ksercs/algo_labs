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
#include <climits>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,LL>
#define LL long long

using namespace std;

const int MAXN = 1000 + 15;
LL INF = LLONG_MAX;

int n, m;
bool have_ans = 1;
LL ans;
VEC <VEC <PII> > gr;
VEC<VEC<int>> ch;
int u[MAXN];

void DFS(int v) {
    u[v] = 1;
    for (int i = 0; i < gr[v].SZ; ++i) {
        int to = gr[v][i].FF;
        if (!u[to]) {
            DFS(to);
        }
    }
}

void check_have_MST() {
    DFS(1);

    for (int i = 1; i <= n; ++i) {
        if (!u[i]) {
            have_ans = 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        u[i] = 0;
    }
}

void local_DFS(int v, VEC<VEC<PII>> & g) {
    u[v] = 1;
    for (int i = 0; i < g[v].SZ; ++i) {
        int to = g[v][i].FF;
        if (!u[to]) {
            local_DFS(to, g);
        }
    }
}

bool check_MST(int root, VEC<VEC<PII>> &g, int n) {
    for (int i = 1; i <= n; ++i) {
        u[i] = 0;
    }

    local_DFS(root, g);

    int fl = 1;
    for (int i = 1; i <= n; ++i) {
        if (!u[i]) {
            fl = 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        u[i] = 0;
    }
    return fl;
}

void top_DFS (int v, VEC <int> & ts, VEC<VEC<PII>> & g) {
    u[v]= 1;
    for (int i = 0; i < g[v].SZ; ++i) {
        int to = g[v][i].FF;
        if (!u[to]) {
            top_DFS (to, ts, g);
        }
    }
    ts.PB(v);
}

void topological_sort(VEC <int> & ts, VEC<VEC<PII>> & g, int n) {
    for (int i = 1; i <= n; ++i) {
        if (!u[i]) {
        //    cout << "START TOP " << i << "\n";
            top_DFS(i, ts, g);
        }
    }
    reverse (ts.begin(), ts.end());
}

void R_DFS(int v, VEC<VEC<PII>> & rg, int col) {
    u[v] = col;
    for (int i = 0; i < rg[v].SZ; ++i) {
        int to = rg[v][i].FF;
        if (!u[to]) {
            R_DFS(to, rg, col);
        }
    }
}

void condensate(VEC<VEC<PII>> & g, int n, int & comp_cnt, int & root_comp, int root) {
    VEC<VEC<PII>> rg(n + 5);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < g[i].SZ; ++j) {
            int to = g[i][j].FF;
            LL w = g[i][j].SS;
            rg[to].PB({i, w});
        }
    }

    VEC<int> ts;
    topological_sort(ts, g, n);
    /*cout << "TS: ";
    for (int i = 0; i < ts.SZ; ++i) {
        cout << ts[i] << " ";
    }
    cout << "\n";
    */
    for (int i = 1; i <= n; ++i) {
        u[i] = 0;
    }

    int col = 0;
    for (int i = 0; i < ts.SZ; ++i) {
        if (!u[ts[i]]) {
            R_DFS(ts[i], rg, ++col);
        }
    }

    g.clear();
    g.resize(n + 5);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < gr[i].SZ; ++j) {
            int to = gr[i][j].FF;
            LL w = gr[i][j].SS;
            if (u[i] != u[to]) {
                g[u[i]].PB({u[to], w});
            }
        }
    }

    gr = g;
    comp_cnt = col;
    root_comp = u[root];
}

LL find_MST(int n, int root) {
    //system("PAUSE");
    //cout << "\n\n START :";
    //cout << n << " " << root << "\n";
    LL res = 0;

    VEC<LL> min_edge(n + 5, INF);
    ch.clear();
    ch.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        ch[i].resize(gr[i].SZ);
        for (int j = 0; j < gr[i].SZ; ++j) {
            LL w = gr[i][j].SS;
            int to = gr[i][j].FF;
            min_edge[to] = min(min_edge[to], w);
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (i == root || min_edge[i] == INF) {
            continue;
        }
        //cout << "M " << i << " " << min_edge[i] << "\n";
        res += min_edge[i];
    }
    //cout << "RES " << res << "\n";
    VEC<VEC<PII>> zero_edges(n + 5);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < gr[i].SZ; ++j) {
            int to = gr[i][j].FF;
            gr[i][j].SS -= min_edge[to];
            LL w = gr[i][j].SS;
            if (w == 0) {
                ch[i][j] = 1;
                //cout << "->>>>> " << i << "\n";
                zero_edges[i].PB({to, 0});
            }
        }
    }

    if (check_MST(root, zero_edges, n)) {
        return res;
    }

    int comp_cnt = 0, root_comp = 0;
    condensate(zero_edges, n, comp_cnt, root_comp, root);

    res += find_MST(comp_cnt, root_comp);
    return res;
}

void in()
{
    //ifstream cin("K.in");
    cin >> n >> m;
    gr.resize(n + 5);
    for (int i = 0; i < m; ++i) {
        int a, b;
        LL w;
        cin >> a >> b >> w;
        gr[a].PB({b, w});
    }
}

void solution()
{
    check_have_MST();
    if (!have_ans) {
        return;
    }

    ans = find_MST(n, 1);
}

void out()
{
    //ofstream cout("K.out");
    if (have_ans) {
        cout << "YES\n" << ans << "\n";
    } else {
        cout << "NO\n";
    }
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
