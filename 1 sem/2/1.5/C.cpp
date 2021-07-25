#include <stdio.h>
#include <vector>
#include <algorithm>
 
#define f_in "topsort.in"
#define f_out "topsort.out"
 
using namespace std;
 
//structures
class Graf {
    private:
        int size;
        vector <int> *loav;
        bool *used, *cycle, have_cycle;
 
        void reset_used() {
            for (int i = 1; i <= size; i++) {
                used[i] = false;
                cycle[i] = false;
            }
            have_cycle = false;
        }
 
        void dfs(vector <int> *topsort, int v) {
            used[v] = true;
            cycle[v] = true;
            for (int i = 0; i < loav[v].size(); i++) {
                if (cycle[ loav[v][i] ]) {
                    have_cycle = true;
                }
                if ( !used[ loav[v][i] ] ) {
                    dfs(topsort, loav[v][i]);
                }
            }
            topsort->push_back(v);
            cycle[v] = false;
        }
 
 
    public:
        Graf(int size) {
            this->size = size;
            loav = new vector<int>[size + 1];
            used = new bool[size + 1];
            cycle = new bool[size + 1];
            reset_used();
        }
 
        void add_vertex(int a, int b) {
            loav[a].push_back(b);
        }
 
        vector <int> *topological_sorting() {
            vector <int> *answer = new vector <int>();
            for (int i = 1; i <= size; i++) {
                if (!used[i]) {
                    dfs(answer, i);
                }
            }
            if (have_cycle) {
                answer->clear();
                answer->push_back(-1);
            } else {
                reverse( answer->begin(), answer->end() );
            }
            return answer;
        }
};
//conastants
const int   n_MIN = 0,
            n_MAX = 100000,
            m_MIN = 0,
            m_MAX = 100000;
 
 
//global
int n, m;
Graf *graf;
vector <int> *answer;
 
void in() {
    freopen(f_in, "r", stdin);
    scanf("%d %d\n", &n, &m);
    graf = new Graf(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d\n", &a, &b);
        graf->add_vertex(a, b);
    }
}
 
void solution() {
    answer = graf->topological_sorting();
}
 
void out() {
    freopen(f_out, "w", stdout);
    for (int i = 0; i < answer->size(); i++) {
        printf("%d ", (*answer)[i]);
    }
}
 
int main() {
    in();
    solution();
    out();
    return 0;
}