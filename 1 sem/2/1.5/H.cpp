#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
 
#define f_in "points.in"
#define f_out "points.out"
 
using namespace std;
 
//constants
const int   n_MIN = 1,
            n_MAX = 20000,
            m_MIN = 1,
            m_MAX = 200000;
 
//global
int n, m;
vector <int> graf[n_MAX + 1];
set <int> answer;
bool used[n_MAX + 1];
int timer, tin[n_MAX + 1], fup[n_MAX + 1];
 
void add_edge(int a, int b) {
    graf[a].push_back(b);
    graf[b].push_back(a);
}
 
void in() {
    freopen(f_in, "r", stdin);
    scanf("%d %d\n", &n, &m);
    for (int i = 1; i <= m; i++) {
        int b, e;
        scanf("%d %d\n", &b, &e);
        add_edge(b, e);
    }
}
 
void save_cutpoint(int v) {
    answer.insert(v);
}
 
void dfs(int v, int p) {
    used[v] = true;
    tin[v] = timer;
    fup[v] = timer;
    timer++;
    int children = 0;
    for (int i = 0; i < graf[v].size(); i++) {
        if (graf[v][i] != p) {
            if (used[ graf[v][i] ]) {
                //printf("used: %d -> %d\n", v, graf[v][i]);
                fup[v] = min(fup[v], tin[ graf[v][i] ]);
            } else {
                //printf("not_used: %d -> %d\n", v, graf[v][i]);
                dfs(graf[v][i], v);
                fup[v] = min(fup[v], fup[ graf[v][i] ]);
                if (fup[ graf[v][i] ] >= tin[v] && p != -1) {
                    save_cutpoint(v);
                }
                children++;
            }
        }
    }
    if (p == -1 && children > 1) {
        save_cutpoint(v);
    }
}
 
void solution() {
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs(i, -1);
        }
    }
    /*
    for (int i = 1; i <= n; i++) {
        printf("%d. %d %d\n", i, tin[i], fup[i]);
    }
    */
}
 
void out() {
    freopen(f_out, "w", stdout);
    printf("%d\n", (int)answer.size());
    for (set<int>::iterator i = answer.begin(); i != answer.end(); i++) {
        printf("%d ", (*i));
    }
    printf("\n");
}
 
int main() {
    in();
    solution();
    out();
    return 0;
}