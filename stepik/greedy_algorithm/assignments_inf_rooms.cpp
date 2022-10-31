/*
 * Задача о выборе заявок с бесконечным числом
 * аудиторий.
 *
 * Рассмотрим модифицированный вариант задачи о
 * выборе заявок. Имеется бесконечное число
 * аудиторий и nnn заявок на проведение занятий в
 * них. Каждая заявка - это временной интервал
 * [li,ri)[l_i, r_i)[li​,ri​), причем левая граница
 * включается в интервал, а правая - нет.
 * Нужно распределить по аудиториям все заявки,
 * чтобы занятия в каждой аудитории не
 * пересекались по времени, и при этом
 * использовалось наименьшее число аудиторий.
 *
 * Входные данные

В первой строке задано целое число n -
количество заявок. Следующие n строк описывают
заявки: i-я строка содержит два целых числа -
l_i​ и r_i​, li < r_i​.

Выходные данные

Выведите одно целое число - наименьшее число
аудиторий, достаточное для удовлетворения всех
заявок.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool sortbyfirst(const pair<int, int>& lhs,
                 const pair<int, int>& rhs){
  return lhs.first<rhs.first;
}

int main(){
  fstream input("request3.in");
  int n;
  input >> n;
  vector<pair<int,int>> asg(n);
  for (int i = 0; i<n; ++i){
    int l, r;
    input >> l >> r;
    asg[i] = make_pair(l,r);
  }
  sort(asg.begin(), asg.end(), sortbyfirst);
  vector<int> room;
  bool flag = 0;
  room.push_back(asg[0].second);
  for (int i = 1; i < n; ++i){
    flag = 0;
    for (unsigned j = 0; j < room.size(); ++j){
      if (asg[i].first >= room[j]){
        room[j] = asg[i].second;
        flag = 1;
        break;
      }
    }
    if (flag == 0){
      room.push_back(asg[i].second);
    }
  }
  cout << room.size() << endl;

  return 0;
}





