#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> ans;

int get_answer (int v, int size, int &c, int p, vector<vector<int>> &gr, vector<int> &sz) {
    int sz_now = 1;
    for (int i = 0; i < gr[v].size(); i++) {
        int to = gr[v][i];
        if (sz[to] == -1 && to != p) {
            sz_now += get_answer(to, size, c, v, gr, sz);
        }
    }
    if (c == -1 && 2*sz_now >= size || c == -1 && p == -1) {
        c = v;
    }
    return sz_now;
}

void dfs(int v, int size, int d, int c, vector<vector<int>> &gr, vector<int> &sz) {
    int cur = -1;
    get_answer(v, size, cur, -1, gr, sz);
    sz[cur] = d;
    for (int i = 0; i < gr[cur].size(); i++) {
        int to = gr[cur][i];
        if (sz[to] == -1) {
            dfs(to, size / 2, d + 1, cur, gr, sz);
        }
    }
    ans[cur] = c + 1;
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> gr(n + 5);
    vector<int> sz(n + 5, -1);
    ans.resize(n + 5);
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        gr[a - 1].push_back(b - 1);
        gr[b - 1].push_back(a - 1);
    }
    dfs(0, n, 0, -1, gr, sz);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
