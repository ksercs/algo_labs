#include <stdio.h>
#include <vector>
#include <algorithm>
 
#define f_in "cycle.in"
#define f_out "cycle.out"
 
using namespace std;
 
//structures
class Graf {
    private:
        int size;
        vector <int> *loav;
        bool *used, *cycle;
        vector <int>* answer;
 
        void reset_used() {
            for (int i = 1; i <= size; i++) {
                cycle[i] = false;
                used[i] = false;
            }
        }
 
        void save_road(vector<int>* road) {
            answer->clear();
            answer->push_back( (*road)[ road->size() - 1 ] );
            int i = road->size() - 2;
            while ( (*road)[i] != (*road)[ road->size() - 1 ] && i >= 0 ) {
                answer->push_back( (*road)[i] );
                i--;
            }
            reverse(answer->begin(), answer->end());
        }
 
        void dfs(vector<int> *road, int v) {
            used[v] = true;
            cycle[v] = true;
            road->push_back(v);
            for (int i = 0; i < loav[v].size(); i++) {
                if (!cycle[ loav[v][i] ]) {
                    dfs(road, loav[v][i]);
                } else {
                    road->push_back(loav[v][i]);
                    save_road(road);
                    road->pop_back();
                }
            }
            cycle[v] = false;
            road->pop_back();
        }
 
 
    public:
        Graf(int size) {
            this->size = size;
            loav = new vector<int>[size + 1];
            used = new bool[size + 1];
            cycle = new bool[size + 1];
            reset_used();
            answer = new vector<int>();
        }
 
        void add_vertex(int a, int b) {
            loav[a].push_back(b);
        }
 
        vector <int> *cycle_checking() {
            vector <int> *road = new vector <int>();
            for (int i = 1; i <= size; i++) {
                if (!used[i]) {
                    dfs(road, i);
                }
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
    answer = graf->cycle_checking();
}
 
void out() {
    freopen(f_out, "w", stdout);
    if (answer->size() > 0) {
        printf("YES\n");
        for (int i = 0; i < answer->size(); i++) {
            printf("%d ", (*answer)[i]);
        }
    } else {
        printf("NO\n");
    }
}
 
int main() {
    in();
    solution();
    out();
    return 0;
}