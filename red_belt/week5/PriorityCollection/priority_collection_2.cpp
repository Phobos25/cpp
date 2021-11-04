#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <map>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = int;/* тип, используемый для идентификаторов */

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
    data[id_] = move(object);
    priority[id_] = 0;
    prior_item[0].insert(id_);       
    return id_++;
  };

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin){  
    while (range_begin != range_end){      
      *ids_begin = Add(move(*range_begin));
      
      cout << *ids_begin << endl;      
      
      ++range_begin;      
      ++ids_begin;
    }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
    if (data.count(id) != 0){
      return true;
    } else {
      return false;
    }
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const{
    return data[id];    
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id){            
    auto prev_prior = priority[id];
    ++priority[id];
    prior_item[priority[id]].insert(id);
    auto it = prior_item[prev_prior].find(id);    
    if (it != prior_item[prev_prior].end()){
      prior_item[prev_prior].erase(it);
    }
    CheckIfEmpty(prev_prior);
  }
  
  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const{
    int last_key = prior_item.rbegin()->first;    
    int id = *prior_item.at(last_key).rbegin();
    return make_pair(data[id], id);
  }
  
  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax(){    
    auto id = prior_item[prior_item.rbegin()->first].rbegin();
    Id id2 = *prior_item[prior_item.rbegin()->first].rbegin();    
    auto result = make_pair(move(data[*id]), move(priority[id2]));    
   
    int key = prior_item.rbegin()->first;
    prior_item[key].erase(*id);
    CheckIfEmpty(key);    
    
    return result;
  }
  
  void CheckIfEmpty(int priority){
    if (prior_item[priority].empty()){
      prior_item.erase(priority);
    }
  }  
  
private:  
  map<Id, T> data;
  map<Id, int> priority;
  map<int, set<Id>> prior_item;
  Id id_ = 0;
  // Приватные поля и методы  

};

class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");
  vector<StringNonCopyable> colors;
  colors.push_back("green");
  colors.push_back("blue");
  colors.push_back("orange");
  colors.push_back("purple");
  
  vector<int> ids;
  ids.push_back(white_id);
  ids.push_back(yellow_id);
  ids.push_back(red_id);
  auto it = find(ids.begin(), ids.end(), red_id);
  strings.Add(colors.begin(), colors.end(), it);
  cout << ids.size() << endl;  

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);  
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }  
  {
    const auto item = strings.PopMax();    
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
