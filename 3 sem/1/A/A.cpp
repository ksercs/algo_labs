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

int n, m;
VEC<VEC<int>> gr;
VEC<int> ans;
int u[MAXN];
bool fl;

void DFS (int v) {
    u[v]= 1;
    for (int i = 0; i < gr[v].SZ; ++i) {
        int to = gr[v][i];
        if (!u[to]) {
            DFS (to);
        } else if (u[to] == 1){
            fl = 1;
        }
    }
    u[v] = 2;
    ans.PB(v);
}

void topological_sort() {
    for (int i = 1; i <= n; ++i) {
        if (!u[i]) {
            DFS (i);
        }
    }
    reverse (ans.begin(), ans.end());
}


void in()
{
    //ifstream cin("A.in");
    cin >> n >> m;
    gr.resize(n + 5);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        gr[a].PB(b);
    }
}

void solution()
{
    topological_sort();
    if (fl) {
        ans.clear();
        ans.PB(-1);
    }
}

void out()
{
    //ofstream cout("A.out");
    for (int i = 0; i < ans.SZ; ++i) {
        cout << ans[i] << " ";
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
