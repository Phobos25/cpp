#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>

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

// Объявляем еще один шаблон, для удобства
template <typename String>
<<<<<<< HEAD
using Key = String;

// данную шаблонную функцию мы используем вместо
// множества, чтобы не было повторов и было отсортировано
template <typename String>
Key<String> ComputeStringKey(const String& string){
  String chars = string;
  sort (begin(chars), end(chars));
  chars.erase((begin(chars), end(chars)), end(chars));
  return chars;
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
>>>>>>> a5e036e5abacbffa6397e2f47cda2fdd771fadc1
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {  
  map<Key<String>, Group<String>> groups_map;
  for (String& string: strings){
    groups_map[ComputeStringKey(string)].push_back(move(string));
  }
  vector<Group<String>> groups;
  for (auto& [key, group] : groups_map){
    groups.push_back(move(group));
  }
  return groups;
}

void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);
  return 0;
}
