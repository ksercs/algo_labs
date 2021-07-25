#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
  
#define f_in "negcycle.in"
#define f_out "negcycle.out"
  
//structures
#define Edge pair < long long, pair<int, int> >
#define weight first
#define from second.first
#define to second.second
 
using namespace std;
  
//constants
const int   n_MIN = 1,
            n_MAX = 250,
            w_MIN = -1e4,
            w_MAX = 1e4,
            non_edge = 1e9;
const long long infinity = 10000000000000ll;
const char  answers[2][5] = {"NO", "YES"};
  
//global
int n;
long long graf[n_MAX + 1][n_MAX + 1], dp[n_MAX + 1][n_MAX + 1];
vector <int> answer;
long long d[n_MAX + 1];
int p[n_MAX + 1];
vector <Edge> bellman_graf;
 
void add_edge(int a, int b, long long w) {
    bellman_graf.push_back( make_pair(w, make_pair(a, b)) );
}
 
void in() {
    freopen(f_in, "r", stdin);
    scanf("%d\n", &n);
    for (int i = 1; i <=n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%lld", &graf[i][j]);
            dp[i][j] = graf[i][j];
            add_edge(i, j, graf[i][j]);
        }
    }
}
  
void Ford_Bellman(int start) {
    for (int i = 1; i <= n; i++) {
        d[i] = infinity;
        p[i] = -1;;
    }
    d[start] = 0;
    int x;
    for (int i = 0; i <= n; i++) {
        x = -1;
        for (int j = 0; j < bellman_graf.size(); j++) {
            if (d[ bellman_graf[j].from ] < infinity) {
                long long new_weight = d[ bellman_graf[j].from ] + bellman_graf[j].weight;
                if (d[ bellman_graf[j].to ] > new_weight) {
                    d[ bellman_graf[j].to ] = max(-infinity, new_weight);
                    p[ bellman_graf[j].to ] = bellman_graf[j].from;
                    x = bellman_graf[j].to;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%lld %d\n", d[i], p[i]);
    }
    if (x != -1) {
        answer.clear();
        int y = x;
        for (int i = 0; i < n; i++) {
            y = p[y];
        }
        int cur = y;
        answer.push_back(cur);
        while (cur != y || answer.size() <= 1) {
            cur = p[cur];
            answer.push_back(cur);
        }
        reverse( answer.begin(), answer.end() );
    }
}
 
void solution() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dp[i][k] != non_edge && dp[k][j] != non_edge) {
                    dp[i][j] = max( -infinity, min(dp[i][j], dp[i][k] + dp[k][j]) );
                }
            }
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dp[k][j] != non_edge && dp[j][i] != non_edge && dp[j][j] < 0) {
                    dp[k][i] = -infinity;
                }
            }
        }
    }
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%lld ", dp[i][j]);
        }
        printf("\n");
    }
    */
    for (int i = 1; i <= n; i++) {
        if (dp[i][i] < 0) {
            Ford_Bellman(i);
            if (!answer.empty()) {
                break;
            }
        }
    }
}
  
void out() {
    freopen(f_out, "w", stdout);
    printf("%s\n", answers[!answer.empty()]);
    if (!answer.empty()) {
        printf("%d\n", (int)answer.size());
        for (int i = 0; i < answer.size(); i++) {
            printf("%d ", answer[i]);
        }
        printf("\n");
    }
}
  
int main() {
    in();
    solution();
    out();
    return 0;
}