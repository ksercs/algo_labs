#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

#define NULLVAL -1
using namespace std;

long long mass[100005];

struct Node {
    long long val = 0;
    Node* Left = nullptr;
    Node* Right = nullptr;
    long long Lt = 0;
    long long Rt = 0;
    long long num = 0;
    long long setVal = NULLVAL;

    Node(long long Lt_, long long Rt_){
        Lt = Lt_;
        Rt = Rt_;
    }

    void makeTree(vector <long long> &a){
        if (Lt == Rt){
            if (Rt < a.size()) {
                val = a[Lt];
                num = a[Lt]*a[Lt];
            }
            return;
        }
        long long mid = (Lt + Rt)/2;
        Left = new Node(Lt, mid);
        Left->makeTree(a);
        Right = new Node(mid + 1, Rt);
        Right->makeTree(a);
        val = Left->val + Right->val;
        num = Left->num + Right->num;
    }

    void check () {
        long long mid = (Lt+Rt)/2;
        if (Left == nullptr) {
            Left = new Node(Lt, mid);
        }
        if (Right == nullptr) {
            Right = new Node(mid+1, Rt);
        }
    }

    pair <long long, long long> get (long long L, long long R) {
        long long mid = (Lt+Rt)/2;
        if (L == Lt && R == Rt) {
            return make_pair(val, num);
        }
        if (R <= mid) {
            return Left->get(L, R);
        }
        else if (L > mid) {
            return Right->get(L, R);
        }
        else {
            pair <long long, long long> Lp = get(L, mid);
            pair <long long, long long> Rp = get(mid+1, R);
            return make_pair(Lp.first+Rp.first, Lp.second+Rp.second);
        }
    }

    void propogate() {
        Left->val = Right->val = val/2;
        Left->num = Right->num = Left->setVal = Right->setVal = (val != 0);
        setVal = NULLVAL;
    }

    void set(long long L, long long R, long long d) {
        //cout << Lt << " " << Rt << "\n";
        long long mid = (Lt+Rt)/2;
        if (L == Lt && R == Rt) {
            val = d;
            num = d*d;
            return;
        }
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
        //cout << "return\n";
        val = Left->val + Right->val;
        num = Left->num+Right->num;
        }
};

int main()
{
    FILE* in = fopen("permutation.in", "r");
    FILE* out = fopen("permutation.out", "w");
    long long n;
    fscanf(in, "%lld", &n);
    vector <long long> num;
    num.push_back(0);
    for (int i = 0; i < n; i++) {
        long long a;
        fscanf(in, "%lld", &a);
        num.push_back(a);
    }
    mass[1] = 1;
    mass[0] = 1;
    for (long long i = 2; i <= n; i++) {
        mass[i] = mass[i-1] + i*i;
    }
    long long m;
    fscanf(in, "%lld ", &m);
    Node* root = new Node(1, 1048576/4);
    root->makeTree(num);
    for (int i = 0; i < m; i++) {
        long long t, L, R;
        fscanf(in, "%lld%lld%lld", &t, &L, &R);
        if (t == 1) {
            root->set(L, L, R);
        } else {
            pair <long long, long long> res = root->get(L, R);
            //cout << res.second << " " << mass[R-L+1] << "\n";
            if (res.first == (1+R-L+1)*(R-L+1)/2 && res.second == mass[R-L+1])
                fprintf(out, "YES\n");
            else
                fprintf(out, "NO\n");
        }
    }
    return 0;
}
