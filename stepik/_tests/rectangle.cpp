#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n; // size of array
  int q; // number of queries
  cin >> n; 
  vector<int> s(n+1, 0);
  vector<int> a(n,0);
  s[0] = 0;
  for (int i = 1; i <= n; i++)
  {
    cin >> a[i];
    s[i] = s[i-1] + a[i];
  }
  
  cin >> q;
  for (int i = 0; i < q; i++)
  {
    int L, R;
    cin >> L >> R;
    cout << s[R] - s[L-1] << endl;
  }
  

  return 0;
}