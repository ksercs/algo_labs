#include <stdio.h>
#include <vector>
 
#define f_in "game.in"
#define f_out "game.out"
 
using namespace std;
 
//constants
const int   n_MIN = 1,
            n_MAX = 1e5,
            m_MIN = 1,
            m_MAX = 1e5;
const char answers[2][20] = {"First player wins", "Second player wins"};
 
//global
int n, m, s;
vector <int> graf[n_MAX + 1];
int loser[n_MAX + 1];
int ans_ind;
 
void add_edge(int a, int b) {
    graf[a].push_back(b);
}
 
void in() {
    freopen(f_in, "r", stdin);
    scanf("%d %d %d\n", &n, &m, &s);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d\n", &a, &b);
        add_edge(a, b);
    }
}
 
int find_loser(int v) {
    if (loser[v] == 0) {
        if (graf[v].empty()) {
            loser[v] = 1;
        } else {
            for (int i = 0; i < graf[v].size(); i++) {
                int next_res = find_loser( graf[v][i] );
                if (next_res == 1) {
                    loser[v] = 2;
                    return loser[v];
                }
            }
            loser[v] = 1;
        }
    }
    return loser[v];
}
 
void solution() {
    ans_ind = find_loser(s) == 1;
    /*
    for (int i = 1; i <= n; i++) {
        printf("%d\n", loser[i]);
    }
    */
}
 
void out() {
    freopen(f_out, "w", stdout);
    printf("%s\n", answers[ans_ind]);
}
 
int main() {
    in();
    solution();
    out();
    return 0;
}