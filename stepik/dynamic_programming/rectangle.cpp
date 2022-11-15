// Суммы в прямоугольниках
// Имеется поле n × m, разбитое на единичные клетки. В клет-
// ках записаны числа. Нам поступают запросы. Каждый запрос
// — это некоторый прямоугольник со сторонами, параллельными
// осям координат. Нужно для каждого прямоугольника определить
// сумму чисел в нём

//  1 3 7 -1 7 11
//  2 6 5  1 1  3
// -3 0 2  0 3  8
//  5 1 3  1 4  7
//  6 1 -2 2 1  0

#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n+1, vector<int> (m+1));
    vector<vector<int>> s(n+1, vector<int> (m+1));
    for (int i=0; i<n+1; ++i){
        s[i][0] = 0;
    }

    for (int i=1; i<=n; ++i){
        for (int j=1; j<=m; ++j){
            cin >> a[i][j];
            s[i][j] = s[i][j-1] + a[i][j];
        }
    }
    for (int i=1; i<n+1; ++i){
        for (int j=1; j<m+1; ++j){
            cout << s[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}

    

