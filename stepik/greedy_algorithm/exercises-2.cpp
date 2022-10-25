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
#include <fstream>
#include <algorithm>

using namespace std;

bool sortbysec(const pair<int,int> &a,
               const pair<int,int> &b)
{
  // ascending
  return (a.second < b.second);
}


int main() {
  fstream input("request2.in");
  int n = 0;
  input >> n;
  int l, r;
  vector<pair<int, int>> apps(n);
  for (int i=0; i<n; ++i){
    input >> l >> r;
    apps[i] = make_pair(l,r);
  }

  sort(apps.begin(), apps.end(), sortbysec);
  //  исходим из того, что первая заявка проходит автоматически
  int cnt = 1;
  int last = 0;
  vector<pair<int, int>> a;
  //  сохраняем первую заявку
  a.push_back(apps[0]);

  for (int i = 0; i< n; ++i){
    if (apps[i].first >= apps[last].second){
      ++cnt;
      last = i;
      a.push_back(apps[i]);
    }
  }
  cout << "Количество заявок: " <<cnt << endl;
//  for (int i = 0; i<cnt; ++i){
//    cout << a[i].first << ' ' << a[i].second << endl;
//  }
  input.close();
  return 0;
}
