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

const int MAXN = 3*(int)1e7 + 15;

int n, k, a, b, c;
int num[MAXN];

int kth() {
    int L = 1, R = n;
	while (1)
	{
	    for (int i = 1; i <= n; ++i) {
            cout << num[i] << " ";
	    }
        cout << "\n";
		if (R <= L+1)
		{
			if (R == L+1 && num[R] < num[L])
				swap (num[L], num[R]);
			return num[k];
		}

		int mid = (L + R) >> 1;
		swap (num[mid], num[L+1]);
		if (num[L] > num[R])
			swap (num[L], num[R]);
		if (num[L+1] > num[R])
			swap (num[L+1], num[R]);
		if (num[L] > num[L+1])
			swap (num[L], num[L+1]);

		int i = L+1,
			j = R;
		int cur = num[L+1];
		while (1)
		{
			while (num[++i] < cur) ;
			while (num[--j] > cur) ;
			if (i > j)
				break;
			swap (num[i], num[j]);
		}
		num[L+1] = num[j];
		num[j] = cur;

		if (j >= k)
			R = j-1;
		if (j <= k)
			L = i;

	}
}

void in()
{
    ifstream cin("kth.in");
    ios_base:: sync_with_stdio(false);
    cin >> n >> k;
    cin >> a >> b >> c >> num[1] >> num[2];
}

void solution()
{
    for (int i = 3; i <= n; ++i){
        num[i] = a*num[i-2] + b*num[i-1] + c;
        //cout << num[i] << " ";
    }
}

void out()
{
    ofstream cout("kth.out");
    cout << kth() << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
