#include<iostream>
#include<stack>
using namespace std;

int const n = 7;
char s[2 * n];
int k;
stack<char> stk;

void out() 
{
    k--;
    if (k == 0) 
    {
        for (int i = 0; i < 2*n; i++) 
            cout << s[i];    
        cout << endl;
    }
}

void rec(int idx) 
{
    if (stk.size() > (2*n - idx)) return;
    if (idx == 2*n)
    {
        if (stk.empty()) 
            out();
        return;
    }
    s[idx] = '(';
    stk.push('(');
    rec(idx + 1);
    stk.pop();
    if (!stk.empty() && stk.top() == '(') 
    {
        s[idx] = ')';
        stk.pop();
        rec(idx + 1);
        stk.push('(');
    }
    s[idx] = '[';
    stk.push('[');
    rec(idx + 1);
    stk.pop();
    if (!stk.empty() && stk.top() == '[')
    {
        s[idx] = ']';
        stk.pop();
        rec(idx + 1);
        stk.push('[');
    }
}

int main() 
{
    cin >> k;
    rec(0);
    return 0;
}