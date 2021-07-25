#include <stdio.h>
 
#define f_in "pathsg.in"
#define f_out "pathsg.out"
 
using namespace std;
 
//constant
const int n_MIN = 1;
const int n_MAX = 200;
const int m_MIN = 0;
const int m_MAX = 10000;
const int p_MIN = 0;
const int p_MAX = 10000;
const long long infinity = 1000000000000000000ll;
 
//global
int n, m;
long long answers[n_MAX + 1][n_MAX + 1];
 
#define first to
#define second p
 
//functions
void add_vertex(int a, int b, long long p) {
    answers[a][b] = p;
}
 
void in() {
    freopen(f_in, "r", stdin);
    scanf("%d %d\n", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b; long long p;
        scanf("%d %d %lld\n", &a, &b, &p);
        add_vertex(a, b, p);
    }
}
 
long long min(long long a, long long b) {
    return a < b? a : b;
}
 
void Floyd() {
    for (int i = 1; i <= n; i++) {
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                answers[u][v] = min(answers[u][v], answers[u][i] + answers[i][v]);
            }
        }
    }
}
 
void out() {
    freopen(f_out, "w", stdout);
    for (int i = 1; i <= n; i++) {
        printf("%lld", answers[i][1]);
        for (int j = 2; j <= n; j++) {
            printf(" %lld", answers[i][j]);
        }
        printf("\n");
    }
}
 
void reset_answers() {
    for (int i = 1; i <= n_MAX; i++) {
        for (int j = 1; j <= n_MAX; j++) {
            answers[i][j] = i == j? 0ll : infinity;
        }
    }
}
 
int main() {
    reset_answers();
    in();
    Floyd();
    out();
    return 0;
}