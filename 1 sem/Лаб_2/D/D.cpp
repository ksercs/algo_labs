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

const int MAXN = (int)1e6 + 15;

int n, head, h;
int st[MAXN], mini[MAXN];
VEC <int> ans;

void in()
{
    ifstream cin("stack-min.in");
    cin >> n;
    for (int i = 0; i < n; ++i){
        int t;
        cin >> t;
        if (t == 1){
            int num;
            cin >> num;
            st[head++] = num;
            if (h == 0){
                mini[h++] = num;
            }
            else{
                /*int ind = h-1;
                while (mini[ind] > num && ind >= 0){
                    --ind;
                }
                mini[ind+1] = num;*/
                if (mini[h-1] >= num){
                    mini[h++] = num;
                }
            }
        }
        if (t == 2){
            int num = st[--head];
            //cout << mini[h-1] << " " <<num << "\n";
            if (mini[h-1] == num){
                h--;
            }
        }
        if (t == 3){
            ans.PB(mini[h-1]);
        }
    }
}

void out()
{
    ofstream cout("stack-min.out");
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
