#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include "test_runner.h"
using namespace std;

template <typename T>
int ExploreSize (map<T, vector<T>>& graph, T node, set<T>& visited){
    
    if (visited.find(node) != visited.end()){
        return 0;
    }
    visited.insert(node);
    
    int size = 1;
    for (T& neighbour: graph[node]){
        size += ExploreSize(graph, neighbour, visited);
    }

    return size;
}

template <typename T>
int LargestComponent(map<T, vector<T>>& graph) {
    set<T> visited;
    int longest = 0;           
    for (auto& node: graph){        
        int size = ExploreSize(graph, node.first, visited);
        if (size > longest){
            longest = size;
        }
    }
    return longest;
}

void TestProgram(){
    map<int, vector<int>> graph {
    {0, vector<int>({8, 1, 5})},
    {1, vector<int>({0})},     
    {5, vector<int>({0, 8})},
    {8, vector<int>({0, 5})},
    {2, vector<int>({3, 4})},
    {3, vector<int>({2, 4})},
    {4, vector<int>({3, 2})} 
    }; // -> largest 4        
            
    map<int,vector<int>> graph2{
    {1, vector<int>({2})},
    {2, vector<int>({1,8})},
    {6, vector<int>({7})},
    {9, vector<int>({8})},
    {7, vector<int>({6, 8})},
    {8, vector<int>({9, 7, 2})}
    }; // -> 6    
    
    map<int, vector<int>> graph3{
    {3, vector<int>({})},
    {4, vector<int>({6})},
    {6, vector<int>({4, 5, 7, 8})},
    {8, vector<int>({6})},
    {7, vector<int>({6})},
    {5, vector<int>({6})},
    {1, vector<int>({2})},
    {2, vector<int>({1})}
    }; // -> 5    
    
    map<int, vector<int>> graph_empty;    
    
    map<int, vector<int>> graph4 {
    {0, vector<int>({4,7})},
    {1, vector<int>({})},
    {2, vector<int>({})},
    {3, vector<int>({6})},
    {4, vector<int>({0})},
    {6, vector<int>({3})},
    {7, vector<int>({0})},
    {8, vector<int>({})}
    }; // -> 3

    ASSERT_EQUAL(LargestComponent(graph), 4);
    ASSERT_EQUAL(LargestComponent(graph2), 6);    
    ASSERT_EQUAL(LargestComponent(graph3), 5);
    ASSERT_EQUAL(LargestComponent(graph_empty), 0);
    ASSERT_EQUAL(LargestComponent(graph4), 3);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestProgram);
    
    return 0;
}