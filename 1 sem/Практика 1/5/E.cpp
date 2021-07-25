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

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define LL long long

using namespace std;

const int MAXN = 15;

int n, m, ans;
int a[MAXN], b[MAXN], dp[MAXN];

int main()
{
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int j = 1; j <= m; ++j)
        cin >> b[j];

    int Ai = 1, Bi = 1;

    while (Ai <= n && Bi <= m){
        int cnt = 0;
        while (a[Ai] > b[Bi] && Bi <= m){
            ++cnt;
            ++Bi;
        }
        int ch = a[Ai];
        dp[Ai] = dp[Ai-1] + cnt;
        ans += dp[Ai];
        ++Ai;
        while (a[Ai] == ch && Ai <= n){
            dp[Ai] = dp[Ai-1];
            ans += dp[Ai];
            ++Ai;
        }
    }

    for (int i = Ai; i <= n; ++i){
        dp[Ai] = dp[Ai-1];
        ans += dp[Ai];
    }

    /*for (int i = 1; i <= n; ++i)
        cout << dp[i] << "\n";*/

    cout << ans << "\n";

    return 0;
}
