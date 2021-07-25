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

const int  MAXN = (int)1e6+15;

int n;
int dsu[MAXN], siz[MAXN], maxi[MAXN], mini[MAXN];
//VEC <VEC <int> > ans;

int get_dsu (int a)
{
    if (a == dsu[a])
        return a;
    int res = get_dsu(dsu[a]);
    dsu[a] = res;
    return res;
}

void union_set (int a, int b)
{
    int pa = get_dsu(a);
    int pb = get_dsu(b);
    if (pa == pb)
        return;
    if (siz[pa] > siz[pb]){
        swap(pa, pb);
    }
    siz[pb] += siz[pa];
    maxi[pb] = max(maxi[pb], maxi[pa]);
    mini[pb] = min(mini[pb], mini[pa]);
    dsu[pa] = dsu[pb];
}

void in()
{
    ios_base:: sync_with_stdio(false);
    ifstream cin("dsu.in");
    ofstream cout("dsu.out");
    cin >> n;
    for (int i = 1; i <= n; ++i){
        dsu[i] = i;
        siz[i] = 1;
        maxi[i] = i;
        mini[i] = i;
    }
    string s;
    while (cin >> s){
        if (s == "union"){
            int a, b;
            cin >> a >> b;
           // cout << a << " " << b << "\n";
            union_set(a, b);
            /*for (int i = 1; i <= n; ++i){
                int j = get_dsu(i);
                cout << mini[j] << " " << maxi[j] << " " << siz[j] << "\n";
            }*/
        }
        else{
            int b;
            cin >> b;
            int a = get_dsu(b);
            cout << mini[a] << " " <<maxi[a] << " " << siz[a] << "\n";
            /*VEC <int> v;
            v.PB(mini[a]);
            v.PB(maxi[a]);
            v.PB(siz[a]);
            ans.PB(v);*/
        }
    }
}

/*void out()
{
    ofstream cout("dsu.out");
    for (int i = 0; i < ans.SZ; ++i){
        for (int j = 0; j < 2; ++j){
            cout << ans[i][j] << " ";
        }
        cout << ans[i][2] << "\n";
    }
}*/

int main()
{
    in();
    //out();
    return 0;
}
