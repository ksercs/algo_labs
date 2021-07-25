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
#include <string.h>
#include <unordered_set>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define LL long long

using namespace std;

const LL MAX_LVL = 23, MOD = (LL)1e9+7;

LL n, lvl, ln, q, p = 11;

LL  hashT[1<<21];
LL  hashDp[1<<21];

struct vertex
{
    LL sum;
    LL hashSum;
    LL val;
    LL Left;
    LL Right;
};

vertex tree[(1<<MAX_LVL)-1];
vector <LL> ans;

vertex pred(LL x)
{
  return tree[(x/2)];
}

LL potom(LL x, LL lr)
{
  return (2*x + lr);
}

LL lvl_count(LL x)
{
    LL level=1, ch=1;
    while(ch<x)
    {
     ch*=2;
     level++;
    }
    return level;
}

void ln_count(LL b)
{
  lvl = lvl_count(b);
  ln = (1<<(lvl))-1;
}

void iniz_t()
{
  for (LL i = ((ln+1)>>1)-1; i >=1; --i)
  {
      LL l_p = potom(i,0), r_p = potom(i,1);
      tree[i].sum = tree[l_p].sum + tree[r_p].sum;
      tree[i].hashSum = tree[l_p].hashSum + tree[r_p].hashSum;
      tree[i].Left = tree[l_p].Left;
      tree[i].Right = tree[r_p].Right;
  }
}

struct event
{
    LL hashSum;
    LL sum;
};

LL SearchSum(LL v, LL sL, LL sR)
{
    //cout << v << " " <<sL << " " <<sR << "\n";
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
        LL l_pot = potom(v,0);
        LL M = tree[l_pot].Right;
        if(sR <= M) return SearchSum(l_pot, sL, sR);
        else if(M < sL)return SearchSum(l_pot + 1, sL, sR);
        else return SearchSum(l_pot, sL, M) + SearchSum(l_pot + 1, M + 1, sR);
    }
    else{
        //cout << tree[v].val << "\n\n";
        return tree[v].sum;
    }
}

LL SearchHashSum(LL v, LL sL, LL sR)
{
    //cout << v << " " <<sL << " " <<sR << "\n";
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
        LL l_pot = potom(v,0);
        LL M = tree[l_pot].Right;
        if(sR <= M) return SearchHashSum(l_pot, sL, sR);
        else if(M < sL)return SearchHashSum(l_pot + 1, sL, sR);
        else return SearchHashSum(l_pot, sL, M) + SearchHashSum(l_pot + 1, M + 1, sR);
    }
    else{
        //cout << tree[v].val << "\n\n";
        return tree[v].hashSum;
    }
}

LL binPow (LL ch, LL st)
{
    if (st == 1)
        return ch;
    if (st&1) {
        return (ch*binPow(ch,st-1));
    }
    return (binPow(ch, st/2) * binPow(ch, st/2));
}

void countHash ()
{
    hashT[0] =  1;
    for (LL i = 1; i <= n; ++i) {
        hashT[i] = hashT[i-1]*p;
        hashDp[i] = hashDp[i-1] + hashT[i];
    }
}

void in()
{
    ifstream cin("permutation.in");
    cin >> n;
    countHash();
    ln_count(n);
    LL l_count = (ln+1)>>1;
    for (LL i = l_count; i < l_count+n; ++i)
    {
        LL a;
        cin >> a;
        tree[i].val = a;
        tree[i].sum = a;
        tree[i].hashSum = hashT[a];
        tree[i].Left =  tree[i].Right = i-l_count+1;
    }
    for (LL i = l_count+n; i <= ln; ++i)
    {
        tree[i].Left = tree[i].Right = i-l_count+1;
    }
    iniz_t();
    cin >> q;
    LL t, x, y;
    for (LL i = 0; i < q; ++i) {
        cin >> t >> x >> y;
        //cout << t << " " << x << " " << y << "\n";
        if (t == 1) {
            LL ind = l_count+x-1;
            tree[ind].val = y;
            tree[ind].sum = y;
            tree[ind].hashSum = hashT[y];
            ind /= 2;
            while (ind) {
                LL l_p = potom(ind, 0);
                LL r_p = potom(ind, 1);
                tree[ind].sum = tree[l_p].sum + tree[r_p].sum;
                tree[ind].hashSum = tree[l_p].hashSum + tree[r_p].hashSum;
                ind /= 2;
            }
        } else {
            event ev;
            ev.sum = SearchSum(1, x, y);
            ev.hashSum = SearchHashSum(1, x, y);
            if (ev.sum == (1+y-x+1)*(y-x+1)/2 && ev.hashSum == hashDp[y-x+1])
                ans.PB(1);
            else
                ans.PB(0);
        }
    }
}

void out()
{
    ofstream cout("permutation.out");
    for (LL i = 0; i < ans.size(); ++i)
    {
        ans[i] ? cout << "YES\n" : cout << "NO\n";
    }
}

int main()
{
    in();
    out();
    return 0;
}
