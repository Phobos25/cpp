#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "profile.h"
#include <queue>
using namespace std;

void BreadthFirstPrint(map <string, vector<string>>& graph, string& source){
    queue<string> que;
    que.push(source);
    while (que.size() > 0){
        auto current = que.front();
        que.pop();
        cout << current << endl;
        for (auto& neighbour : graph.at(current)){
            que.push(neighbour);
        }
    }
}

int main() {
    
    map<string, vector<string>> graph {
        {"a", vector<string>({"c", "b"})},
        {"b", vector<string>({"d"})},     
        {"c", vector<string>({"e"})},
        {"d", vector<string>({"f"})},
        {"e", vector<string>()},
        {"f", vector<string>()} 
    };
    string source = "a";
    BreadthFirstPrint(graph, source);
    return 0;
}