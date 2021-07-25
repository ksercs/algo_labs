#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <set>
#include <map>
#include <utility>
#include <queue>
#include <climits>
#include <string.h>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define LL long long

using namespace std;

const int ALPHA = 26;
const int MAX_VERTEX_CNT = 8 * (int)1e5 + 15;

int ctoi(char c) {
    if (c >= 'a' && c <= 'z') {
        return (int)c - (int)'a';
    }
}

char itoc(int i) {
    return (char) (i + (int)('a'));
}

bool isInAlpha(int c) {
    return c <= 25;
}

class Vertex {
public :
    Vertex() {}
    Vertex(int _sz, int _link = 0, array<int, ALPHA> arr = array<int, ALPHA>()) : sz(_sz), link(_link), to(arr) {}

    friend class Suffix_automat;

    int & operator [](size_t index) {
        return to[index];
    }

private:
    int sz;
    int link;
    array<int, ALPHA> to;
};

class Suffix_automat {
public :
    Suffix_automat() : last_vertex(0) {
        states.PB(Vertex(0, -1));
    }

    Vertex & operator [](size_t index) {
        return states[index];
    }

    Suffix_automat & operator +=(char c) {
        int next = ctoi(c);
        int cur_vertex = states.SZ;
        states.PB(Vertex(states[last_vertex].sz + 1));

        int p = last_vertex;
        for (; p != -1 && !states[p][next]; p = states[p].link) {
            states[p][next] = cur_vertex;
//            updateLongest(cur_vertex, p, c);
        }
        if (p == -1) {
            states[cur_vertex].link = 0;
        } else {
            int q = states[p][next];
            if (states[p].sz + 1 == states[q].sz) {
                states[cur_vertex].link = q;
            } else {
                states.PB(Vertex(states[p].sz + 1, states[q].link, states[q].to));
                int ind = (int)states.SZ - 1;
                for (; p != -1 && states[p][next] == q; p = states[p].link) {
                    states[p][next] = ind;
//                    updateLongest(ind, p, c);
                }
                states[q].link = states[cur_vertex].link = ind;
            }
        }
        last_vertex = cur_vertex;
        return *this;
    }

    size_t size() const {
        return states.SZ;
    }

private :
    VEC <Vertex> states;
    int last_vertex;
};

Suffix_automat aut;
int k, ansLen, ansInd;

LL u[MAX_VERTEX_CNT];

LL DFS(int v) {
    if (u[v]) {
        return u[v];
    }
    LL res = 1;
    for (int i = 0; i < ALPHA; ++i) {
        int to = aut[v][i];
        if (to) {
            res += DFS(to);
        }
    }

    return u[v] = res;
}

void in()
{
    ios_base::sync_with_stdio(false);
    ifstream cin("count.in");
    cin.tie(0);
    string s;
    cin >> s;
    for (auto c : s) {
        aut += c;
    }
}

void solution()
{
    DFS(0);
}

void out()
{
    ofstream cout("count.out");
    cout.tie(0);
    cout << u[0] - 1 << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
