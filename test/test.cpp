#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <future>
#include <map>

using namespace std;

using mymap = map<int, int>;

void printIt(const mymap& m) {
    for (auto const &[k, v] : m)
        std::cout << k << ":" << v << " ";
    std::cout << std::endl;
}

// mymap operator += (mymap& lhs, mymap& rhs){
// 	for (auto& [key, value]:rhs){
// 		if (lhs.count(key) != 0){
// 			lhs[key] += value;
// 		} else {
// 			lhs[key] = value;
// 		}
// 	}
// 	return lhs;
// }

int main() {
    mymap foo{ {1, 11}, {2, 12}, {3, 13} };
    mymap bar{ {2, 20}, {3, 30}, {4, 40} };
    printIt(foo);
    printIt(bar);    
    for (auto& [key, value]:bar){
    	if (foo.count(key) != 0){
    		foo[key] += value;
    	} else {
    		foo[key] = value;
    	}
    }
    printIt(foo);
    return 0;
}