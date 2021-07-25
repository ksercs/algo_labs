#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <list>
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

const int MAXN = 75000 + 15;

int n, m;
int L[MAXN], R[MAXN];
VEC <int> ans;

void in()
{
    ifstream cin("formation.in");
    cin >> n >> m;
    for (int i = 1; i <= m; ++i){
        string s;
        int a, b;
        cin >> s;
        if (s == "left"){
            cin >> a >> b;
            if (L[b] != 0){
                R[L[b]] = a;
            }
            L[a] = L[b];
            R[a] = b;
            L[b] = a;
        }
        if (s == "right"){
            cin >> a >> b;
            if (R[b] != 0){
                L[R[b]] = a;
            }
            R[a] = R[b];
            L[a] = b;
            R[b] = a;
        }
        if (s == "leave"){
            cin >> a;
            R[L[a]] = R[a];
            L[R[a]] = L[a];
        }
        if (s == "name"){
            cin >> a;
            ans.PB(L[a]);
            ans.PB(R[a]);
        }
    }
}

void out()
{
    ofstream cout("formation.out");
    for (int i = 0; i < ans.SZ; i += 2){
        cout << ans[i] << " " << ans[i+1] << "\n";
    }
}

int main()
{
    in();
    out();
    return 0;
}
