#include <bits/stdc++.h>

using namespace std;

int get (int a, vector <int>& v)
{
    if (a == v[a])
        return a;
    return v[a] = get(v[a], v);
}

int main()
{
    freopen("dsu.in", "r", stdin);
    freopen("dsu.out", "w", stdout);
    int n, a, b;
    cin >> n;
    vector <int> s(n+1), sz(n+1, 1), lit(n+1), big(n+1);
    for (int i = 1; i <= n; i += 1)
    {
        s[i] = i;
        lit[i] = i;
        big[i] = i;
    }
    string str;
    while (cin >> str)
    {
        if (str == "union")
        {
            cin >> a >> b;
            a = get(a, s);
            b = get(b, s);
            if (a != b)
            {
                if (sz[a] > sz[b])
                    swap(a, b);
                sz[b] += sz[a];
                if (big[b] < big[a])
                    big[b] = big[a];
                if (lit[b] > lit[a])
                    lit[b] = lit[a];
                s[a] = s[b];
            }
        }
        else
        {
            cin >> a;
            a = get(a, s);
            cout << lit[a] << " " << big[a] << " " << sz[a] << endl;
        }
    }
    return 0;
}
