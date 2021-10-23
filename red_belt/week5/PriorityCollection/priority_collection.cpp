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
    ++id_;
  };

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin);

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
    if (data.count(id) != 0){
      return true;
    } else {
      return false;
    }
  }
  // из-за того, что я использую словарь, тут все элекментарно
  // просто смотрим count по id

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
    prior_item[priority[id]+1].push_back(*id_to_promote);
    prior_item[priority[id]].erase(id_to_promote);
    ++priority[id];
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const{
    int last_key = prior_item.rbegin()->first;
    int id = prior_item[last_key].back();
    return make_pair(data[id], id);
  }
  // тут по сложнее. мне надо найти объект с максимальным приоритет
  // следовательно надо искать по приортитету, который у меня является
  // значением. поэтому придется итерироваться по всему диапазон
  // тут будет линейная сложность 10^6. но это не так уж и много

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax(){
    auto last_key = prior_item.rbegin()->first;
    int id = prior_item[last_key].back();
    auto result = make_pair(data[id], id);
    data.erase(id);
    priority.erase(id);
    prior_item[last_key].pop_back();
    return result;
  }

private:
  map<Id, T> data;
  map<Id, int> priority;
  map<int, vector<Id>> prior_item;
  Id id_ = 0;
  // Приватные поля и методы
  // я ведь могу создать еще один контейнер в котором буду хранить приоритеты
  // можно что-то типа map<int, vector<id>>, тогда я могу при увеличении приоритета
  // добавить в вектор элемент по номеру id, конечно удаление объекта из вектора не очень
  // оптимально, но не линейная сложность
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
