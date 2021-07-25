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
#define LL long long

using namespace std;

const LL MAX_LVL = 21;

LL n, lvl, ln, q;

struct vertex
{
    LL val;
    LL Tagged;
    LL Left;
    LL Right;
    LL pl;
    LL neut = 0;
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
      tree[i].val = min(tree[l_p].val, tree[r_p].val);
      tree[i].Left = tree[l_p].Left;
      tree[i].Right = tree[r_p].Right;
  }
}

void push(LL v)
{
    //cout << v <<" " <<tree[v].val <<"\n";
    LL l_p = v<<1;
    if (!tree[v].Tagged && tree[v].pl) {
        tree[l_p].pl += tree[v].pl;
        tree[l_p+1].pl += tree[v].pl;
        tree[l_p].val += tree[v].pl;
        tree[l_p+1].val += tree[v].pl;
        tree[v].pl = 0;
        return;
    }
    tree[v].Tagged = 0;
    tree[v].pl = 0;
    tree[l_p].Tagged = 1;
    tree[l_p].pl = 0;
    tree[l_p+1].pl = 0;
    tree[l_p+1].Tagged = 1;
    tree[l_p].val = tree[l_p+1].val = tree[v].val;
    //cout << potom(v,0).val << " " << potom(v,1).val <<  " " << tree[v].val/2 <<"\n";
}

void assign(LL v, LL new_val, LL sL, LL sR)
{
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
        if (tree[v].Tagged || tree[v].pl) push(v);
        LL pot = (v << 1);
        LL M = tree[pot].Right;
        if(sR <= M)  assign(pot, new_val, sL, sR);
        else if(M < sL) assign(pot + 1, new_val, sL, sR);
        else  {assign(pot, new_val, sL, M); assign(pot + 1, new_val, M + 1, sR);}
        tree[v].val = min(tree[potom(v,0)].val, tree[potom(v,1)].val);
    }
    else{
        //cout << tree[v].val << "\n\n";
        if (tree[v].Tagged || tree[v].pl) push(v);
        tree[v].Tagged = 1;
        tree[v].pl = 0;
        tree[v].val = new_val;
    }
}

void add(LL v, LL new_val, LL sL, LL sR)
{
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
        if (tree[v].Tagged || tree[v].pl) push(v);
        LL pot = (v << 1);
        LL M = tree[pot].Right;
        if(sR <= M)  add(pot, new_val, sL, sR);
        else if(M < sL) add(pot + 1, new_val, sL, sR);
        else  {add(pot, new_val, sL, M); add(pot + 1, new_val, M + 1, sR);}
        tree[v].val = min(tree[potom(v,0)].val, tree[potom(v,1)].val);
    }
    else{
        //cout << tree[v].val << "\n\n";
        if (tree[v].Tagged || tree[v].pl) push(v);
        tree[v].pl = new_val;
        tree[v].val += new_val;
    }
}

LL Search(LL v, LL sL, LL sR)
{
    //cout << v << " " <<sL << " " <<sR << "\n";
    if( (tree[v].Left != sL) || (tree[v].Right != sR) )
    {
        if (tree[v].Tagged || tree[v].pl) push(v);
        LL l_pot = potom(v,0);
        LL M = tree[l_pot].Right;
        if(sR <= M) return Search(l_pot, sL, sR);
        else if(M < sL)return Search(l_pot + 1, sL, sR);
        else return min(Search(l_pot, sL, M), Search(l_pot + 1, M + 1, sR));
    }
    else{
        //cout << tree[v].val << "\n\n";
        if (tree[v].Tagged || tree[v].pl) push(v);
        return tree[v].val;
    }
}

void in()
{
    ifstream cin("rmq2.in");
    cin >> n;
    ln_count(n);
    LL l_count = (ln+1)>>1;
    for (LL i = l_count; i < l_count+n; ++i)
    {
        LL a;
        cin >> a;
        tree[i].val = a;
        tree[i].Left =  tree[i].Right = i-l_count+1;
    }
    for (LL i = l_count+n; i <= ln; ++i)
    {
        tree[i].Left = tree[i].Right = i-l_count+1;
        tree[i].val = LLONG_MAX;
    }
    iniz_t();
    LL L, R;
    string t;
    while (cin  >> t >> L >> R)
    {
        //cout << t << " " << L << " " << R << "\n";
        if (t == "set") {
            LL x;
            cin >> x;
            assign(1, x, L, R);
        }
        else if (t == "add") {
            LL x;
            cin >> x;
            add(1, x, L, R);

        } else {
            ans.push_back(Search(1, L, R));
        }
    }
}

void out()
{
    ofstream cout("rmq2.out");
    for (LL i = 1; i <= ln; ++i)
    {
        if (tree[i].Tagged && (tree[i].Left != tree[i].Right) ) push(i);
        //cout << tree[i].val << " " << tree[i].Left << " " << tree[i].Right << " " << tree[i].Tagged << "\n";
    }
    //cout << "\n";
    for (LL i = 0; i < ans.size(); ++i)
    {
        cout << ans[i] << "\n";
    }
}

int main()
{
    in();
    out();
    return 0;
}
