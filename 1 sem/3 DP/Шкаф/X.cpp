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

const int MAXN = 100;

LL n, m, ans;
LL h[MAXN], w[MAXN], dp[MAXN];

void in()
{
    ifstream cin("A.in");
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> h[i] >> w[i];
}

void solution()
{
	for(int i = 1; i <= n; ++i){
		LL Htmp = h[i],
           Wtmp = w[i];
		dp[i] = dp[i-1]+Htmp;
		for(int k = i-1; k > 0; --k){
            Wtmp += w[k];
            if (Wtmp > m)
                break;
			Htmp = max(Htmp, h[k]);
			dp[i] = min(dp[i],dp[k-1]+Htmp);
		}
	}
	ans = dp[n];
}

void out()
{
    ofstream cout("A.out");
    cout << ans << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
