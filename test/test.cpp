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

void sort_by_map(){
    map<string, string> veggy_map = {{"1", "Yam",},
                                     {"2", "Pumpkin",},
                                     {"3", "Ginger",},
                                     {"4", "Melon",},
                                     {"5", "Beetroot",},
                                     {"6", "Spinach",}};



    map<string, string> veggy_map2;

    for (const auto & [key, value] : veggy_map) {
        veggy_map2.emplace(value, key);
    }  
}

void sort_by_vector(){
    map<string, string> veggy_map = {{"1", "Yam",},
                                     {"2", "Pumpkin",},
                                     {"3", "Ginger",},
                                     {"4", "Melon",},
                                     {"5", "Beetroot",},
                                     {"6", "Spinach",}};

    vector<std::pair<string, string> > arr;
    for (const auto &item : veggy_map) {
        arr.emplace_back(item);
    }

    std::sort(arr.begin(), arr.end(),
              [] (const auto x, const auto y) {return x.second < y.second;});

}

int main() {
    
    {LOG_DURATION("sort by map");
        for (int i=0; i<10'000'000; ++i){
            sort_by_map();
        }
    }

    {LOG_DURATION("sort by vector");
        for (int i=0; i<10'000'000; ++i){
            sort_by_vector();
        }
    }
    
    return 0;
}