#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

#define NULLVAL -1
using namespace std;

int r;

struct matrix {
        long long a;
        long long b;
        long long c;
        long long d;
        matrix(long long a_, long long b_, long long c_, long long d_) {
            a = a_;
            b = b_;
            c = c_;
            d = d_;
        }
        matrix () {
            a = 1;
            b = 0;
            c = 0;
            d = 1;
        }

        const matrix operator*(const matrix& ss) const {
            matrix res;
            res.a = (this->a*ss.a + this->b*ss.c)%r;
            res.b = (this->a*ss.b + this->b*ss.d)%r;
            res.c = (this->c*ss.a + this->d*ss.c)%r;
            res.d = (this->c*ss.b + this->d*ss.d)%r;
            return res;
        }
};


struct Node {
    Node* Left = nullptr;
    Node* Right = nullptr;
    int Lt = 0;
    int Rt = 0;
    matrix m ;//= matrix();

    Node(int Lt_, int Rt_){
        Lt = Lt_;
        Rt = Rt_;
    }

    void makeTree(vector <matrix> &matr){
        if (Lt == Rt) {
            if (Lt < matr.size())
                m = matr[Lt];
            else
                m = matrix();
            return;
        }
        int mid = (Lt + Rt)/2;
        Left = new Node(Lt, mid);
        Left->makeTree(matr);
        Right = new Node(mid + 1, Rt);
        Right->makeTree(matr);
        m = Left->m * Right->m;
        //cout << Rt << " " << Lt << " : " << m.a << " " << m.b << " " << m.c << " " << m.d << "\n";
    }

    matrix get (int L, int R) {
        int mid = (Lt+Rt)/2;
        if (L == Lt && R == Rt) {
            return m;
        }
        if (R <= mid) {
            return Left->get(L, R);
        }
        else if (L > mid) {
            return Right->get(L, R);
        }
        else {
            return Left->get(L, mid) * Right->get(mid+1, R);
        }
    }
};

int main()
{
    FILE* in = fopen("crypto.in", "r");
    FILE* out = fopen("crypto.out", "w");
    int n, m;
    fscanf(in, "%d%d%d", &r, &n, &m);
    Node* root = new Node(1, (int)pow(2,((int)log2(n)+((int)pow(2,(int)log2(n)) != n))));
    vector <matrix> matr(n+1);
    for (int i = 1; i <= n; ++i) {
        int a, b, c, d;
        fscanf(in, "%d%d%d%d", &a, &b, &c, &d);
        matr[i] = matrix(a, b, c, d);
        //cout << a << " " << b << " " << c << " " << d << "\n";
    }
    root->makeTree(matr);
    for (int i = 0; i < m; ++i) {
        int L, R;
        fscanf(in, "%d%d", &L, &R);
        //cout << L << " " << R << "\n";
        matrix res = root->get(L, R);
        fprintf(out, "%lld %lld\n%lld %lld\n", res.a, res.b, res.c, res.d);
    }
    return 0;
}
