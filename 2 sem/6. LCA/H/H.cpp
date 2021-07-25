#include <iostream>
#include <set>
#include <vector>

using namespace std;

set<int>* dfs (int v, vector<vector<int>> &gr, vector<int> &c) {
    auto st = new set<int>;
    st->insert(c[v]);
    for (int i = 0; i < gr[v].size(); i++) {
        auto tmp = dfs(gr[v][i], gr, c);
        if (st->size() < tmp->size())
            swap(st, tmp);
		for (auto it: *tmp) {
            st->insert(it);
		}
    }
    c[v] = st->size();
    return st;
}

int main()
{
    int n, a, r;
    cin >> n;
    vector<int> c(n+1);
    vector<vector<int>> gr(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a >> c[i];
        gr[a].push_back(i);
        if (a == 0) {
            r = i;
        }
    }
    dfs(r, gr, c);
    for (int i = 1; i <= n; ++i) {
        cout << c[i] << " ";
    }
    return 0;
}
