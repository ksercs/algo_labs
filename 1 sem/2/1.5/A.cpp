#include <stdio.h>
#include <algorithm>
 
#define f_in "spantree2.in"
#define f_out "spantree2.out"
 
using namespace std;
 
//structures
class DSU {
 
    private:
        int size;
        int *storage, *rank;
 
    public:
        DSU(int size) {
            this->size = size;
            storage = new int[size + 1];
            rank = new int[size + 1];
            for (int i = 0; i <= size; i++) {
                storage[i] = i;
                rank[i] = 1;
            }
        }
 
        int get_parent(int a) {
            if (storage[a] != a) {
                storage[a] = get_parent(storage[a]);
            }
            return storage[a];
        }
 
        void merge(int a, int b) {
            a = get_parent(a);
            b = get_parent(b);
            if (a != b) {
                if (rank[a] < rank[b]) {
                    swap(a, b);
                }
                storage[a] = b;
                rank[b] += rank[a] + 1;
            }
        }
 
        bool check_group(int a, int b) {
            return get_parent(a) == get_parent(b);
        }
};
 
#define weight first
#define from second.first
#define to second.second
#define Edge pair<long long, pair<int, int> > 
 
//conastants
const int   n_MIN = 0,
            n_MAX = 20000,
            m_MIN = 0,
            m_MAX = 100000,
            w_MIN = 0,
            w_MAX = 100000;
 
 
//global
int n, m;
Edge edges[m_MAX];
DSU dsu(n_MAX);
long long answer;
 
void in() {
    freopen(f_in, "r", stdin);
    scanf("%d %d\n", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %lld", &edges[i].from, &edges[i].to, &edges[i].weight);
    }
}
 
void solution() {
    sort(edges, edges + m);
    for (int i = 0; i < m; i++) {
        if ( !dsu.check_group( edges[i].from, edges[i].to ) ) {
            dsu.merge( edges[i].from, edges[i].to );
            answer += edges[i].weight;
        }
    }
}
 
void out() {
    freopen(f_out, "w", stdout);
    printf("%lld\n", answer);
}
 
int main() {
    in();
    solution();
    out();
    return 0;
}