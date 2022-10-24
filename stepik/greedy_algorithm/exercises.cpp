/*
 * Задача о расписании. У программиста есть n заказов.
 * Для каждого заказа известен дедлайн di_ - срок,
 * до которого нужно выполнить заказ, и стоимость
 * заказа ci​. На выполнение каждого заказа
 * требуется один день. Программист начинает
 * работать с 1-го дня, и если у заказа дедлайн di​,
 * то этот заказ нужно выполнить до конца di​-го дня.
 * Например, если дедлайн равен 1, то программист
 * успеет выполнить этот заказ в первый день.
 * Нужно составить оптимальное расписание -
 * определить, какие заказы программист может
 * выполнять и в каком порядке, чтобы максимизировать
 * суммарную стоимость выполненных заказов.

* Входные данные
* В первой строке задано число n - количество заказов
* Следующие n строк содержат описания заказов: i-я
* строка содержит два целых числа - дедлайн di​ и
* стоимость ci​.
*
* Выходные данные
* Выведите одно целое число - максимальную суммарную
* стоимость выполненных заказов.
* Пример входных данных
* 5
* 2 5
* 2 4
* 5 3
* 1 2
* 3 1
*
* Пример выходных данных
* 13
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


bool sortbysec(const pair<int,int> &a,
               const pair<int,int> &b)
{
  // descending
  return (a.second > b.second);
}


int main() {
  ifstream input("schedule.in");
  int n = 0;
  input >> n;
  vector<int> d(n);
  vector<int> c(n);
  for (int i =0; i < n; ++i){
    input >> d[i] >> c[i];
  }
  input.close();

  int TMAX = *max_element(begin(d), end(d));
  vector<bool> used(TMAX, false);

  long long s = 0;

  vector<pair<int, int>> target(n);
  for (unsigned i = 0; i < n; ++i){
    target[i] = make_pair(d[i], c[i]);
  }
  //  сортировка пары векторов по стоимости (второму вектору в парке)
  sort(target.begin(), target.end(), sortbysec);

  for (int i = 0; i< n; ++i){
    int k = target[i].first;
    while (k >= 1 && used [k]){
      --k;
    }
    if (k==0){
      continue;
    }
    used[k] = true;
    s += target[i].second;
  }
  cout << s << endl;
  ofstream output("output.txt");
  output << s;
  output.close();
  return 0;
}


