// Write a function "canConstruct(target, wordBank)" that accepts
// a target string and an array of strings

// The function should return a boolean indicating whether or not the
// "target" can eb constructed by concatenating elements of the
// "wordBank" array.

// You may reuse elements of "wordBank" as many times as needed.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// O(m^2*n) time
// O(m) space

bool CanConstruct(string target, vector<string> wordBank){
    vector<bool> table(target.length()+1, false);
    table[0] = true;

    for (int i=0; i<=target.length(); ++i){
        if (table[i] == true){
            for (auto& word:wordBank){
                 if (target.substr(i, word.length()) == word){
                     table[i+word.length()] = true;
                 }
            }
        }
    }
    return table[target.length()];
} 

int main() {
    cout << CanConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}) << endl;
    cout << CanConstruct("skateboard", vector<string> {"bo", "rd", "ate", "t", "ska", "sk", "boat"}) << endl;
    cout << CanConstruct("enterapotentpot", vector<string> {"a", "p", "ent", "enter", "ot", "o", "t"}) << endl;
    cout << CanConstruct("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", 
    vector<string> 
    {"e", 
    "ee", 
    "eee", 
    "eeee", 
    "eeeee", 
    "eeeeee"}) << endl;
    return 0;
}