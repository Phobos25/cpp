#include <numeric>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <iostream>

using namespace std;


template <typename T>
class Synchronized {
public:
  explicit Synchronized(T initial = T())
          : value(move(initial))
  {
  }

  struct Access {
    T& ref_to_value;    
    lock_guard<mutex> guard;    
  };

  Access GetAccess(){  
    return {value, lock_guard(m)};
  }

private:
  T value;
  mutex m;
};

void TestConcurrentUpdate() {
  Synchronized<string> common_string;

  const size_t add_count = 50000;
  auto updater = [&common_string, add_count] {
    for (size_t i = 0; i < add_count; ++i) {
      auto access = common_string.GetAccess();
      access.ref_to_value += 'a';
    }
  };

  auto f1 = async(updater);
  auto f2 = async(updater);

  f1.get();
  f2.get();
  
  cout << common_string.GetAccess().ref_to_value.size() << endl;
}

int main() {
  Synchronized<string> common_string;
  TestConcurrentUpdate();
  return 0;
}