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

const int MAXN = 500;

int n, head, tail, ch;
int tim[MAXN], q[MAXN], ans[MAXN];

void in()
{
    ifstream cin("saloon.in");
    cin >> n;
    for (int i = 0; i < n; ++i){
        int h, m, t;
        cin >> h >> m >> t;
        int a = h*60+m;
        //cout << a << "\n";
        while (i!=0 && a >= tim[tail]+20 && tail != head) {
            ++tail;
        }
        /*cout << tail << " " << head << "\n";
        for (int  j= tail; j < head; ++j)
            cout << q[j] << " " << tim[j] << " | ";
        cout << "\n";*/
        if (t >= head-tail){
            //q[head] = a;
            if (head-1 < 0)
                tim[head] = a;
            else
                if (tim[head-1]+20 > a)
                    tim[head] = tim[head-1]+20;
                else
                    tim[head] = a;
            //cout << i << " : "<< tim[head-1] << "\n";
            ans[i] = tim[head]+20;
            ++head;
        }
        else{
            ans[i] = a;
        }
    }
}

void out()
{
    ofstream cout("saloon.out");
    for (int i = 0; i < n; ++i){
        cout << ans[i]/60 << " " << ans[i]%60 << "\n";
    }
}

int main()
{
    in();
    out();
    return 0;
}
