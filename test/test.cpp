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
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
  // Напишите реализацию функции,
  set<char> s;
  map<set<char>, size_t> group;
  // тут можно использовать int вместо vector<String>, но туда пихать номер
  // группы слов, т.е. мне нужна еще 1 переменная-счетчки, которая будет учитывать
  // номер группы стрингов
  size_t count = 0;
  vector<Group<String>> result; 

  for (const auto& word:strings){
    s.clear();
    for (const auto& letter:word){
      if (s.count(letter) == 0){
        s.insert(letter);        
      } 
    }        
    // TODO сделать проверку
    if (group.count(s) == 0){
      group[s] = count++;
    }    

    if (result.size() >= count){
      result[group[s]].push_back(word);
    } else {      
      result.push_back({word});
    }
  }  

  // for (auto& [key, value]:group){
  //   Group<String> vec;
  //   for (auto& v:value){
  //     vec.push_back(move(v));
  //   }
  //   result.push_back(vec);    
  // }
  
  return result;
  // использовав не более 1 копирования каждого символа
}

int main (){
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c", "d", "cba"};
  auto groups = GroupHeavyStrings(strings);
  for (auto vec:groups){
    for (auto v:vec){
      cout << v << ' ';
    }
    cout << endl;
  }
  return 0;
}