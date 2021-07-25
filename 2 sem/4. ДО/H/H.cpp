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
#include <climits>

#define SZ size()
#define VEC vector
#define PB push_back
#define MP make_pair
#define SS second
#define FF first
#define PII pair <int,int>
#define LL long long

using namespace std;

const LL MAX_LVL = 20, MAX_VAL = (1<<31)-2;

LL n, lvl, ln, q, fl = 1, l_count;

struct vertex
{
    LL val;
    LL maxi;
    LL Tagged;
    LL Left;
    LL Right;
};

vertex tree[(1<<MAX_LVL)-1];

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

struct que
{
    LL L;
    LL R;
    LL res;
    que (LL a, LL b, LL c)
    {
        L = a;
        R = b;
        res = c;
    }
};

void iniz_t()
{
  for (LL i = ((ln+1)>>1)-1; i >=1; --i)
  {
      LL l_p = potom(i,0), r_p = potom(i,1);
      tree[i].maxi = LLONG_MIN;
      tree[i].Left = tree[l_p].Left;
      tree[i].Right = tree[r_p].Right;
  }
}

void push(LL v)
{
    //cout << v <<" " <<tree[v].val <<"\n";
    LL l_p = v<<1;
    tree[v].Tagged = 0;
    tree[l_p].Tagged = 1;
    tree[l_p+1].Tagged = 1;
    tree[l_p].maxi = max(tree[l_p].maxi, tree[v].maxi);
    tree[l_p+1].maxi = max(tree[l_p+1].maxi, tree[v].maxi);
    //cout << potom(v,0).val << " " << potom(v,1).val <<  " " << tree[v].val/2 <<"\n";
}

LL Search(LL v, LL sL, LL sR)
{
    //cout << v << " " <<sL << " " <<sR << "\n";
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
        if (tree[v].Tagged) push(v);
        LL l_pot = potom(v,0);
        LL M = tree[l_pot].Right;
        if(sR <= M) return Search(l_pot, sL, sR);
        else if(M < sL)return Search(l_pot + 1, sL, sR);
        else return min(Search(l_pot, sL, M), Search(l_pot + 1, M + 1, sR));
    }
    else{
        //cout << tree[v].val << "\n\n";
        //if (tree[v].Tagged) push(v);
        return tree[v].val;
    }
}


void update(LL v, LL x, LL sL, LL sR)
{
    //cout << v << " " <<sL << " " <<sR << "\n";
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {//cout << "1 : " << sL << " " << sR << " " << tree[v].Left << " " << tree[v].Right << "\n";
        if (tree[v].Tagged) push(v);
        LL l_pot = potom(v,0);
        LL M = tree[l_pot].Right;
        //cout << M << "\n";
        if(sR <= M)  update(l_pot, x, sL, sR);
        else if(M < sL) update(l_pot + 1, x, sL, sR);
        else { update(l_pot, x, sL, M) ; update(l_pot + 1, x, M + 1, sR);}
    }
    else{
        //cout  << "HEYHEYHEY\n\n";
        //if (tree[v].Tagged) push(v);
        tree[v].Tagged = 1;
        tree[v].maxi = max(tree[v].maxi, x);
        //cout << v << " " << tree[v].st.SZ << "\n";// system("PAUSE");
    }
}

void in()
{
    ios_base:: sync_with_stdio(false);
    cin.tie(0);
    ifstream cin("rmq.in");
    cin >> n >> q;
    ln_count(n);
    l_count = (ln+1)>>1;
    for (LL i = l_count; i <= ln; ++i)
    {
        tree[i].maxi = LLONG_MIN;
        tree[i].val = MAX_VAL;
        tree[i].Left =  tree[i].Right = i-l_count+1;
    }
    iniz_t();
    LL L, R, x;
    VEC <que> quest;
    for (LL i = 0; i < q; ++i) {
        cin >> L >> R >> x;
        quest.PB(que(L,R,x));
        update(1, x, L, R);
    }
    for (LL i = 1; i < l_count; ++i) {
        if (tree[i].Tagged) push(i);
    }
    for (LL i = l_count; i < l_count+n; ++i) {
        if (tree[i].maxi != LLONG_MIN) tree[i].val = tree[i].maxi;
           // cout << tree[i].val << " ";
    }
    for (LL i = ((ln+1)>>1)-1; i >=1; --i) {
        LL l_p = potom(i,0), r_p = potom(i,1);
        tree[i].val = min(tree[l_p].val, tree[r_p].val);
    }
    for (LL i = 0; i < quest.SZ; ++i) {
        LL a = Search(1, quest[i].L, quest[i].R);
        //cout << quest[i].res << " " << a << "\n";
        if (a != quest[i].res) {
            fl = 0;
            break;
        }
    }
}

void out()
{
    cout.tie(0);
    ofstream cout("rmq.out");
    if (fl) {
        cout << "consistent\n";
        for (LL i = l_count; i < l_count + n; ++i) {
            cout << tree[i].val << " ";
        }
    }
    else {
        cout << "inconsistent\n";
    }
}

int main()
{
    in();
    out();
    return 0;
}
