#include <iostream>
#include <fstream>
#include <vector>
#include <set>
 
using namespace std;
 
//constant
const int n_MIN = 2;
const int n_MAX = 30000;
const int m_MIN = 1;
const int m_MAX = 400000;
const int start = 1;
const int p_MIN = 1;
const int p_MAX = 10000;
 
//global
int n, m;
vector < pair <int, long long> > graf[n_MAX + 1];
long long answers[n_MAX + 1];
 
void add_vertex(int a, int b, long long p) {
    graf[a].push_back( make_pair(b, p) );
    graf[b].push_back( make_pair(a, p) );
}
 
void answers_reset() {
    for (int i = 1; i <= n; i++) {
        answers[i] = (long long)m_MAX * (long long)m_MAX;
    }
    answers[start] = 0ll;
}
 
void Dijkstra() {
    answers_reset();
    set < pair <long long, int> > q;
    q.insert( make_pair( answers[start], start) );
    while(!q.empty()) {
        int cur_v = q.begin()->second;
        q.erase( q.begin() );
        for (int i = 0; i < graf[cur_v].size(); i++) {
            int next_v = graf[cur_v][i].first;
            long long next_p = answers[cur_v] + graf[cur_v][i].second;
            if (next_p < answers[next_v]) {
                q.erase( make_pair( answers[next_v], next_v) );
                answers[next_v] = next_p;
                q.insert( make_pair( answers[next_v], next_v) );
            }
        }
    }
}
 
void in() {
    ifstream cin("pathbgep.in");
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; long long p;
        cin >> a >> b >> p;
        add_vertex(a, b, p);
    }
}
 
void solution() {
    Dijkstra();
}
 
void out() {
    ofstream cout("pathbgep.out");
    for (int i = 1; i <= n; i++) {
        cout << answers[i] << " ";
    }
    cout << "\n";
}
 
int main() {
    in();
    solution();
    out();
    return 0;
}