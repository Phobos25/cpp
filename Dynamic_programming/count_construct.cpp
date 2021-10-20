// Write a function 'countConstruct(target, wordBank' that 
// accpets a target string an an array of __cpp_raw_strings

// The function should return the number of ways that the 'target'
// can be constructed by concatenating elemenst of the 'wordBank' array

// You may reuse elements of 'wordBank' as many times as needed

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// CountConstruct
// m = target.length
// n = wordBank.length

// brute force
// O(n^m * m) time complexity
// O(m^2) space complexity

// memoized
// O(n * m^2) time complexity
// O(m^2) space complexity
int CountConstruct(string target, vector<string> wordBank){
    static map<string, int> memo;
    if (memo.find(target) != memo.end()){
        return memo[target];
    }
    if (target == ""){
        return 1;
    }
    int totalCount = 0;
    for (auto& word: wordBank){
        if (target.find(word) == 0){
            int numWaysForRest = CountConstruct(target.substr(word.length()), wordBank);
            totalCount += numWaysForRest;            
        }
    }

    memo[target] = totalCount;
    return totalCount;
}

int main(){
    cout << CountConstruct("purple", vector<string>{"purp", "p", "ur", "le", "purpl"}) << endl;
    cout << CountConstruct("abcdef", vector<string> {"abc", "d", "bc", "def"}) << endl;
    cout << CountConstruct("skateboard", vector<string> {"bo", "rd", "ate", "t", "ska", "sk", "boat"}) << endl;
    cout << CountConstruct("enterapotentpot", vector<string> {"a", "p", "ent", "enter", "ot", "o", "t"}) << endl;
    cout << CountConstruct("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", 
    vector<string> 
    {"e", 
    "ee", 
    "eee", 
    "eeee", 
    "eeeee", 
    "eeeeee"}) << endl;
    return 0;
    return 0;
}