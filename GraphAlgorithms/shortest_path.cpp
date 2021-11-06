#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <queue>
using namespace std;

template <typename T>
int FindShortestPath(map <T, vector<T>>& graph, T start, T finish){    
    set <T> visited;
    queue<pair<T, int>> que;
    int count = 0;
    que.push(make_pair(start, count));
    while (que.size() > 0){
        auto current = que.front(); 
        que.pop();
        auto node = current.first;
        auto distance = current.second;
        if (node == finish) {
        	return distance;
        }

        for (auto& neighbour : graph.at(node)){
            if (visited.find(neighbour) == visited.end()){
            	visited.insert(neighbour);
            	que.push(make_pair(neighbour, distance+1));	            	
            }            
        }
    }
    return -1;
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
    {
    	vector<pair<string, string>> edges; 
    	edges.push_back(make_pair("w","x"));
    	edges.push_back(make_pair("x","y"));
    	edges.push_back(make_pair("z","y"));
    	edges.push_back(make_pair("z","v"));
    	edges.push_back(make_pair("w","v"));
    	auto graph = BuildGraph(edges);	
    	string start = "w";
    	string finish = "z";
    	cout << FindShortestPath(graph, start, finish) << endl; // 2
    }

	{
		vector<pair<string, string>> edges;	
		edges.push_back(make_pair("w", "x"));
		edges.push_back(make_pair("x", "y"));
		edges.push_back(make_pair("z", "y"));
		edges.push_back(make_pair("z", "v"));
		edges.push_back(make_pair("w", "v"));
		auto graph = BuildGraph(edges);
		string start = "y";
		string finish = "x";
		cout << FindShortestPath(graph, start, finish)<<endl; // 1
	}

	{
		vector<pair<string, string>> edges;	
		edges.push_back(make_pair("a", "c"));
		edges.push_back(make_pair("a", "b"));
		edges.push_back(make_pair("c", "b"));
		edges.push_back(make_pair("c", "d"));
		edges.push_back(make_pair("b", "d"));
		edges.push_back(make_pair("e", "d"));
		edges.push_back(make_pair("g", "f"));
		string start = "a";
		string finish = "e";
		auto graph = BuildGraph(edges);
		cout << FindShortestPath(graph, start,finish) << endl; // 3		
	}
	{
		vector<pair<string, string>> edges;	
		edges.push_back(make_pair("a", "c"));
		edges.push_back(make_pair("a", "b"));
		edges.push_back(make_pair("c", "b"));
		edges.push_back(make_pair("c", "d"));
		edges.push_back(make_pair("b", "d"));
		edges.push_back(make_pair("e", "d"));
		edges.push_back(make_pair("g", "f"));
		string start = "e";
		string finish = "c";
		auto graph = BuildGraph(edges);
		cout << FindShortestPath(graph, start,finish) << endl; // 2			

	}
	{
		vector<pair<string, string>> edges;	
		edges.push_back(make_pair("a", "c"));
		edges.push_back(make_pair("a", "b"));
		edges.push_back(make_pair("c", "b"));
		edges.push_back(make_pair("c", "d"));
		edges.push_back(make_pair("b", "d"));
		edges.push_back(make_pair("e", "d"));
		edges.push_back(make_pair("g", "f"));
		string start = "b";
		string finish = "g";
		auto graph = BuildGraph(edges);
		cout << FindShortestPath(graph, start, finish) << endl; // -1
	}	

	return 0;
}