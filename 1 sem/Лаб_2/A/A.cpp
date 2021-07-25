#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <set>
#include <stack>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int MAX_SIZE = 200000 + 5;

char s;

string str, s1;

stack <int> st;

void in()
{
    ifstream cin("decode.in");
    cin >> s1;
    for (int i = 0; i < s1.size(); i++)
    {
        s = s1[i];
        if (st.empty()) {st.push(s);}
        else
        {
            if (st.top() == s) {st.pop();}
            else               {st.push(s);}
        }
    }
}

void solution()
{
    while(!st.empty())
    {
        str+=st.top();
        st.pop();
    }
}

void out()
{
    ofstream cout("decode.out");
  for (int i = str.size()-1; i >= 0; i--)
  {
      cout << str[i];
  }
  cout << "\n";
}

int main()
{
    in();
    solution();
    out();
return 0;
}
