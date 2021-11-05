#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
using namespace std;

template <typename T>
bool Explore (map<T, vector<T>>& graph, T node, set<T>& visited){
    if (visited.find(node) != visited.end()){
        return false;
    }
    visited.insert(node);
    for (T& neighbour: graph[node]){
        Explore(graph, neighbour, visited);
    }

    return true;
}

template <typename T>
int ConnectedComponentsCount(map<T, vector<T>>& graph){
    set<T> visited;
    int count = 0;
    for (auto& node: graph){
        if (Explore(graph, node.first, visited) == true){
            ++count;
        }
    }
    
    return count;
}

int main() {
    map<int, vector<int>> graph {
    {0, vector<int>({8, 1, 5})},
    {1, vector<int>({0})},     
    {5, vector<int>({0, 8})},
    {8, vector<int>({0, 5})},
    {2, vector<int>({3, 4})},
    {3, vector<int>({2, 4})},
    {4, vector<int>({3, 2})} 
    }; // -> 2
    cout << ConnectedComponentsCount(graph) << endl;
    return 0;
}