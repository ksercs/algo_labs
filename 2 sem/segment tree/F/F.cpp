#include <vector>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

int main()
{
    FILE* in = fopen("sparse.in", "r");
    FILE* out = fopen("sparse.out", "w");
    long long n, m, a1, u, v;
    vector<long long> a;
    vector<vector <long long>> sparse;
    fscanf(in, "%lld%lld%lld", &n, &m, &a1);
    fscanf(in, "%lld%lld", &u, &v);
    a.resize(n+15);
    long long logg = (int)log2(n);
    sparse.resize(logg+2);
    a[1] = a1;
    sparse[0].resize(n+15);
    sparse[1].resize(n+15);
    sparse[0][1] = 1;
    for (long long i = 2; i <= n; i++) {
        a[i] = (23 * a[i-1] + 21563) % 16714589;
        if (i <= logg)
            sparse[i].resize(n+15);
        sparse[0][i] = i;
    }
    for (long long i = 1; i <= logg; i++) {
        for (long long j = 1; j + (long long)pow(2, i) <= n+1; j++) {
            if (a[sparse[i-1][j]] >= a[sparse[i-1][j + (long long)pow(2, i-1)]]) {
                sparse[i][j] = sparse[i-1][j + (long long)pow(2, i-1)];
            } else {
                sparse[i][j] = sparse[i-1][j];
            }
        }
    }
    /*for (long long i = 1; i <= logg; i++) {
        for (long long j = 1; j <= n; j++) {
            cout << sparse[i][j] << " " ;
        }
        cout << "\n";
    }*/
    long long ans;
    for (long long i = 1; i <= m; i++) {
        long long f = min(u, v);
        long long s = max(u, v);
        long long loggg = (long long)log2(s-f+1);
        if (a[sparse[loggg][s-(long long)pow(2, loggg)+1]] >= a[sparse[loggg][f]]) {
            ans = a[sparse[loggg][f]];
        } else {
            ans = a[sparse[loggg][s-(long long)pow(2, loggg)+1]];
        }
        if (i == m)
            break;
        u = ((17 * u + 751 + ans + 2*i) % n) + 1;
        v = ((13 * v + 593 + ans + 5*i) % n) + 1;
    }
    fprintf(out, "%lld %lld %lld\n", u, v, ans);
    return 0;
}
