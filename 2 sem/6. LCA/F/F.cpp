#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, Log;
vector<vector<int>> gr, dp;
vector<bool> isKilled;
vector<int> P, d, SZ, ok, rang;

void makeSet(int v) {
    P[v] = v;
    rang[v] = 0;
}

int findSet(int v) {
    if (v == P[v])
        return v;
    return P[v] = findSet(P[v]);
}

void unionSet(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a == b)
        return;
    if (rang[a] < rang[b]) {
        swap(a, b);
    }
    P[b] = a;
    if (rang[a] == rang[b])
        ++rang[a];
}

void check(int v) {
    makeSet(v);
    for (int i = 0; i < gr[v].size(); ++i) {
        int to = gr[v][i];
        if (isKilled[to]) {
            unionSet(to, v);
        }
    }
    ok[findSet(v)] = dp[v][0];
    if (isKilled[dp[v][0]]) {
        int tmp = ok[findSet(dp[v][0])];
        unionSet(v, dp[v][0]);
        ok[findSet(v)] = tmp;
    }
}

int getAns(int v) {
    if (isKilled[v]) {
        return ok[findSet(v)];
    }
    return v;
}

int LCA(int ff, int ss) {
    if (d[ff] > d[ss]) {
        swap(ss, ff);
    }
    for (int i = Log; i >= 0; --i) {
        if (d[ss] - d[ff] >= SZ[i]) {
            ss = dp[ss][i];
        }
    }
    if (ff == ss) {
        return ff;
    }
    for (int i = Log; i >= 0; --i)
        if (dp[ff][i] != dp[ss][i] && d[dp[ff][i]] == d[dp[ss][i]]) {
            ff = dp[ff][i];
            ss = dp[ss][i];
        }
    return getAns(dp[ff][0]);
}

void insertVertex(int P, int son) {
    d[son] = d[P] + 1;
    dp[son][0] = P;
    for (int i = 1; i <= Log; ++i) {
        dp[son][i] = dp[dp[son][i - 1]][i - 1];
    }
}

void DFS(int v, int p, int s) {
    //cout << v << " " << p << " " << s << "\n";
    dp[v][0] = p;
    d[v] = s;
    for (int i = 1; i <= Log; ++i)
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    for (int i = 0; i < gr[v].size(); i++) {
        DFS(gr[v][i], v, s + 1);
    }
}

int main() {
    cin >> n;
    Log = int(log2(n) + 1);
    gr.resize(200000 + 5);
    dp.resize(200000 + 5, vector<int>(Log + 1));
    isKilled.resize(200000 + 5);
    P.resize(200000 + 5);
    d.resize(200000 + 5);
    ok.resize(200000 + 5);
    rang.resize(200000 + 5);
    for (int i = 0; i <= 200000; i++) {
        ok[i] = i;
    }
    for (int i = 0; i <= Log; i++) {
        SZ.push_back(1 << i);
    }
    DFS(0, 0, 1);
    char q;
    int tmp = 1, a, b;
    for (int i = 0; i < n; ++i) {
        cin >> q;
        if (q == '+') {
            cin >> a;
            a--;
            gr[a].push_back(tmp);
            insertVertex(a, tmp);
            tmp++;
        }
        if (q == '-') {
            cin >> a;
            a--;
            isKilled[a] = 1;
            check(a);
        }
        if (q == '?') {
            cin >> a >> b;
            a--, b--;
            cout << LCA(a, b) + 1 << "\n";
        }
    }
    return 0;
}
