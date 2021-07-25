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

const int MAXN = 1000 + 15;

int n, ans, maxi;
int gr[MAXN][MAXN], tmp[MAXN][MAXN];
int u[MAXN];

void DFS(int v) {
    u[v] = 1;
    for (int i = 1; i <= n; ++i) {
        if (tmp[v][i] && !u[i]) {
            DFS(i);
        }
    }
}

void DFS_2(int v) {
    u[v] = 1;
    for (int i = 1; i <= n; ++i) {
        if (tmp[i][v] && !u[i]) {
            DFS_2(i);
        }
    }
}

bool check(int M) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) {
                continue;
            }
            tmp[i][j] = (gr[i][j] <= M);
        }
    }

    DFS(1);
    int used = 1;
    for (int i = 1; i <= n; ++i) {
        if (!u[i]) {
            used = 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        u[i] = 0;
    }
    if (!used) {
        return 0;
    }


    DFS_2(1);
    used = 1;
    for (int i = 1; i <= n; ++i) {
        if (!u[i]) {
            used = 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        u[i] = 0;
    }
    if (!used) {
        return 0;
    }

    return 1;
}

void in()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    ifstream cin("avia.in");
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> gr[i][j];
            maxi = max(maxi, gr[i][j]);
        }
    }
}

void solution()
{
    int L = 0, R = maxi + 1;
    while (R - L > 1) {
        int M = L + (R - L) / 2;
        //cout << L << " " << R << " " << M << "\n"; system("PAUSE");
        if (check(M)) {
            R = M + 1;
            if (R == L + 2) {
                L = M;
            }
        } else {
            L = M;
        }
    }
    ans = L;
}

void out()
{
    ofstream cout("avia.out");
    cout << ans << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
