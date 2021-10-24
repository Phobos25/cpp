#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <map>

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
    prior_item[0].push_back(id_);    
    return ++id_;
  };

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin){    
    for (auto& it=range_begin; it< range_end; ++it){
      data[id_] = move(*it);
      ++id_;
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
    // по идее, я же могу испортить данные, которые получил через get
    // тогда и другой контейнер тоже должен исключить этот id
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id){
    auto id_to_promote = find(prior_item[priority[id]].begin(),
                              prior_item[priority[id]].end(),
                              id);
    cout << priority[id] << endl;
    prior_item[priority[id]+1].push_back(move(*id_to_promote));        
    ++priority[id];
  }
  
  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const{
    int last_key = prior_item.rbegin()->first;    
    int id = prior_item.at(last_key).back();
    return make_pair(data[id], id);
  }
  
  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax(){
    // int last_key = prior_item.rbegin()->first;
    int id = prior_item[prior_item.rbegin()->first].back();
    auto result = make_pair(move(data[id]), id);    
    priority.erase(id);
    prior_item[prior_item.rbegin()->first].pop_back();
    return result;
  }
  void PrintPriority(){
    for (auto& [key, value]:prior_item){
      cout << key << ": " << value.size() << endl;
    }
  }
private:
  map<Id, T> data;
  map<Id, int> priority;
  map<int, vector<Id>> prior_item;
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

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  strings.PrintPriority();
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  strings.PrintPriority();
  {
    const auto item = strings.PopMax();
    cout << item.first << " " << item.second << endl;
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
