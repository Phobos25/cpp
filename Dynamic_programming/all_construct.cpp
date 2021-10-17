// Write a function 'AllConstruct(target, wordBank)' that accepts
// a target string and an array of strings.

// The function should return a 2D array containing all of the ways
// that the 'target' can be constructed by concatenating elements of
// of the 'wordBank' array. Each element of the 2D array should 
// represent one combination that constructs the 'target'.

//  you may reuse elements of 'wordBank' as many times as needed

// One distinctive difference of this problem is it doesn't benefit from meoization
// since it still needs to return all possible combination. 
#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// AllConstruct
// m = target.length
// n = wordBank.length

// brute force
// O(n^m) time complexity
// O(m) space complexity

// memoized
// O(n^m) time complexity
// O(m) space complexity

vector<deque<string>> AllConstruct(string target, vector<string> wordBank){
  static map<string, vector<deque<string>>> memo;
  if (memo.find(target) != memo.end()){
    return memo[target];
  }
  if (target == ""){
    return {{}};
  }
  vector<deque<string>> result;
  for (auto& word: wordBank){    
    if (target.find(word) == 0){
      auto suffix = target.substr(word.length());      
      auto suffixWays = AllConstruct(suffix, wordBank);      
      for (auto& way:suffixWays){
        way.push_front(word);
      }
      
      for (size_t i = 0; i< suffixWays.size(); ++i){        
          result.push_back(move(suffixWays[i]));
      }

    }
  }
  memo[target] = result;
  return result;
} 

void PrintResult(const vector<deque<string>>& container) {
  cout << container.size() << endl;
  for (const auto& v:container){
      for (const auto& it:v){
        cout << it << " ";
      }
      cout << endl;
  }    
}

int main(){
    auto result1 = AllConstruct("purple", vector<string>{"purp", "p", "ur", "le", "purpl"});
    PrintResult(result1);

    auto result2 = AllConstruct("abcdef", vector<string>{"ab", "abc", "cd", "def", "abcd", "ef", "c"});
    PrintResult(result2);

    auto result3 = AllConstruct("skateboard", vector<string>{"bo", "rd", "ate", "t", "ska", "sk", "boar"});
    PrintResult(result3);

    auto result4 = AllConstruct("aaaaaaaaaaaaaaaaz", vector<string>{"a", "aa", "aaa", "aaaa", "aaaaa"});
    PrintResult(result4);
    return 0;
}