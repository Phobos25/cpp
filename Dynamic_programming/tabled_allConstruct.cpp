// Write a function 'AllConstruct(target, wordBank)' that accepts
// a target string and an array of strings.

// The function should return a 2D array containing all of the ways
// that the 'target' can be constructed by concatenating elements of
// of the 'wordBank' array. Each element of the 2D array should 
// represent one combination that constructs the 'target'.

//  you may reuse elements of 'wordBank' as many times as needed

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// O(n^m) time
// O(n^m) space
vector<vector<string>> AllConstruct(string target, vector<string> wordBank) {
    map<int, vector<vector<string>>> table;
    for (int i=0; i<=target.length(); ++i){
        table[i] = {};
    }
    
    table[0] = {{}};
    for (int i=0; i<target.length(); ++i){
        for (string& word:wordBank){
            if (target.substr(i, word.length()) == word){                                
                table[i+word.length()]
            }
        }
    }
}

int main() {

    return 0;
}