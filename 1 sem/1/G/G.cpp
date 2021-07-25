#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>

using namespace std;

const int MAXN = int(1e6+15);

int res[4], pos[4], best, s, n;
VEC < PII > p;

void SiftDown (int v, int board)
{
    int MaxChild = 0,
        fl = 0;
    int L = 2*v+1, R = 2*v+2;
    while (L <= board && !fl){
        if (L == board)
            MaxChild = board;
        else
            if (p[L].FF > p[R].FF)
                    MaxChild = L;
            else
                    MaxChild = R;
        if (p[v].FF < p[MaxChild].FF){
            swap(p[v], p[MaxChild]);
            v = MaxChild;
            L = 2*v+1, R = 2*v+2;
        }
        else    fl = 1;
    }
}

void HeapSort ()
{
    int LastLeave = s/2-1;
    for (int i = LastLeave; i >= 0; --i)
        SiftDown(i, n-1);
    for (int i = n - 1; i >= 1; i--) {
      swap(p[i], p[0]);
      SiftDown(0, i-1);
    }
}

void in()
{
    ifstream cin("style.in");
    for (int t = 0; t < 4; ++t){
		int n, x;
		cin >> n;
		for (int i = 0; i < n; ++i){
			cin >> x;
			p.PB(MP(x, t));
		}
	 }
}

void solution()
{
    s = (int)p.SZ;
    n = s;
    HeapSort();
    //for (int i = 0; i < s;++i)
    //    cout << p[i].FF << " " << p[i].SS << "\n";
    int best = MAXN;
	for (int i = 0; i < s; ++i) {
        for (int j = 0; j < 4; ++j)
			while (pos[j] < s && (pos[j] < i || p[pos[j]].SS != j))
				pos[j] ++;
		int R = -1;
		/*cout << i << " : ";
		for (int j = 0; j < 4; ++j)
            cout << pos[j] << " ";
        cout << "\n";*/
		for (int j = 0; j < 4; ++j)
			R = max(R, pos[j]);
		if (R >= s) break;
		if (best > p[R].FF - p[i].FF){
			best = p[R].FF - p[i].FF;
			for (int j = 0; j < 4; ++j)
				res[j] = pos[j];
		}
	}
}

void out()
{
    ofstream cout("style.out");
	for (int i = 0; i < 3; ++i)
		cout << p[res[i]].FF << " ";
	cout << p[res[3]].FF << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
