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

int partition(int L, int R) {
  if (L != R)
    swap(num[L + rand() % (R - L)], num[R]);
  int x = num[R];
  int i = L-1;
  for (int j = L; j <= R; j++) {
    if (num[j] <= x)
      swap(num[++i],num[j]);
  }
  return i;
}
int kth() {
  int L = 1, R = n;
  for(;;) {
    int pos = partition(L, R);
    if (pos < k)
        L = pos + 1;
    else if (pos > k)
            R = pos - 1;
         else return num[k];
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
