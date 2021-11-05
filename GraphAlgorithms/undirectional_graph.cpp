#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
using namespace std;

template <typename T>
map<T, vector<T>> BuildGraph(vector<pair<T, T>>& edges);

bool hasPath(map<string, vector<string>>& graph, string src, string dst, set<string>& visited);

bool UndirectedGraph(
		vector<pair<string, string>>& edges, 
		string nodeA, 
		string nodeB){
	set<string> visited;
	auto graph = BuildGraph(edges);
	for (auto it:graph){
		cout << it.first << ": ";
		for (auto i: it.second){
			cout << i << ' ';
		}
		cout << endl;
	}
	return hasPath(graph, nodeA, nodeB, visited);
}

bool hasPath(map<string, vector<string>>& graph, string src, string dst, set<string>& visited){	
	if (src == dst){ 
		return true;
	}
	if (visited.find(src) != visited.end()){
		return false;
	} 

	visited.insert(src);
	
	for (auto& n:graph[src]){
		if (hasPath(graph, n, dst, visited) == true){
			return true;
		} 		
	}
	return false;
}

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
	edges.push_back(make_pair("i","j"));
	edges.push_back(make_pair("k","i"));
	edges.push_back(make_pair("m","k"));
	edges.push_back(make_pair("k","l"));
	edges.push_back(make_pair("o","n"));
	cout << UndirectedGraph(edges, "i", "j") << endl;
	return 0;
}