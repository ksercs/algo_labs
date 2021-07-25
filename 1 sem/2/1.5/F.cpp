#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>
 
#define f_in "cond.in"
#define f_out "cond.out"
 
using namespace std;
 
//constants
const int   n_MIN = 1,
            n_MAX = 20000,
            m_MIN = 1,
            m_MAX = 200000;
 
//global
int n, m;
vector <int> graf[n_MAX + 1];
vector <int> tr_graf[n_MAX + 1];
vector <int> top_sort;
int used[n_MAX + 1];
int answer;
set < pair <int, int> > answer_edges;
 
void add_vertex(int a, int b) {
    graf[a].push_back(b);
    tr_graf[b].push_back(a);
}
 
void in() {
    freopen(f_in, "r", stdin);
    scanf("%d %d\n", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d\n", &a, &b);
        add_vertex(a, b);
    }
}
 
void used_reset() {
    for (int i = 1; i <= n; i++) {
        used[i] = 0;
    }
}
 
void dfs1(int v) {
    used[v] = true;
    for (int i = 0; i < graf[v].size(); i++) {
        if (!used[ graf[v][i] ]) {
            dfs1( graf[v][i] );
        }
    }
    top_sort.push_back(v);
}
 
void dfs2(int v) {
    used[v] = answer;
    for (int i = 0; i < tr_graf[v].size(); i++) {
        if ( !used[ tr_graf[v][i] ] ) {
            dfs2( tr_graf[v][i] );
        }
    }
}
 
void solution() {
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs1(i);
        }
    }
    reverse(top_sort.begin(), top_sort.end());
    used_reset();
    for (int i = 0; i < n; i++) {
        if (!used[ top_sort[i] ]) {
            answer++;
            dfs2( top_sort[i] );
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < graf[i].size(); j++) {
            if (used[i] != used[ graf[i][j] ] ) {
                answer_edges.insert( make_pair(used[i], used[graf[i][j]]) );
            }
        }
    }
}
 
void out() {
    freopen(f_out, "w", stdout);
    printf("%d %d\n", answer, (int)answer_edges.size());
}
 
int main() {
    in();
    solution();
    out();
    return 0;
}