#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "profile.h"
#include <queue>
using namespace std;

void DepthFirstPrint(const map <string, vector<string>>& graph, string& source){
    vector<string> stack{source};
    while (stack.size() > 0){
        auto current = stack.back();
        stack.pop_back();
        cout << current << "\n";

        for (auto& neighbour: graph.at(current)){
            stack.push_back(neighbour);
        }
    }
}

void DepthFirstPrintRecursively(
    map<string, vector<string>>& graph, 
    string& source){
    
    cout << source << "\n";
    for (auto& neighbour: graph.at(source)){
        DepthFirstPrintRecursively(graph, neighbour);
    }
}

int main() {
    
    map<string, vector<string>> graph {
        {"a", vector<string>({"b", "c"})},
        {"b", vector<string>({"d"})},     
        {"c", vector<string>({"e"})},
        {"d", vector<string>({"f"})},
        {"e", vector<string>()},
        {"f", vector<string>()} 
    };
    string source = "a";
    {
        LogDuration("for loop");
        DepthFirstPrint(graph, source);
    }
    {
        LogDuration("recursion");
        DepthFirstPrintRecursively(graph, source);
    }
    return 0;
}