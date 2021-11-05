#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include "test_runner.h"
using namespace std;

template <typename T>
map<T, vector<T>> BuildGraph(vector<pair<T, T>>& edges){
	map<T, vector<T>> graph;
	for (auto& [first, second]:edges){		
		graph[first].push_back(second);
		graph[second].push_back(first);
	}
	return graph;		
}
 
int main() {
    vector<pair<string, string>> edges; 
	edges.push_back(make_pair("w","x"));
	edges.push_back(make_pair("x","y"));
	edges.push_back(make_pair("z","y"));
	edges.push_back(make_pair("z","v"));
	edges.push_back(make_pair("w","v"));
    return 0;
}