#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 70000 + 15;

int n;
int num[MAXN];

void in()
{
    ifstream cin("antiqs.in");
    cin >> n;
}

void solution()
{
    if (n == 1){
        num[0] = 1;
        return;
    }
    if (n == 2){
        num[0] = 1;
        num[1] = 2;
        return;
    }
    if (n == 3){
        num[0] = 2;
        num[1] = 1;
        num[2] = 3;
        return;
    }
    num[1] = 1;
    num[2] = 3;
    for (int i = 4; i <= n; i++)
        if ( !(i%2) )
            num[i-1] = num[i/2-1];
        else {
            num[i-1] = num[i/2];
            num[i/2] = i;
        }
    for (int i=0; i < n/2; i++)
        num[i] = i+i+2;
}

void out()
{
    ofstream cout("antiqs.out");
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
