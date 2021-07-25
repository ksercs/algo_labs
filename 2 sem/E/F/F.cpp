#include <bits/stdc++.h>

using namespace std;

int sparse[23][100005];
int a[100005];

int main()
{
    freopen("sparse.in", "r", stdin);
    freopen("sparse.out", "w", stdout);
    int n, m, a1, u, v, answer;
    cin >> n >> m >> a1 >> u >> v;
    a[1] = a1;
    sparse[0][1] = 1;
    for (int i = 2; i <= n; i++) {
        a[i] = (23*a[i-1] + 21563) % 16714589;
        sparse[0][i] = i;
    }
    for (int i = 1; i <= log2(n); i++) {
        for (int j = 1; j+(1<<i) <= n+1; j++) {
            if (a[sparse[i-1][j]] >= a[sparse[i-1][j+(1<<(i-1))]])
                sparse[i][j] = sparse[i-1][j+(1<<(i-1))];
            else
                sparse[i][j] = sparse[i-1][j];
        }
    }
    for (int i = 1; i <= m; i++) {
        int fl = 0;
        if (u < v) {
            fl = 1;
            swap(u, v);
        }
        int g = log2(u-v+1);
        if (a[sparse[g][u-(1<<g)+1]] >= a[sparse[g][v]])
            answer = a[sparse[g][v]];
        else
            answer = a[sparse[g][u-(1<<g)+1]];
        if (fl)
            swap(v, u);
        if (i != m) {
            u = (17*u + 751 + answer + 2*i) % n + 1;
            v = (13*v + 593 + answer + 5*i) % n + 1;
        }
    }
    cout << u << " " << v << " " << answer << "\n";
    return 0;
}
