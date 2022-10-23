/*
* Задача о выборе заявок
* Имеется аудитория и n заявок на проведение занятий в ней. Каж-
* дая заявка — это временной интервал [li, ri), причём, как обычно
* бывает при 0-индексации, левая граница включается, а правая —
* нет. Нужно выбрать наибольшее число заявок, чтобы они не пе-
* ресекались.
 */


#include <iostream>
#include <vector>

using namespace std;

int main() {
  // будем считать что входные данные уже отсортированы
  //  сортировка должна быть по времени окончания ri
  // [1, 5), [3, 6), [5, 7)
  vector<int> l {1, 3, 5};
  vector<int> r {5, 6, 7};
  vector<pair<int, int>> apps;
  //  исходим первая заявка проходит автоматически
  int cnt = 1;
  int last = 0;
  int n = l.size();
  //  сохраняем первую заявку
  apps.push_back(make_pair(l[0],r[0]));

  for (int i = 0; i< n; ++i){
    if (l[i] >= r[last]){
      ++cnt;
      last = i;
      apps.push_back(make_pair(l[i],r[i]));
    }
  }
  cout << "Количество заявок: " <<cnt << endl;
  for (int i = 0; i<cnt; ++i){
    cout << apps[i].first << ' ' << apps[i].second << endl;
  }
  return 0;
}
