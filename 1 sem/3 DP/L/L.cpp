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

const int MAXST = (int)1e6, MAXN = 20;

int n, W, t, ans;
int w[MAXN], ok[MAXST], dp[MAXST], prevMask[MAXST], test[MAXST];
VEC < VEC <int> > sub;

void DP ()
{
	for(int mask = 1; mask < (1<<n); ++mask) {
		if(ok[mask]){
			prevMask[mask] = mask;
			dp[mask] = 1;
			continue;
		}

		int bits_cnt =  0;
		for (int i = 0; i < 31; ++i)
            if (mask&(1<<i))
                ++bits_cnt;
		dp[mask] = n;
		prevMask[mask] = (mask&-mask);

        int last = 0, tmp = 0;
		if((1<<(bits_cnt-1)) < t) {
			last = (mask&-mask);
			tmp = (mask^last);
			int i = -1;
			while(i) {
                if (i == -1)
                    i = 0;
				if(ok[(i|last)] && dp[tmp^i]+1 < dp[mask]) {
					dp[mask] = dp[tmp^i]+1;
					prevMask[mask] = i+last;
				}
				i = ((i-tmp)&tmp);
			}
		}
        else
            for (int i = t-1; i >= 0; --i) {
                bits_cnt = (test[i]&mask);
                if (dp[mask^bits_cnt]+1 < dp[mask]) {
                    dp[mask] = dp[mask^bits_cnt]+1;
                    prevMask[mask] = bits_cnt;
                }
            }
	}
}

void getSubsets ()
{
    for(int mask = (1<<n)-1; mask >= 0; --mask) {
		int sum  = 0, fl = 0;
		for(int i = 0; i < n; ++i){
			if(mask&(1<<i))
                sum += w[i];
                if(sum > W) {
                    fl = 1;
                    break;
                }
			}
		if (fl)
            continue;
		ok[mask] = 1;
        fl = 0;
		for(int i = 0; i < n; ++i)
			if(!(mask&(1<<i)) && ok[mask|(1<<i)]) {
                fl = 1;
                break;
			}
		if(!fl)
            test[t++] = mask;
	}
}

void getAns ()
{
    int cur = (1<<n)-1;
    while (cur) {
        VEC <int> v;
		for(int i = 0; i < n; ++i)
			if(prevMask[cur]&(1<<i))
                v.PB(i+1);
		sub.PB(v);
		cur ^= prevMask[cur];
	}
}

void in()
{
    ifstream cin("skyscraper.in");
    ios_base:: sync_with_stdio(false);
    cin >> n >> W;
    for (int i = 0; i < n; ++i)
        cin >> w[i];
}

void solution()
{
    getSubsets();
    DP();
    getAns();
    ans = dp[(1<<n)-1];
}

void out()
{
    ofstream cout("skyscraper.out");
    cout << ans << "\n";
    for (int i = 0; i < sub.SZ; ++i) {
        cout << sub[i].SZ;
        for (int j = 0; j < sub[i].SZ; ++j)
            cout << " " << sub[i][j];
        cout << "\n";
    }
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
