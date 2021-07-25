#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = (int)1e6;

int n;
int num[MAXN];

void SiftDown (int v, int board)
{
    int MaxChild = 0,
        fl = 0;
    int L = 2*v+1, R = 2*v+2;
    while (L <= board && !fl){
        if (L == board)
            MaxChild = board;
        else
            if (num[L] > num[R])
                    MaxChild = L;
            else
                    MaxChild = R;
        if (num[v] < num[MaxChild]){
            swap(num[v], num[MaxChild]);
            v = MaxChild;
            L = 2*v+1, R = 2*v+2;
        }
        else    fl = 1;
    }
}

void HeapSort ()
{
    int LastLeave = n/2-1;
    for (int i = LastLeave; i >= 0; --i)
        SiftDown(i, n-1);
    for (int i = n - 1; i >= 1; i--) {
      swap(num[i], num[0]);
      SiftDown(0, i-1);
    }
}

void in()
{
    ifstream cin("sort.in");
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> num[i];
}

void solution()
{
    HeapSort();
}

void out()
{
    ofstream cout("sort.out");
    for (int i = 0; i < n-1; ++i)
        cout << num[i] << " ";
    cout << num[n-1] << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
