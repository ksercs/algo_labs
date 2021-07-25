#include <iostream>
#include <fstream>
#include <string>

#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define PB push_back

using namespace std;

const int MAXN = (int)1e7;

int n, k;
PII num[MAXN];

void SiftDown (int v, int board)
{
    int L, R, MinChild;
    while (true)
    {
        L = 2 * v + 1;
        R = 2 * v + 2;
        MinChild = v;
        if (L < board && num[L].FF < num[MinChild].FF)
            MinChild = L;
        if (R < board && num[R].FF < num[MinChild].FF)
            MinChild = R;
        if (MinChild == v)
            break;
        swap(num[v], num[MinChild]);
        v = MinChild;
    }
}

void SiftUp(int v)
{
    while (v > 0 && num[v].FF < num[(v-1)/2].FF){
        swap(num[(v-1)/2], num[v]);
        v = (v-1)/2;
    }
}

void push (int f, int s)
{
    num[n].FF = f;
    num[n].SS = s;
    n++;
    SiftUp(n - 1);
}
int main()
{
    ifstream cin("priorityqueue.in");
    ofstream cout("priorityqueue.out");
    string str = "";
    while (cin >> str){
        ++k;
        if (str == "push"){
            int v = 0;
            cin >> v;
            push(v, k);
        }
        if (str == "extract-min"){
            if (!n){
                cout << "*\n";
            }
            else{
                cout << num[0].FF << "\n";
                swap(num[0], num[--n]);
                SiftDown(0, n);
            }
        }
        if (str == "decrease-key"){
            int v = 0, to = 0;
            cin >> v >> to;
            for (int i = 0; i < n; ++i)
                if (num[i].SS == v){
                    num[i].FF = to;
                    SiftUp(i);
                    SiftDown(i, n);
                    break;
                }
        }

    }
    return 0;
}
