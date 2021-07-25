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

const int MAXN = (int)1e5 + 15;

int n, ans = 1;
int num[MAXN];

void in()
{
    ifstream cin("isheap.in");
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> num[i];
}

void solution()
{
    for (int i = 0; i < n; ++i){
        int to = 2*i+1;
        if (to < n)
            if (num[to] < num[i]) {
                ans = 0;
                break;
            }
        ++to;
        if (to < n)
            if (num[to] < num[i]) {
                ans = 0;
                break;
            }
    }
}

void out()
{
    ofstream cout("isheap.out");
    ans ? cout << "YES\n" : cout << "NO\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
