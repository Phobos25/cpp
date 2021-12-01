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
    string current_query = "current_query";
    int docid = 10;
    size_t hitcount = 3;
    
    search_results_output << current_query << ':'<< " {"; //O(1)  
    search_results_output << "docid: " << docid << ", "
                          << "hitcount: " << hitcount << '}';                
    
    search_results_output << endl;

    return search_results_output.str();
}

int main() {    
    const vector<string> queries = {"london", "the"};
    vector<future<string>> futures;

    for (string query:queries){
        futures.push_back(
            async([&query] {
                return SingleThread(query);
            })
        );
    }
    for (auto f: futures){
        
    }
    // cout << search_results_output.str();
    return 0;
}