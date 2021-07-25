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
#include <unordered_map>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define LL long long

using namespace std;

const int MAXN = 3000 + 15;

int n, m, ans;
string name[MAXN];
unordered_map<string, int> name_num;
int u[MAXN];
VEC<VEC<int>> gr, r_gr;
VEC<int> ts, fr;

void DFS (int v) {
    u[v]= 1;
    for (int i = 0; i < gr[v].SZ; ++i) {
        int to = gr[v][i];
        if (!u[to]) {
            DFS (to);
        }
    }
    u[v] = 2;
    ts.PB(v);
}

void topological_sort() {
    for (int i = 0; i < n; ++i) {
        if (!u[i]) {
            DFS (i);
        }
    }
    /*for (auto it : ts) {
        cout << it << " ";
    }
    cout << "\n";*/
    reverse (ts.begin(), ts.end());
}

void DFS_2(int v) {
    //cout << " ->>> " << v << " " << ans << "\n";
    u[v] = ans;
    for (int i = 0; i < r_gr[v].SZ; ++i) {
        int to = r_gr[v][i];
        if (!u[to]) {
            DFS_2(to);
        }
    }
    //cout << " <----" << v << "\n";
}

void in()
{
    //ifstream cin("G.in");
    cin >> n >> m;
    n *= 2;
    gr.resize(n + 5);
    r_gr.resize(n + 5);
    for (int i = 0; i < n; i += 2) {
        cin >> name[i];
        name_num[name[i]] = i;
    }
    for (int i = 0; i < m; ++i) {
        string a, b, c;
        cin >> a >> b >> c;
        int n1 = name_num[a.substr(1)];
        int n2 = name_num[c.substr(1)];
        //cout << n1 << " " << n2 << "\n";
        int cf1 = 0, cf2 =0;
        if (a[0] == '-') {
            ++ cf1;
        }
        if (c[0] == '-') {
            ++ cf2;
        }
        int num1 = n1 + cf1,
            num2 = n2 + cf2;
        gr[num1].PB(num2);
        r_gr[num2].PB(num1);
        gr[num2^1].PB(num1^1);
        r_gr[num1^1].PB(num2^1);
    }
}

void solution()
{
    topological_sort();

    for (int i = 0; i <= n; ++i) {
        u[i] = 0;
    }
/*
    for (auto it : ts) {
        cout << it << " ";
    }
    cout << "\n";
*/
   for (int i = 0; i < n; ++i) {
        int v = ts[i];
        if (!u[v]) {
            ++ans;
            DFS_2(v);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (u[i] == u[i ^ 1]) {
            return;
        }
    }
    for (int i = 0; i < n; i += 2) {
        int res = ((u[i] > u[i^1]) ? i : (i^1));
        if (res % 2 == 0) {
            fr.PB(res);
        }
    }
}

void out()
{
    //ofstream cout("G.out");
    if (fr.SZ) {
        cout << fr.SZ << "\n";
        for (auto it : fr) {
            cout << name[it] << " ";
        }
        cout << "\n";
    } else {
        cout << "-1\n";
    }
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
