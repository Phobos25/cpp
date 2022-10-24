/*
 * Каким наименьшим количеством монет с
 * номиналами 1, 2, 8 и 10 можно набрать сумму 27?
 * Можно использовать несколько монет каждого
 * номинала.
 */


#include <iostream>
#include <vector>

using namespace std;

int change(int n, const vector<int> &a, int s){
  int cnt = 0;

  for (int i = 0; i < n; ++i){
    cnt += s / a[i];
    s %= a[i];
  }

  return cnt;
}

int main() {
  vector<int> d {10, 8, 2, 1};
  int total = 27;
  cout << change (4, d, total) << endl;
  return 0;
}

