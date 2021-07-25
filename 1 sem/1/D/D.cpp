#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 1000 + 15, MAXVAL = 256;

int n, m, k;
char s[MAXN][MAXN], B[MAXN][MAXN];
int C[MAXVAL];

void RadixSort()
{
     for (int i = m-1; i > m-k-1; --i){
         for (int j = 0; j < MAXVAL; ++j)
             C[j] = 0;
         for (int j = 0; j < n; ++j){
             int d = (s[j][i]-'0');
             C[d]++;
         }
         int cnt = 0;
         for (int j = 0; j < MAXVAL; ++j){
             int tmp = C[j];
             C[j] = cnt;
             cnt += tmp;
         }
         for (int j = 0; j < n; ++j){
             int d = int(s[j][i]-'0');
             for (int g = 0; g < m; ++g){
                B[C[d]][g] = s[j][g];
             }
             C[d]++;
         }
         for (int j = 0; j < n; ++j)
            for (int g = 0; g < m; ++g)
                s[j][g] = B[j][g];
     }
}

void in()
{
    ifstream cin("radixsort.in");
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> s[i][j];
}

void solution()
{
    RadixSort();
}

void out()
{
    ofstream cout("radixsort.out");
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            cout << s[i][j];
        cout  << "\n";
    }
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
