#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int main()
{
    FILE* in = fopen("sum0.in", "r");
    FILE* out = fopen("sum0.out", "w");
    long long n, x, y, a0, m, z, t, b0;
    vector <long long> p;
    long long sum = 0;
    vector <int> a, b, c;
    fscanf(in, "%lld%lld%lld%lld", &n, &x, &y, &a0);
    fscanf(in, "%lld%lld%lld%lld", &m, &z, &t, &b0);
    a.push_back(a0);
    p.push_back(a0);
    b.push_back(b0);
    for (int i = 1; i < n; i++) {
        a.push_back((a[i-1]*x + y) % (1 << 16));
        p.push_back(p[i-1] + a[i]);
    }
    for (int i = 1; i < 2*m; i++) {
        b.push_back((b[i-1]*z + t) % (1 << 30));
    }
    for (int i = 0; i < 2*m; i++) {
        b[i] = b[i]%n;
        if (i%2) {
            if (b[i-1] > b[i])
                swap(b[i], b[i-1]);
            sum += p[b[i]];
            if (b[i-1] > 0)
                sum -= p[b[i-1]-1];
        }
    }
    fprintf(out, "%lld", sum);
    return 0;
}
