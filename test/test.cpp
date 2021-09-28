#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
<<<<<<< HEAD
using Key = String;

template <typename String>
Key<String> ComputeStringKey (const String& string){
  String chars = string;
  sort(begin(chars), end(chars));
  chars.erase(unique(begin(chars), end(chars)), end(chars));
  return chars;
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
  map<Key<String>, Group<String>> groups_map;
  for (String& string:strings){
    groups_map[ComputeStringKey(string)].push_back(move(string));
  }
  vector<Group<String>> groups;
  for (auto& [key, group]:groups_map){
    groups.push_back(move(group));
  }
  return groups;
=======
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
  // Напишите реализацию функции,
  set<char> s;
  map<set<char>, int> group;

  for (const auto& word:strings){
    s.clear();
    for (const auto& letter:word){
      if (s.count(letter) == 0){
        s.insert(letter);
      }
    }
    ++group[s];
  }
  
  cout << group.size();  

  vector<Group<String>> result;
  return result;
  // использовав не более 1 копирования каждого символа
>>>>>>> parent of 38dc16c... trying heavy strings
}

int main (){
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c", "d", "cba"};
  auto groups = GroupHeavyStrings(strings);
  return 0;
}

