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
#include <string.h>
#include <climits>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define LL long long

using namespace std;

const int MAXN = 10000 + 15;
LL n, k, ans;
LL c[MAXN], dp[MAXN], p[MAXN];
VEC <LL> way;

void in()
{
    ifstream cin("input.txt");
    cin >> n >> k;
    for (int i = 2; i <= n-1; ++i)
        cin >> c[i];
}

void solution()
{
    for (int i = 0; i <= n; ++i)
        dp[i] = INT_MIN;
    dp[1] = 0;
    for (int i = 1; i <= n; ++i){
        if (dp[i] == INT_MIN)
            continue;
        for (int j = i+1; j <= min(i+k,n); ++j){
            if (dp[i]+c[j] > dp[j]){
                dp[j] = dp[i]+c[j];
                p[j] = i;
            }
        }
    }

    int ind = n;
    while (ind != 0){
        ++ans;
        way.PB(ind);
        ind = p[ind];
    }
    --ans;
}

void out()
{
    ofstream cout("output.txt");
    cout << dp[n] << "\n";
    cout << ans << "\n";
    for (int i = way.SZ-1; i >= 0; --i)
        cout << way[i] << " ";
    cout << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
