#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <thread>
#include <future>
#include <string>

using namespace std;

string SingleThread(string& current_query){
  ostringstream search_results_output;
  int docid = 10;
  size_t hitcount = 3;

  search_results_output << current_query << ':'<< " {"; //O(1)
  search_results_output << "docid: " << docid << ", "
      << "hitcount: " << hitcount << '}';

  search_results_output << endl;

  return search_results_output.str();
}

int main() {    
  vector<string> queries = {"london", "the"};
  vector<future<string>> futures;
  for (string& query:queries){
    futures.push_back(async(SingleThread, ref(query)));
  }
//  futures[0]  = async(SingleThread, ref(queries[0]));
//  futures[1]  = async(SingleThread, ref(queries[1]));

  for (auto& fut:futures){
    cout << fut.get() << endl;
  }
  return 0;
}
