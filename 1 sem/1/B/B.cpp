#include <iostream>
#include <fstream>
#include <vector>

#define PB push_back

using namespace std;

const int MAXN = (int)1e7;

int n, k;
int num[MAXN], p[MAXN], st[MAXN], u[MAXN];
vector <int> ans;

void SiftDown (int v, int board)
{
    int MinChild = 0,
        fl = 0;
    int L = 2*v+1, R = 2*v+2;
    while (L <= board && !fl){
        if (L == board)
            MinChild = board;
        else
            if (num[L] < num[R])
                    MinChild = L;
            else
                    MinChild = R;
        if (num[v] > num[MinChild]){
            swap(num[v], num[MinChild]);
            swap(p[st[v]], p[st[MinChild]]);
            swap(st[v], st[MinChild]);
            v = MinChild;
            L = 2*v+1, R = 2*v+2;
        }
        else    fl = 1;
    }
}

void SiftUp(int v)
{
    while (v != 0 && num[v] < num[v/2]){
        swap(num[v/2], num[v]);
        swap(p[st[v]], p[st[v/2]]);
        swap(st[v], st[v/2]);
        v /= 2;
    }
}

void in()
{
    ifstream cin("priorityqueue.in");
    string str = "";
    while (cin >> str){
        ++k;
        if (str == "push"){
            int v = 0;
            cin >> v;
            num[n++] = v;
            p[k] = n-1;
            u[k] = 1;
            st[n-1] = k;
            SiftUp(n-1);
        }
        if (str == "extract-min"){
            if (!n){
                ans.PB(-1);
                continue;
            }
            else{
                ans.PB(num[0]);
                u[st[0]] = 0;
                swap(num[0], num[n-1]);
                swap(p[st[0]], p[st[n-1]]);
                swap(st[0], st[n-1]);
                --n;
                SiftDown(0, n-1);
            }
        }
        if (str == "decrease-key"){
            int v = 0, to = 0;
            cin >> v >> to;
            --v;
            if (u[v]){
                u[v] = 0;
                //cout << num[p[v]] << "\n";
                num[v] = to;
                SiftUp(v);
            }
        }
        /*for (int i = 0; i < n; ++i)
            cout << num[i] << " ";
            cout << "\n";
        for (int i = 0; i < n; ++i)
            cout << st[i] << " ";
            cout << "\n";
        for (int i = 0; i < n; ++i)
            cout << p[st[i]] << " ";
        cout << "\n\n";*/
    }
}

void out()
{
    ofstream cout("priorityqueue.out");
    for (int i = 0; i < (int)ans.size(); ++i)
        (ans[i] == -1) ? cout << "*\n" : cout << ans[i] << "\n";
}

int main()
{
    in();
    out();
    return 0;
}
