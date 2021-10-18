// Write a function "canSum(targetSum, numbers)" that takes in a targetSum and an
// array of numbers as arguments.

//  the function should return a boolean indicating whether or not it
// is possible to generate the targetSum using numbers from the array.

//  You may use an element of the array as many times as needed.

// You may assume that all input numbers are nonnegative.

#include <iostream>
#include <vector>

using namespace std;

// O(m*n) time
// O(m) space

bool CanSum(int target, vector<int> numBank){
    vector<bool> table(target+1, false);
    table[0] = true;
    for (int i=0; i<= table.size(); ++i){
        if (table[i] == true){
            for (auto& num:numBank){
                if ((i+num) <= table.size() ){
                    table[i+num] = true;
                }                
            }
        }
    }

    return table[target];
}

int main() {
    cout << CanSum(7, {5, 3, 4}) << endl;
    cout << CanSum(7, {5, 3, 4, 7}) << endl;
    cout << CanSum(7, {2, 4}) << endl;
    cout << CanSum(8, {2, 3, 5}) << endl;
    cout << CanSum(300, {7, 14}) << endl;

    return 0;
}