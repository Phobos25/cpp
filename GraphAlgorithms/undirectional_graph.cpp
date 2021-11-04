#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

map<string, vector<string>> BuildGraph(vector<pair<string, string>>& edges);
bool HasPath(map<string, vector<string>> graph, string src, string dst);
	
bool UndirectedGraph(
		vector<pair<string, string>>& edges, 
		string nodeA, 
		string nodeB){
	auto graph = BuildGraph(edges);
	for (auto it:graph){
		cout << it.first << ": ";
		for (auto i: it.second){
			cout << i << ' ';
		}
		cout << endl;
	}
	return HasPath(graph, nodeA, nodeB);
}

bool HasPath(map<string, vector<string>> graph, string src, string dst){
	
}


map<string, vector<string>> BuildGraph(vector<pair<string, string>>& edges){
	map<string, vector<string>> graph;
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
	UndirectedGraph(edges, "i", "j");
	return 0;
}