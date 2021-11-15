#include <numeric>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <iostream>

using namespace std;

int main() {
  int key = 5000;
  vector <int> data;
  data.push_back(1);
  data.push_back(2);

  cout << "5999 dividded by 2 " << key % data.size() << endl;
  data.push_back(3);
  cout << "5000 dividded by 3 " << key % data.size() << endl;
  
  cout << "5000 dividded by 6 " << key % 6 << endl;
  return 0;
}