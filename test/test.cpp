// Write a function 'hoSum(targetSum, numbers)' that takes in a 
// targetSum and an array of numbers as arguments

// The function should return an array containing any combination of
// elements that add up to exactly the targetSum

// if there is no combination that adds up to the targetSum, then
// return null

// if there are multiple combinations possible, you may return any 
// single one
#include <iostream>
#include <vector>

using namespace std;

// O(m^2*n) time
// O(m^2) space
vector<int> HowSum(int targetSum, vector<int> numbers){
    vector<vector<int>> table (
        targetSum+1, 
        vector<int>{INT16_MIN});
    table[0] = {{}};
    for (int i=0; i<=targetSum; ++i){
        if (table[i][0] != INT16_MIN){
            for (auto& num:numbers){
                if ((i + num) <= targetSum){                    
                    if (i == 0){
                        table[i+num].clear();
                    } else {
                        table[i+num] = table[i];
                    }                   
                    table[i+num].push_back(num);
                }                
            }
        }
    }

    return table[targetSum];
}

template <typename T>
void PrintContainer(T container) {
  for (auto it: container){
      cout << it << " ";
  }
}

int main() {
    auto result1 = HowSum(7, {2,3});
    PrintContainer(result1);
    cout << endl;
    // int targetSum = 7;
    // vector<vector<int>> table (
    //       targetSum+1, 
    //       vector<int>{INT16_MIN});   
    // table[0] = {{}};    
    // cout << table[0].size() << endl;
    // cout << table[0][0] << endl;
    // return 0;
}