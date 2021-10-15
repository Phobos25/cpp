
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// CanConstruct
// m = target.length
// n = wordBank.length

// brute force
// O(n^m * m) time complexity
// O(m^2) space complexity

// memoized
// O(n * m^2) time complexity
// O(m^2) space complexity
bool canConstruct(string target, vector<string> wordBank){
    static map<string, bool> memo;
    if (memo.find(target) != memo.end()){
        return memo[target];
    }
    if (target == ""){
        return true;
    }
    for (auto& word: wordBank){
        if (target.find(word) == 0){
            string suffix = target.substr(word.length());
            if (canConstruct(suffix, wordBank)){
                memo[target] = true;
                return true;
            }
        }
    }
    memo[target] = false;
    return false;
}

int main() {    
   
    cout << canConstruct("abcdef", vector<string> {"abc", "d", "bc", "def"}) << endl;
    cout << canConstruct("skateboard", vector<string> {"bo", "rd", "ate", "t", "ska", "sk", "boat"}) << endl;
    cout << canConstruct("enterapotentpot", vector<string> {"a", "p", "ent", "enter", "ot", "o", "t"}) << endl;
    cout << canConstruct("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", 
    vector<string> 
    {"e", 
    "ee", 
    "eee", 
    "eeee", 
    "eeeee", 
    "eeeeee"}) << endl;
    return 0;
}