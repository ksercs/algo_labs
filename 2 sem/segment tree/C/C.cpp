#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

#define NULLVAL 10000000000
using namespace std;

struct Node {
    long long val = NULLVAL;
    Node* Left = nullptr;
    Node* Right = nullptr;
    int Lt = 0;
    int Rt = 0;
    long long addVal = NULLVAL;
    long long setVal = NULLVAL;

    Node(int Lt_, int Rt_){
        Lt = Lt_;
        Rt = Rt_;
    }

    void makeTree(vector <long long> &a){
        if (Lt == Rt) {
            if (Lt < a.size())
                val = a[Lt];
            else
                val = NULLVAL;
            return;
        }
        int mid = (Lt + Rt)/2;
        Left = new Node(Lt, mid);
        (*Left).makeTree(a);
        Right = new Node(mid + 1, Rt);
        (*Right).makeTree(a);
        val = min((*Left).val, (*Right).val);
    }

    long long get (int L, int R) {
        if (L > Rt || R < Lt)
            return NULLVAL;
        if (Lt >= L && Rt <= R) {
            return val;
        }
        propogate();
        return min((*Left).get(L, R), (*Right).get(L, R));
    }

    void propogate() {
        if (Lt == Rt || (setVal == NULLVAL && addVal == NULLVAL))
            return;
        if (setVal != NULLVAL) {
            (*Left).val = setVal;
            (*Left).addVal = NULLVAL;
            (*Left).setVal = setVal;
            (*Right).val = setVal;
            (*Right).setVal = setVal;
            (*Right).addVal = NULLVAL;
        }
        if (addVal != NULLVAL) {
            (*Left).val += addVal;
            if ((*Left).addVal == NULLVAL)
                (*Left).addVal = addVal;
            else
                (*Left).addVal += addVal;
            (*Right).val += addVal;
            if ((*Right).addVal == NULLVAL)
                (*Right).addVal = addVal;
            else
                (*Right).addVal += addVal;
        }
        setVal = NULLVAL;
        addVal = NULLVAL;
    }

    void add(int L, int R, int d) {
        if (L > Rt || R < Lt) {
            return;
        }
        if (Lt >= L && Rt <= R) {
            propogate();
            val += d;
            addVal = d;
            return;
        }
        propogate();
        (*Left).add(L, R, d);
        (*Right).add(L, R, d);
        val = min((*Left).val, (*Right).val);
    }

    void set(int L, int R, int d) {
        if (L > Rt || R < Lt) {
            return;
        }
        if (Lt >= L && Rt <= R) {
            val = d;
            setVal = d;
            addVal = NULLVAL;
            return;
        }
        propogate();
        (*Left).set(L, R, d);
        (*Right).set(L, R, d);
        val = min((*Left).val, (*Right).val);
    }
};

int main()
{
    FILE* in = fopen("rmq2.in", "r");
    FILE* out = fopen("rmq2.out", "w");
    int n;
    vector <long long> a;
    fscanf(in, "%d", &n);
    a.resize(n+1);
    for (int i = 1; i <= n; i++) {
        fscanf(in, "%lld", &a[i]);
    }
    Node* root = new Node(1, (int)pow(2,((int)log2(n)+((int)pow(2,(int)log2(n)) != n))));
    (*root).makeTree(a);
    char t[100];
    while (fscanf(in, "%s", &t) != -1) {
        int L, R;
        fscanf(in, "%d%d", &L, &R);
        if (t[0] == 'm') {
            fprintf(out, "%lld\n", (*root).get(L, R));
        }
        if (t[0] == 'a') {
            long long val;
            fscanf(in, "%lld", &val);
            (*root).add(L, R, val);
        }
        if (t[0] == 's') {
            long long val;
            fscanf(in, "%lld", &val);
            (*root).set(L, R, val);
        }
    }
    return 0;
}
