#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

long long get (vector <long long> &tree, int v, long long tl, long long tr, long long l, long long r)
{
    if (l > r)
        return 0;
    if (tl == l && tr == r) {
        return tree[v];
    }
    long long mid = (tl+tr)/2;
    return get(tree, 2*v,  tl, mid, l, min(r, mid)) + get(tree, 2*v+1, mid+1, tr, max(l, mid+1), r);
}

void update (vector <long long> &tree, int v)
{
    v /= 2;
    while (v >= 1) {
        tree[v] = tree[2*v] + tree[2*v+1];
        v /= 2;
    }
}

int main()
{
    FILE* in = fopen("rsq.in", "r");
    FILE* out = fopen("rsq.out", "w");
    int n;
    fscanf(in, "%d", &n);
    int tree_sz = (1<<((int)log2(n)+2)) + 1;
    vector <long long> tree(tree_sz, 0);
    for (int i = 0; i < n; i++)
        fscanf(in, "%lld", &tree[tree_sz/2+i]);
    for (int i = tree_sz/2-1; i >= 1; i--)
        tree[i] = tree[2*i] + tree[2*i+1];
    char t[4];
    long long a, b;
    while (fscanf(in, "%s%lld%lld", &t, &a, &b) != -1) {
        if (strcmp(t, "sum") == 0) {
            fprintf(out, "%lld\n", get(tree, 1, 1, tree_sz/2, a, b));
        }
        else {
            a -= 1;
            tree[tree_sz/2+a] = b;
            update(tree, tree_sz/2+a  );
        }
    }
    return 0;
}
