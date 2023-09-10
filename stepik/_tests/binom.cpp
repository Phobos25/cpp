#include <iostream>
#include <vector>

using namespace std;

int main() {   
  int n, k;
  cin >> n >> k;
  vector<vector<long long>> c(n+1,vector<long long> (k+1));  

  for (int i = 0; i <= n; i++){
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; j++)
      c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
  }
  cout << c[n][k] << endl;
  return 0;
}