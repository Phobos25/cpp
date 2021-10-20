// Write a function 'countConstruct(target, wordBank' that 
// accpets a target string an an array of __cpp_raw_strings

// The function should return the number of ways that the 'target'
// can be constructed by concatenating elemenst of the 'wordBank' array

// You may reuse elements of 'wordBank' as many times as ne

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// m - target
// n - wordBank.length

// O(m^2*n) time
// O(m) space

int CountConstruct(string target, vector<string> wordBank){
    vector<int> table(target.length()+1, 0);
    table[0] = 1;
    for (int i=0; i<=target.length(); ++i){
        for (auto& word:wordBank){
            if (target.substr(i, word.length()) == word){
                table[i+word.length()] += table[i];
            }
        }
    }

    return table[target.length()];
}
int main(){
    cout << CountConstruct("purple", {"purp", "p", "ur", "le", "purpl"}) << endl;
    cout << CountConstruct("abcdef", {"ab", "abc", "cd", "def", "abcd"}) << endl;
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
}