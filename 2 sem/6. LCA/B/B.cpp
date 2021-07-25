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

void DFS(int v, long long c, int h, vector<vector<pair<int, long long>>> &gr, vector<int> &tin, vector<int> &tout, vector<vector<pair<int, long long>>> &dp, vector<int> &d) {
    tin[v] = tmp++;
    d[v] = h;
    dp[v][0].second = c;
    for (int i = 0; i < gr[v].size(); i++) {
        int to = gr[v][i].first;
        DFS(to, gr[v][i].second, h + 1, gr, tin, tout, dp, d);
    }
    tout[v] = tmp++;
}

bool comp (int a, int b, vector <int> &tin, vector <int> &tout) {
    if (tin[a] <= tin[b] && tout[a] >= tout[b])
        return 1;
    return 0;
}

long long getAns(int a, int b, vector<vector<pair <int, long long>>> &dp, vector <int> &d) {
    int s = d[a] - d[b], cur = a;
    long long res = 20000000000;
    for (int i = 0; s > 0; i++) {
        if (s&1) {
            res = min(res, dp[cur][i].second);
            cur = dp[cur][i].first;
        }
        s /= 2;
    }
    return res;
}

int main()
{
    ios_base:: sync_with_stdio(false);
    ifstream cin("minonpath.in");
    ofstream cout("minonpath.out");
    int n, m;
    cin >> n;
    int LOG = log2(n);
    vector<vector<pair<int, long long>>> gr(n+1);
    vector<int> tin(n+1), tout(n+1), d(n + 1);
    vector<vector<pair <int, long long>>> dp(n + 1, vector<pair <int, long long>>(LOG + 2));
    dp[1][0].first = 1;
    for (int i = 2; i <= n; i++) {
        int a, c;
        cin >> a >> c;
        dp[i][0].first = a;
        gr[a].push_back({i, c});
    }

    DFS(1, 0, 0, gr, tin, tout, dp, d);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= LOG; j++) {
            dp[i][j].first = dp[dp[i][j - 1].first][j - 1].first;
            dp[i][j].second =  min(dp[i][j-1].second, dp[dp[i][j-1].first][j-1].second);
        }
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (comp(a, b, tin, tout))
            cout << getAns(b, a, dp, d) << endl;
        else if (comp(b, a, tin, tout))
            cout << getAns(a, b, dp, d) << endl;
        else {
            int startA = a;
            for (int j = LOG; j >= 0; j--) {
                if (!comp(dp[a][j].first, b, tin, tout))
                    a = dp[a][j].first;
            }
            cout << min(getAns(startA, dp[a][0].first, dp, d), getAns(b, dp[a][0].first, dp, d)) << endl;
        }
    }
    return 0;
}

