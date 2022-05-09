// рассмотрим задачу о коммивояжере.
// коммивояжер должен обойти все города, и сделать это за наименьшее расстояние
// элементы в двумерном массиве --- это расстояние между городами
// a[i][j] --- расстояние между i-м и j-м городом
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

template <typename T>
ostream& operator << (ostream& stream, const vector<T>& vec){
  for (auto& v:vec){
    stream << v << ' ';
  }
  return stream;
}

vector<vector<int>> readinput(string filename){
  ifstream input(filename);  
  int n;     
  vector<vector<int>> result;
  input >> n;

  while (input){    
    vector<int> vec;
    for (int i=0; i<n; ++i){
      int element;
      input >> element;
      vec.push_back(element);
      input.ignore(1);
    }
    result.push_back(vec);
  }
  cout << "file read:" << endl;
  cout << n << endl;
  for (auto& v: result){
    cout << v;
    cout << endl;
  }  
  return result;
}

int main(){
  vector<vector<int>> a = readinput("salesman.in");
  cout << "number of cities: "<<a.size() << endl;

  vector<int> vec;
  for (int i = 0; i<a.size(); ++i){
    vec.push_back(i);
  }

  vector<vector<int>> result;
  int n = vec.size();
  do {
    result.push_back(vec);    
  }while (next_permutation(vec.begin(), vec.end()));
  

  int min = INT_MAX;
  auto min_vec = result[0];  
  for (auto& d:result){
      int count = a[0][d[0]];      
      for (int i=0; i< d.size() -1; ++i){
          count += a[d[i]][d[i+1]];
      }
      
      if (count <= min){
          min = count;
          min_vec = d;
      }
  }
  cout << "minimal distance: " <<min << endl;
  cout << min_vec;
  cout << endl;                         
  return 0;
}