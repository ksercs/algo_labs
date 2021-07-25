#include <stdio.h>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
 
#define f_in "bridges.in"
#define f_out "bridges.out"
 
using namespace std;
 
//constants
const int   n_MIN = 1,
            n_MAX = 20000,
            m_MIN = 1,
            m_MAX = 200000;
 
//global
int n, m;
vector < pair <int, int> > graf[n_MAX + 1];
set <int> answer;
bool used[n_MAX + 1];
int timer, tin[n_MAX + 1], fup[n_MAX + 1];
 
void add_edge(int a, int b, int ind) {
    graf[a].push_back( make_pair(b, ind) );
    graf[b].push_back( make_pair(a, ind) );
}
 
void in() {
    freopen(f_in, "r", stdin);
    scanf("%d %d\n", &n, &m);
    for (int i = 1; i <= m; i++) {
        int b, e;
        scanf("%d %d\n", &b, &e);
        add_edge(b, e, i);
    }
}
 
void save_bridge(pair <int, int> to_save) {
    answer.insert(to_save.second);
}
 
void dfs(int v, int p) {
    used[v] = true;
    fup[v] = timer;
    tin[v] = timer;
    timer++;
    for (int i = 0; i < graf[v].size(); i++) {
        if ( graf[v][i].first != p ) {
            if (used[graf[v][i].first]) {
                //printf("used: %d -> %d\n", v, graf[v][i].first);
                fup[v] = min(fup[v], tin[ graf[v][i].first ]);
            } else {
                //printf("not_used: %d -> %d\n", v, graf[v][i].first);
                dfs(graf[v][i].first, v);
                fup[v] = min(fup[v], fup[graf[v][i].first]);
                if (fup[graf[v][i].first] > tin[v]) {
                    save_bridge(graf[v][i]);
                }
            }
        }
    }
}
 
void solution() {
    for (int i = 1; i <= n; i++) {
        if(!used[i]) {
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