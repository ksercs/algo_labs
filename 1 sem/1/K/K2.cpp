#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = (int)1e5+15;

int n, L;
int t[MAXN], v[MAXN], S[MAXN], T[MAXN];
double ans;

void in()
{
    ifstream cin("trains.in");
    cin >> L >> n;
    for (int i = 1; i <= n; ++i)
        cin >> t[i] >> v[i];
}

double Count (double x)
{
    if (x < 0) return 0;
    if (x > S[n])
        return T[n];
    int i = 0;
    double res = 0;
    while (S[i] < x && i <= n){
        ++i;
        res = T[i]-(S[i]-x)/v[i];
    }
    return res;
}

void solution()
{
    v[0] = 1;
    for (int i = 1; i <= n; ++i)
        S[i] = S[i-1] + v[i]*t[i];
    for (int i = 1; i <= n; ++i)
        T[i] = T[i-1] + t[i];

    for (int i = 0; i <= n; ++i){
        ans = max(ans, Count(S[i]+L) - T[i]);
        ans = max(ans, T[i] - Count(S[i]-L));
    }
}

void out()
{
    ofstream cout("trains.out");
    cout.precision(10);
    cout << fixed << ans << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
