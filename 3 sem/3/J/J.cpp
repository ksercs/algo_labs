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
#define LL uint64_t

using namespace std;

const char ZERO_SIGN = 'a' - 1;
const int ALPHA = 27;
const LL MOD = (LL)1e9 + 17;

int ctoi(char c) {
    return (int)c - (int)(ZERO_SIGN);
}

class SuffixArray {
public :
    SuffixArray(string const & s) : n(s.SZ) {
        suff.resize(n, 0);
        c.resize(n, 0);
        int classCnt = firstSort(s);
        for (int blockSize = 1; blockSize < n; blockSize *= 2) {
            classCnt = Sort(blockSize, classCnt);
        }

        countPref(s);
    }

    friend ostream& operator<<(ostream& os, const SuffixArray& sufArr);

private :
    int firstSort(string const & s) {
        VEC <int> cnt(ALPHA, 0);
        for (size_t i = 0; i < n; ++cnt[ctoi(s[i++])]);
        for (size_t i = 1; i < ALPHA; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (size_t i = 0; i < n; ++i) {
            int c = ctoi(s[i]);
            suff[--cnt[c]] = i;
        }
        int cur_c = 0;
        for (size_t i = 1; i < n; ++i) {
            cur_c += (int)(s[suff[i]] != s[suff[i - 1]]);
            c[suff[i]] = cur_c;
        }
        return cur_c + 1;
    }

    void sortBySecondElement(const int & blockSize, const int classCnt) {
        VEC <int> suff_tmp(n);
        for (size_t i = 0; i < n; ++i) {
            suff_tmp[i] = suff[i] - blockSize + n * (blockSize > suff[i]);
        }

        updateSuff(suff_tmp, classCnt);
    }

    void updateSuff(VEC <int> & suff_tmp, const int classCnt) {
        VEC <int> cnt(classCnt, 0);
        for (size_t i = 0; i < n; ++cnt[c[suff_tmp[i++]]]);
        for (size_t i = 1; i < classCnt; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            int shiftedInd = suff_tmp[i];
            suff[--cnt[c[shiftedInd]]] = shiftedInd;
        }
    }

    int Sort(const int & blockSize, const int classCnt) {
        sortBySecondElement(blockSize, classCnt);

        VEC <int> c_tmp(n, 0);
        int cur_c = 0;
        for (size_t i = 1; i < n; ++i) {
            int a_mid = (suff[  i  ] + blockSize) % n,
                b_mid = (suff[i - 1] + blockSize) % n;
            cur_c += int(c[suff[i]] != c[suff[i - 1]] || c[a_mid] != c[b_mid]);
            c_tmp[suff[i]] = cur_c;
        }
        c = c_tmp;

        return cur_c + 1;
    }

    void countHash(string const & s, LL * h, LL * st) {
        LL p = 1;
        *st = p;
        *h = p * s[0];
        LL last = *h;

        for (int i = 1; i < n; ++i) {
            p = (p * 1003) % MOD;
            ++h;
            ++st;
            *h = (last + s[i] * p) % MOD;
            *st = p;
            last = *h;
        }
    }

    void countPref(string const & s) {
        pref.resize(n - 2, 0);
        LL h[n];
        LL st[n];
        countHash(s, h, st);

        for (int i = 1; i < n - 1; ++i) {
            int a = suff[i];
            int b = suff[i + 1];
            pref[i - 1] = binSearch(a, b, h, st);
        }
    }

    bool check(int a, int b, int len, LL const * h, LL const * st) {
        int dif = b - a;
        LL a_hash = ((h[a + len - 1]) - (a == 0 ? 0 : h[a - 1]));
        LL b_hash = ((h[b + len - 1]) - h[b - 1]);
        a_hash = (a_hash * st[dif]) % MOD;

        return a_hash == b_hash;
    }

    int binSearch(int a, int b, LL const * h, LL const * st) {
        int L = 0, R = 0;
        if (a > b) {
            R += (n - a);
            swap(a, b);
        } else {
            R += (n - b);
        }

        while (R - L > 1) {
            int M = L + (R - L) / 2;
            if (check(a, b, M, h, st)) {
                L = M;
            } else {
                R = M;
            }
        }
        return L;
    }

    int n;
    VEC <int> suff;
    VEC <int> c;
    VEC <int> pref;
};

ostream& operator <<(ostream& os, const SuffixArray& sufArr) {
    for (int i = 1; i < sufArr.n; ++i) {
        os << sufArr.suff[i] + 1 << " ";
    }
    os << "\n";
    for (auto it : sufArr.pref) {
        os << it << " ";
    }
    os << "\n";
    return os;
}

string s;

int main()
{
    ios_base::sync_with_stdio(false);
    ifstream cin("array.in");
    cin.tie(0);
    getline(cin, s);

    SuffixArray sufArr(s + ZERO_SIGN);

    ofstream cout("array.out");
    cout.tie(0);
    cout << sufArr;

    return 0;
}
