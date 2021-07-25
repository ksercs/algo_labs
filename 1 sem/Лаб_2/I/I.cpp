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
#include <stack>
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

const int MAXN = (int)1e5;

int n, head;
VEC <LL> ans;
LL sum[MAXN], q[MAXN];

void in()
{
    ifstream cin("hemoglobin.in");
    cin >> n;
    for (int i = 0; i < n; ++i){
        char c;
        int a;
        cin >> c;
        if (c == '+'){
            cin >> a;
            q[head++] = a;
            if (head-2 >= 0)
                sum[head-1] = sum[head-2]+a;
            else{
                sum[head-1] = a;
            }
        }
        if (c == '-'){
            ans.PB(q[--head]);
        }
        if (c == '?'){
            cin >> a;
            if (a == 0)
                ans.PB(0);
            else{
                ans.PB(sum[head-1]- sum[head-1-a]);
            }
        }
    }
}

void out()
{
    ofstream cout("hemoglobin.out");
    for (int i = 0; i < ans.SZ; ++i){
        cout << ans[i] << "\n";
    }
}

int main()
{
    in();
    out();
    return 0;
}
