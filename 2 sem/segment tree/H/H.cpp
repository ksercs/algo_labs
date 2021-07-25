#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

#define NULLVAL -100000000000
using namespace std;

vector <long long> ans;

struct Node {
    long long val = NULLVAL;
    Node* Left = nullptr;
    Node* Right = nullptr;
    int Lt = 0;
    int Rt = 0;
    long long setVal = NULLVAL;

    Node(int Lt_, int Rt_){
        Lt = Lt_;
        Rt = Rt_;
    }

    void check () {
        int mid = (Lt+Rt)/2;
        if (Left == nullptr) {
            Left = new Node(Lt, mid);
        }
        if (Right == nullptr) {
            Right = new Node(mid+1, Rt);
        }
    }

    long long get (int L, int R) {
        int mid = (Lt+Rt)/2;
        if (L == Lt && R == Rt) {
            return val;
        }
        if (R <= mid) {
            return Left->get(L, R);
        }
        else if (L > mid) {
            return Right->get(L, R);
        }
        else {
            return min(Left->get(L, mid), Right->get(mid+1, R));
        }
    }

    void propogate() {
        //cout << Lt << " " << Rt << "\n";
        if (Lt == Rt) {
            if (val == NULLVAL) {
                val = ((1LL<<31)-1);
            }
            //cout << "RETURN " << val << "\n";
            ans.push_back(val);
            return;
        }
        check();
        Left->val = max(Left->val, setVal);
        Right->val = max(Right->val, setVal);
        Left -> setVal = max(Left->setVal, setVal);
        Right -> setVal = max(Right->setVal, setVal);
        Left->propogate();
        Right->propogate();
        val = min(Left->val, Right->val);
        setVal = NULLVAL;
    }

    void set(int L, int R, long long d) {
        //cout << Lt << " " << Rt << "\n";
        int mid = (Lt+Rt)/2;
        if (L == Lt && R == Rt) {
            setVal = max(setVal, d);
            val = max(val, setVal);
            //cout << "RETURN " << setVal << "\n";
            return;
        }
        check();
        if (R <= mid){
            Left->set(L, R, d);
        }
        else if (L > mid) {
            Right->set(L, R, d);
        }
        else {
            Left->set(L, mid, d);
            Right->set(mid+1, R, d);
        }
    }
};

int main()
{
    FILE* in = fopen("rmq.in", "r");
    FILE* out = fopen("rmq.out", "w");
    int n, m;
    fscanf(in, "%d%d", &n, &m);
    Node* root = new Node(1, (int)pow(2,((int)log2(n)+((int)pow(2,(int)log2(n)) != n))));
    vector <int> L(m), R(m);
    vector <long long> x(m);
    for (int i = 0; i < m; ++i) {
        fscanf(in, "%d%d%lld", &L[i], &R[i], &x[i]);
        //cout << L[i] << " " << R[i] << " " << x[i] << "\n";
        root->set(L[i], R[i], x[i]);
    }
    root->propogate();
    int flag = 1;
    for (int i = 0; i < m; ++i) {
        if (root->get(L[i], R[i]) != x[i])
            flag = -1;
    }
    if (flag == 1){
        fprintf(out, "consistent\n");
        for (int i = 0; i < n; i++) {
            fprintf(out, "%lld ", ans[i]);
        }
        fprintf(out, "\n");
    } else {
        fprintf(out, "inconsistent\n");
    }
    return 0;
}
