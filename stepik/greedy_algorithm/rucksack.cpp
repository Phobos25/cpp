/*
*  Задача о рюкзаке
* Вор пробрался на склад, на котором есть n предметов. Для каж-
* дого предмета известны его вес wi и стоимость ci. У вора есть
* рюкзак, который вмещает суммарный вес не более W . Вор хочет
* набрать в рюкзак предметы максимальной суммарной стоимости.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool sortbyvalue(const pair<int,int> &lhs,
                 const pair<int,int> &rhs){
  // descending
  return (lhs.first/lhs.second > rhs.first/rhs.second);
}


int main() {
//  vector<int> c {10, 20, 30};
//  vector<int> w {2, 5, 10};
//  int W = 10;

  vector<int> c {10, 20, 30};
  vector<int> w {2, 5, 10};
  int W = 12;

//  vector<int> c {12, 15, 18};
//  vector<int> w {3, 3, 9};
//  int W = 10;

//  vector<int> c {10, 12};
//  vector<int> w {2, 3};
//  int W = 4;
//
  vector<pair<int, int>> target(c.size());
  for (unsigned i = 0; i < target.size(); ++i){
    target[i] = make_pair(c[i], w[i]);
  }
  // сортируем наши значения по цене на 1 кг
  sort(target.begin(), target.end(), sortbyvalue);

  for (const auto& [first, second]:target){
    cout << first << ' ' << second << endl;
  }
  int cur_w = 0;
  int price = 0;
//  дискретный случай
  for (unsigned i = 0; i< c.size(); ++i){
    cur_w += target[i].second;

    if (cur_w >= W){
      break;
    }
    price += target[i].first;
  }
  cout << "дискретный случай: " <<price << endl;
  cur_w = 0;
  price = 0;
//  теперь рассмотрим непрерывный случай
  for (unsigned i = 0; i< c.size(); ++i){
      cur_w += target[i].second;

      if (cur_w >= W){
        float part_w = static_cast<float>(W - cur_w + target[i].second)/target[i].second;
        price += part_w * target[i].first;

        break;
      }
      price += target[i].first;
    }
  cout << "непрерывный случай: " << price << endl;

  return 0;
}

