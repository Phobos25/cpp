#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
using namespace std;

// recursive
// bool HasPath(map<string, vector<string>>& graph, string src, string dst){
//     if (src == dst){
//         return true;
//     }
//     for (auto& n: graph.at(src)){
//         if (HasPath(graph, n, dst) == true){
//             return true;
//         }
//     }

//     return false;
// }
// breadth first
// bool HasPath(map<string, vector<string>>& graph, string src, string dst){
//     queue<string> que;
//     que.push(src);
//     while (que.size() > 0){
//         auto current = que.front();
//         que.pop();
//         if (current == dst){
//             return true;
//         }
//         for (auto& n : graph.at(current)){
//             que.push(n);
//         }
//     }
//     return false;
// }

bool HasPath(map<string, vector<string>>& graph, string src, string dst){
    vector<string> stack;
    stack.push_back(src);
    while (stack.size() > 0){
        auto current = stack.back();
        stack.pop_back();
        if (current == dst){
            return true;
        }
        for (auto& n : graph.at(current)){
            stack.push_back(n);
        }
    }
    return false;
}


int main() {
    map<string, vector<string>> graph {
        {"f", vector<string>({"g", "i"})},
        {"g", vector<string>({"h"})},     
        {"h", vector<string>()},
        {"i", vector<string>({"g", "k"})},
        {"j", vector<string>({"i"})},
        {"k", vector<string>()} 
    };

    string src = "f";
    string dst = "k";
    cout << HasPath(graph, src, dst) << endl;
    return 0;
}