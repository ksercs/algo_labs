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

const int MAXN = (int)1e5+15;

int n;
VEC <int> ans;
deque <int> f, s;

void in()
{
    ifstream cin("hospital.in");
    cin >> n;
    for (int i = 0; i < n; ++i){
        char c;
        int a;
        cin >> c;
        if (c == '+'){
            cin >> a;
            f.PB(a);
        }
        if (c == '*'){
            cin >> a;
            f.push_front(a);
        }
        if (c == '-'){
            ans.PB(s.front());
            s.pop_front();
        }
        while (!f.empty() && f.SZ > s.SZ){
            s.PB(f.front());
            f.pop_front();
        }
    }
}

void out()
{
    ofstream cout("hospital.out");
    for (int i = 0; i < ans.SZ; ++i)
        cout << ans[i] << "\n";
}

int main()
{
    in();
    out();
    return 0;
}
