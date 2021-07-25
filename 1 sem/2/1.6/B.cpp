#include <iostream>
#include <stdio.h>
#include <vector>
 
using namespace std;
 
//constant
const int n_MIN = 1;
const int n_MAX = 2000;
const int m_MIN = n_MIN*(n_MIN-1)/2;
const int m_MAX = n_MAX*(n_MAX-1)/2;
const long long infinity = 1000000000000000000ll;
 
//global
int n, m;
int start, finish;
vector < pair <int, long long> > graf[n_MAX + 1];
long long answers[n_MAX + 1];
char used[n_MAX + 1];
long long answer;
 
void add_vertex(int a, int b, long long p) {
    graf[a].push_back( make_pair(b, p) );
}
 
void answers_reset() {
    for (int i = 1; i <= n; i++) {
        answers[i] = infinity;
        used[i] = false;
    }
    answers[start] = 0ll;
}
 
long long Dijkstra() {
    answers_reset();
    for (int i = 1; i <= n; i++) {
        int v = 0;
        for (int j = 1; j <= n; j++) {
            if ( !used[j] && (v == 0 || answers[j] < answers[v]) ) {
                v = j;
            }
        }
        if (answers[v] == infinity) {
            break;
        }
        used[v] = true;
        for (int j = 0; j < graf[v].size(); j++) {
            long long new_p = graf[v][j].second + answers[v];
            if (new_p < answers[ graf[v][j].first ]) {
                answers[ graf[v][j].first ] = new_p;
            }
        }
    }
    return answers[finish] == infinity? -1 : answers[finish];
}
 
void in() {
    freopen("pathmgep.in", "r", stdin);
    scanf("%d %d %d\n", &n, &start, &finish);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            long long value;
            scanf("%lld", &value);
            if (value > 0 && i != j) {
                add_vertex(i, j, value);
            }
        }
    }
}
 
void solution() {
    answer = Dijkstra();
}
 
void out() {
    freopen("pathmgep.out", "w", stdout);
    printf("%lld\n", answer);
}
 
int main() {
    in();
    solution();
    out();
    return 0;
}