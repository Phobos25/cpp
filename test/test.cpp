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

// option 1 : pass a reference to the future
double tes(double z){
    vector<double> v = { 0, 1.1, 2.2, 3.3, 4.4, 5.5 };
    int y =0;
    for (const auto x:v){
        y += x*x*z;
    }
    return y;
}
void test1()
{
    vector<double> v = { 0, 1.1, 2.2, 3.3, 4.4, 5.5 };
    auto K = [=](double z){
    double y=0; 
    for (const auto x : v)
        y += x*x*z;
    return y;
    };
    
    vector<future<double>> VF;
    // for (double i : {1,2,3,4,5,6,7,8,9}) VF.push_back(async(K,i));
    for (double i : {1,2,3,4,5,6,7,8,9}){
        VF.push_back(async(tes, i));
    }

    for (auto& f:VF){
        cout << f.get() << " ";
    }
    cout << endl;
}


int main() {    
    vector<string> queries = {"london", "the"};
    vector<future<string>> futures(2);
    int count = 0;
    // for (string query:queries){        
    //     futures[count++] = async(SingleThread, query);
    //     // futures.push_back(async(SingleThread, query));
    // }
    futures[0]  = async(SingleThread, ref(queries[0]));
    futures[1]  = async(SingleThread, ref(queries[1]));

    for (auto& fut:futures){
        cout << fut.get() << endl;
    }
    // cout << futures.size() << endl;
    // string result = "";
    // for (auto& fut:futures){
    //     result += fut.get();
    // }
    // cout << result << endl;
    // cout << search_results_output.str();
    return 0;
}