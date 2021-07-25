#include <iostream>
#include <fstream>
#include <algorithm>
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

const int ALPHA = 27;
const string ANS[] = {"NO\n", "YES\n"};

int ctoi(char c) {
    return (int)c - int('a');
}

class Vertex {
public:
    Vertex(int _p = -1, char _pc = 0) : cnt(0), minLink(-1), link(-1), p(_p), pc(_pc) {
        toBor.resize(ALPHA, -1);
        toAut.resize(ALPHA, -1);
    }

    friend class AhoKorasik;

private:
    VEC <int> toBor;
    VEC <int> toAut;
    VEC <int> terms;
    int p;
    char pc;
    int link;
    int minLink;
    int cnt;
};


class AhoKorasik {
public:
    AhoKorasik() {
        bor.PB(Vertex());
    }

    AhoKorasik(VEC <string> const & stringSet) {
        bor.PB(Vertex());

        for (auto s : stringSet) {
            *this += s;
        }
    }

    AhoKorasik & operator +=(const string & s) {
        ++sz;
        int v = 0;
        for (int i = 0; i < s.SZ; ++i) {
            int c = ctoi(s[i]);
            if (bor[v].toBor[c] == -1) {
                bor.PB(Vertex(v, c));
                bor[v].toBor[c] = size() - 1;
            }
            v = bor[v].toBor[c];
        }
        bor[v].terms.PB(sz - 1);

        return *this;
    }

    size_t size() const {
        return bor.SZ;
    }

    VEC <int> checkSubstr(const string & t) {
        VEC <int> res(sz, 0);
        int v = 0;
        for (char c : t) {
            v = tryGo(v, ctoi(c));
            ++bor[v].cnt;
        }
        for (int i = 0; i < size(); ++i) {
            for (int j = i; j != 0; j = getMinLink(j)) {
                for (int v : bor[j].terms) {
                    res[v] += bor[i].cnt;
                }
            }
        }
        return res;
    }

private:

    int getLink(int v) {
        if (bor[v].link == -1) {
            if (v == 0 || bor[v].p == 0) {
                bor[v].link = 0;
            } else {
                bor[v].link = tryGo(getLink(bor[v].p), bor[v].pc);
            }
        }
        return bor[v].link;
    }

    int tryGo(int v, char c) {
        if (bor[v].toAut[c] == -1) {
            if (bor[v].toBor[c] != -1) {
                bor[v].toAut[c] = bor[v].toBor[c];
            } else {
                bor[v].toAut[c] = (v == 0 ? 0 : tryGo(getLink(v), c));
            }
        }
        return bor[v].toAut[c];
    }

    int getMinLink(int v) {
        if (bor[v].minLink == -1) {
            int curLink = getLink(v);
            if (!bor[curLink].terms.empty()) {
                bor[v].minLink = curLink;
            } else if (!curLink) {
                bor[v].minLink = 0;
            } else {
                bor[v].minLink = getMinLink(curLink);
            }
        }
        return bor[v].minLink;
    }

    VEC <Vertex> bor;
    int sz = 0;
};

VEC <int> ans;
AhoKorasik bor;
string t;

void in()
{
    ifstream cin("search5.in");
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        bor += s;
    }
    cin >> t;
}

void solution()
{
    ans = bor.checkSubstr(t);
}

void out()
{
    ofstream cout("search5.out");
    for (auto it : ans) {
        cout << it << "\n";
    }
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
