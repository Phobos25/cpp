#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v{1,2,3,4,5};
    vector<int> vector_two;    
    auto it = find(v.begin(), v.end(), 4);
    cout << *it << endl;

    v.erase(it);
    vector_two.push_back(*it);
    cout << vector_two[0] << endl;
    
}