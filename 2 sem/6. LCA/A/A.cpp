#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

int tmp = 1;

int log2(int n) {
    int res = 0;
    while (n >= 1) {
        n >>= 1;
        res++;
    }
    return res;
}

void DFS (int v, vector<vector<int>> &gr, vector<int> &tin, vector<int> &tout) {
    tin[v] = tmp++;
    for (int i = 0; i < gr[v].size(); i++) {
        int to = gr[v][i];
        DFS(to, gr, tin, tout);
    }
    tout[v] = tmp++;
}

bool comp (int a, int b, vector <int> &tin, vector <int> &tout) {
    if (tin[a] <= tin[b] && tout[a] >= tout[b])
        return 1;
    return 0;
}

int main()
{
    int n, m;
    cin >> n;
    int LOG = log2(n);
    vector<vector<int>> gr(n+1);
    vector<int> tin(n+1), tout(n+1), p(n+1);
    vector<vector<int>> dp(n + 1, vector<int>(LOG + 2));
    p[1] = 1;
    for (int i = 2; i <= n; i++) {
        int a;
        cin >> a;
        p[i] = a;
        gr[a].push_back(i);
    }

    DFS(1, gr, tin, tout);

    for (int i = 1; i <= n; i++) {
        dp[i][0] = p[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= LOG; j++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (comp(a, b, tin, tout))
            cout << a << endl;
        else if (comp(b, a, tin, tout))
            cout << b << endl;
        else {
            for (int j = LOG; j >= 0; j--) {
                if (!comp(dp[a][j], b, tin, tout))
                    a = dp[a][j];
            }
            cout << dp[a][0] << endl;
        }
    }
    return 0;
}

