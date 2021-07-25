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
    Vertex(int _p = -1, char _pc = 0) : cnt(0), minLink(-1), link(-1), p(_p), pc(_pc), ind(INT_MAX, -1) {
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
    PII ind;
};

VEC <PII> ans;

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

    void checkSubstr(const string & t) {
        ans.resize(sz, {INT_MAX, -1});
        int v = 0;
        for (int i = 0; i < t.SZ; ++i) {
            char c = t[i];
            v = tryGo(v, ctoi(c));
            bor[v].ind.FF = min(bor[v].ind.FF, i);
            bor[v].ind.SS = max(bor[v].ind.SS, i);
        }
        for (int i = 0; i < size(); ++i) {
            for (int j = i; j != 0; j = getMinLink(j)) {
                for (int v : bor[j].terms) {
                    ans[v].FF = min(ans[v].FF, bor[i].ind.FF);
                    ans[v].SS = max(ans[v].SS, bor[i].ind.SS);
                }
            }
        }
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

int n;
AhoKorasik bor;
VEC <int> len;
string t;

void in()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ifstream cin("search6.in");
    cin >> n;
    len.resize(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        bor += s;
        len[i] = s.SZ;
    }
    cin >> t;
}

void solution()
{
    bor.checkSubstr(t);
}

void out()
{
    cout.tie(0);
    ofstream cout("search6.out");
    for (int i = 0; i < n; ++i) {
        if (ans[i].FF == INT_MAX) {
            cout << "-1 -1\n";
            continue;
        }
        cout << ans[i].FF - len[i] + 1 << " " << ans[i].SS - len[i] + 1 << "\n";
    }
}

int main()
{
    in();
    solution();
    out();
    return 0;
}
