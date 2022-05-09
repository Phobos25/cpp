#include <fstream>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

int ans = INT_MAX;

template <typename T>
ostream& operator << (ostream& stream, const vector<T>& vec){
  for (auto& v:vec){
    stream << v << ' ';
  }
  return stream;
}

int main(){  
  vector<vector<int>> result;
  vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  do {
    result.push_back(vec);    
  }while (next_permutation(vec.begin(), vec.end()));
  cout << result.size() << endl;
  return 0;
}
