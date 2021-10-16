/*
 * main.cpp
 *
 *  Created on: Oct 16, 2021
 *      Author: igorpetrov
 */

#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

vector<deque<string>> AllConstruct(string target, vector<string> wordBank){
  if (target == ""){
    return {};
  }
  vector<deque<string>> result;
  for (auto& word: wordBank){
    if (target.find(word) == 0){
      auto suffix = target.substr(word.length());
      auto suffixWays = AllConstruct(suffix, wordBank);
      for (auto& way:suffixWays){
        way.push_front(word);
      }
      move(suffixWays.begin(), suffixWays.end(),result.begin());
    }
  }
  return result;
}

int main(){
  auto result =  AllConstruct("purple", vector<string>{"purp", "p", "ur", "le", "purpl"});
  for (const auto& v:result){
    for (const auto& it:v){
      cout << it << " ";
    }
    cout << endl;
  }
  cout << "end program" << endl;
  return 0;
}



