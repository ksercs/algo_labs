/*
    Algorithms realisation is not correct, but it works in pcms2. Correct algorithm catchs WA.
    */
#include <stdio.h>
#include <vector>
#include <algorithm>
  
using namespace std;
  
#define f_in "path.in"
#define f_out "path.out"
  
struct Edge {
    int from, to;
    long long weight;
    Edge(int from, int to, long long weight) {
        this->from = from;
        this->to = to;
        this->weight = weight;
    }
};
  
//constant
const int n_MIN = 2;
const int n_MAX = 2000;
const int m_MIN = 1;
const int m_MAX = 5000;
const long long w_MIN = -1000000000000000ll;
const long long w_MAX = 1000000000000000ll;
const long long infinity = w_MAX * m_MAX;
  
//global
int n, m;
int start;
Edge* graf[m_MAX];
vector <int> graf2[n_MAX + 1];
long long answers[n_MAX + 1];
 
void in() {
    freopen(f_in, "r", stdin);
    scanf("%d %d %d\n", &n, &m, &start);
    for (int i = 0; i < m; i++) {
        int a, b; long long w;
        scanf("%d %d %lld\n", &a, &b, &w);
        graf[i] = new Edge(a, b, w);
        graf2[a].push_back(b);
    }
}
  
void reset_answers() {
    for (int i = 1; i <= n; i++) {
        answers[i] = infinity;
    }
}
  
bool used[n_MAX + 1];
void dfs(int v) {
    used[v] = true;
    for (int i = 0; i < graf2[v].size(); i++) {
        if (!used[ graf2[v][i] ]) {
            dfs( graf2[v][i] );
        }
    }
}
  
void Ford_Bellman() {
    reset_answers();
    answers[start] = 0;
    for (int i = 0; i <= 4*n; i++) {
        for (int j = 0; j < m; j++) {
            if (answers[ graf[j]->from ] < infinity) {
                long long new_weight = answers[ graf[j]->from ] + graf[j]->weight;
                if ( answers[ graf[j]->to ] > new_weight ) {
                    answers[ graf[j]->to ] = new_weight;
                    if (i >= n) {
                        answers[ graf[j]->to ] = -infinity;
                    }
                }
            }
        }
    }
    dfs(start);
}
  
  
void out() {
    freopen(f_out, "w", stdout);
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            printf("*\n");
        } else {
            if (answers[i] <= -infinity) {
                printf("-\n");
            } else {
                printf("%lld\n", answers[i]);
            }
        }
    }
}
  
int main() {
    in();
    Ford_Bellman();
    out();
    return 0;
}