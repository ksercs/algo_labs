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

const int ALPHA = 36;
const int MAX_VERTEX_CNT = 2 * (int)1e5 + 15;
const char delimeters[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')'};

int ctoi(char c) {
    if (c >= 'a' && c <= 'z') {
        return (int)c - (int)'a';
    }
    for (int i = 0; i < 10; ++i) {
        if (delimeters[i] == c) {
            return 25 + i + 1;
        }
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

    int getLen() const {
        return ansLen;
    }

private:
    int sz;
    int ansLen = 0;
    int link;
    array<int, ALPHA> to;
    int p = -1;
};

class Suffix_automat {
public :
    Suffix_automat() : last_vertex(0) {
        states.PB(Vertex(0, -1));
    }

    Vertex & operator [](size_t index) {
        return states[index];
    }

    void updateLongest(int cur, int p, char c) {
        if (states[p].ansLen + 1 > states[cur].ansLen) {
            states[cur].p = p;
            states[cur].ansLen = states[p].ansLen + 1;
        }
    }

    Suffix_automat & operator +=(char c) {
        int next = ctoi(c);
        int cur_vertex = states.SZ;
        states.PB(Vertex(states[last_vertex].sz + 1));

        int p = last_vertex;
        for (; p != -1 && !states[p][next]; p = states[p].link) {
            states[p][next] = cur_vertex;
            updateLongest(cur_vertex, p, c);
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
                    updateLongest(ind, p, c);
                }
                states[q].link = states[cur_vertex].link = ind;
            }
        }
        last_vertex = cur_vertex;
        cout << states.size() << "\n";
        return *this;
    }

    size_t size() const {
        return states.SZ;
    }

    string getLongest(int i) {
        string res = "";
        if (i != 0) {
            int prev = states[i].p;
            res += getLongest(prev);
            for (int j = 0; j < 26; ++j) {
                if (states[prev][j] == i) {
                    res += itoc(j);
                }
            }
        }
        return res;
    }

private :
    VEC <Vertex> states;
    int last_vertex;
};

Suffix_automat aut;
int k, ansLen, ansInd;

int u[MAX_VERTEX_CNT];

int DFS(int v) {
    if (u[v]) {
        return u[v];
    }
    int st = 0;
    for (int i = 0; i < ALPHA; ++i) {
        int to = aut[v][i];
        if (to) {
            if (!isInAlpha(i)) {
                st |= (1 << (i - 26));
            } else {
                int tmp = DFS(to);
                st |= tmp;
            }
        }
    }

    if (st == (1 << k) - 1 && aut[v].getLen() > ansLen) {
        ansLen = aut[v].getLen();
        ansInd = v;
    }
    cout << v << " : " << st << "\n";
    return u[v] = st;
}

void in()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
//    ifstream cin("F.in");
    cin >> k;
    for (int i = 0; i < k; ++i) {
        string s;
        cin >> s;
        for (auto c : s) {
            aut += c;
        }
        aut += delimeters[i];
    }
}

void solution()
{
    DFS(0);
}

void out()
{
    cout.tie(0);
//    ofstream cout("F.out");
    cout << aut.getLongest(ansInd) << "\n";
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
