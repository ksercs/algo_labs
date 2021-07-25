#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> gr;
vector<int> heavy, P, BigParent, d, place, h, from, u, w;

struct TREE {
    int size;
    vector<int> tree, a;

    TREE(){
        size = 0;
    }
};
vector<TREE> tr;

void addV(int i, int v) {
    place[v] = tr[i].size++;
    tr[i].a.push_back(h[v]);
}

void addToTree(int i, int v, int L, int R, int pos, int val) {
    if (L == R) {
        tr[i].tree[v] = val;
    }
    else {
        int M = (L + R) / 2;
        if (pos <= M) {
            addToTree(i, 2 * v + 1, L, M, pos, val);
        } else {
            addToTree(i, 2 * v + 2, M + 1, R, pos, val);
        }
        tr[i].tree[v] = max(tr[i].tree[2 * v + 1], tr[i].tree[2 * v + 2]);
    }
}

void addTr(int i, int v, int val) {
    addToTree(i, 0, 0, tr[i].size - 1, place[v], val);
}


void build(int i, int v, int L, int R) {
    if (L == R) {
        tr[i].tree[v] = tr[i].a[L];
    } else {
        int M = (L + R) / 2;
        build(i, 2 * v + 1, L, M);
        build(i, 2 * v + 2, M + 1, R);
        tr[i].tree[v] = max(tr[i].tree[2 * v + 1], tr[i].tree[2 * v + 2]);
    }
}

void makeTree(int i) {
    tr[i].tree.resize(4 * (tr[i].size + 1), 0);
    build(i, 0, 0, tr[i].size - 1);
}

int getFromTree(int i, int v, int L, int R, int l, int r) {
    if (L > r || l > R) {
        return 0;
    }
    if (l <= L && R <= r) {
        return tr[i].tree[v];
    }
    int M = (L + R) / 2;
    return max(getFromTree(i, 2 * v + 1, L, M, l, r),
               getFromTree(i, 2 * v + 2, M + 1, R, l, r));
}

int getTr(int i, int v, int u) {
    return getFromTree(i, 0, 0, tr[i].size - 1, place[v], place[u]);
}

void add(int v, int h) {
    addTr(from[v], v, h);
}

int getAns(int v, int u) {
    int ans = -1;
    if (d[v] > d[u]) {
        swap(u, v);
    }
    while (from[u] != from[v]) {
        if (d[BigParent[from[v]]] >= d[BigParent[from[u]]]) {
            ans = max(ans, getTr(from[v], BigParent[from[v]], v));
            v = P[BigParent[from[v]]];
        } else {
            ans = max(ans, getTr(from[u], BigParent[from[u]], u));
            u = P[BigParent[from[u]]];
        }
    }
    if (d[v] > d[u]) {
        swap(u, v);
    }
    return max(ans, getTr(from[v], v, u));
}

void DFS(int v, int p = 0, int h = 1) {
    d[v] = h;
    P[v] = p;
    u[v] = 1;
    int maxi = -1;
    for (int i = 0; i < gr[v].size(); i++) {
        int to = gr[v][i];
        if (!u[to]) {
            DFS(to, v, h + 1);
            w[v] += w[to];
            if (w[to] > maxi) {
                maxi = w[to];
                heavy[v] = to;
            }
        }
    }
}

void HLD(int v, int p = -1) {
    if (p == -1) {
        TREE tree;
        tr.push_back(tree);
        int size = (int) tr.size() - 1;
        BigParent[size] = v;
        from[v] = size;
        addV(size, v);
    } else {
        addV(p, v);
        from[v] = p;
    }
    u[v] = 1;
    for (int i = 0; i < gr[v].size(); i++) {
        int to = gr[v][i];
        if (!u[to]) {
            if (heavy[v] == to) {
                HLD(to, from[v]);
            }
            else {
                HLD(to);
            }
        }
    }
}

int main() {
    ifstream cin("mail.in");
    ofstream cout("mail.out");
    int n;
    cin >> n;
    int m;
    gr.resize(n+5);
    heavy.resize(n+5, n+5);
    P.resize(n+5, -1);
    BigParent.resize(n+5, -1);
    d.resize(n+5, -1);
    place.resize(n+5, -1);
    h.resize(n+5, -1);
    from.resize(n+5, -1);
    u.resize(n+5, 0);
    w.resize(n+5, 1);
    int a, b;
    for (int i = 0; i < n; i++) {
        cin >> a;
        h[i] = a;
    }
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        a--;
        b--;
        gr[a].push_back(b);
        gr[b].push_back(a);
    }
    DFS(0);
    u.assign(n+5, false);
    HLD(0);
    for (int i = 0; i < tr.size(); i++)
        makeTree(i);
    cin >> m;
    char c;
    for (int i = 0; i < m; ++i) {
        cin >> c;
        cin >> a >> b;
        a--;
        b--;
        if (c == '!') {
            add(a, b + 1);
        } else {
            cout << getAns(a, b) << "\n";
        }
    }
    return 0;
}
