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

int n, m;
vector < vector<long long> > d;


void calc (int x = 0, int y = 0, int mask = 0, int next_mask = 0)
{
    cout << x << " " << y << " " << next_mask << "\n";
	if (x == n-1)
		return;
	if (y >= m)
		d[x+2][next_mask] += d[x][mask];
	else
	{
		int my_mask = 1 << y;
		if (mask & my_mask)
			calc (x, y+1, mask, next_mask);
		else
		{
			calc (x, y+1, mask, next_mask | my_mask);
			if (y+2 < m && ! (mask & my_mask) && ! (mask & (my_mask << 1)) && !(mask & (my_mask << 2)))
				calc (x, y+3, mask, next_mask);
		}
	}
}


int main()
{
    ifstream cin("nice.in");
    ofstream cout("nice.out");
	cin >> n >> m;

	d.resize (n+1, vector<long long> (1<<m));
	d[0][0] = 1;
	for (int x=0; x<n; ++x)
		for (int mask=0; mask<(1<<m); ++mask)
			calc (x, 0, mask, 0);

	cout << d[n][0] << "\n";

}
