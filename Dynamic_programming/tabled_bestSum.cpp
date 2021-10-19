// Write a function 'bestSum(targetSum, numbers' that takes in a 
// targetSum and an array of numbers as arguments

// The function should return an array containing the shortest
// combination of numbers that add up to exactly the targetSum

// if there is a tie for shortest combination, you may return any
// one of the shortest

#include <iostream>
#include <vector>

using namespace std;

vector<int> BestSum(int targetSum, vector<int> numbers) {
    vector<vector<int>> table (targetSum+1);
    table[0] = {{}};
    for (int i=0; i<=targetSum; ++i){
        if (table[i].size() != 0){
            for (auto& num: numbers){
                if(i+num <= targetSum){
                    vector<int> v;
                    // condition ? result_if_true : result_if_false
                    if (i != 0){
                        v = table[i];
                    }
                    v.push_back(num);
                    if ((table[i+num].size() == 0) || (v.size() < table[i+num].size())){
                        table[i+num] = v;    
                    }               
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

int main(){
    
    auto result1 = BestSum(7, {5,3,4,7});
    PrintContainer(result1);
    cout << endl;
    
    auto result2 = BestSum(8, {2,3,5});
    PrintContainer(result2);
    cout << endl; 

    auto result3 = BestSum(8, {1,4,5});
    PrintContainer(result3);
    cout << endl;

    auto result4 = BestSum(100, {1,2,5,25});
    PrintContainer(result4);
    cout << endl;

    return 0;
}