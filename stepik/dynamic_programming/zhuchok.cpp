// Задача про жучка
// Имеется прямоугольное поле размера n × m. Поле разделено на
// единичные клетки. В левой верхней клетке сидит жучок. Он мо-
// жет перемещаться по полю ходами вправо или вниз на одну клет-
// ку. Для каждой клетки задано целое положительное число — ко-
// личество бонусов, которое получит жучок при проходе через эту
// клетку. Нужно добраться в правую нижнюю клетку, собрав как
// можно больше бонусов. Бонусы в начальной и конечной клетках
// жучок тоже собирает. Бонусы ниже: 
// 5 3 2 2
// 2 1 7 3
// 4 3 1 2

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> p;

void recout (int i, int j){
    if (i == 0 && j == 0) return;        
    if (p[i][j] == 0){
        recout (i-1, j);
        cout << 'D';
    }
    if (p[i][j] == 1){
        recout (i, j-1);
        cout << 'R';
    }
}

int main() {
    int n = 4;
    int m = 5;
    vector<vector<int>> d(n, vector<int>(m));
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i){
        vector<int> temp;
        for (int j = 0; j < m; ++j){
            cin >> a[i][j];            
            temp.push_back(0);
        }
        p.push_back(temp);
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j){
            d[i][j] = a[i][j];
            if (i > 0 && d[i-1][j] + a[i][j] > d[i][j]) {
                d[i][j] = d[i-1][j] + a[i][j];
                p[i][j] = 0;
            }                
            if (j > 0 && d[i][j-1] + a[i][j] > d[i][j]){
                d[i][j] = d[i][j-1] + a[i][j];
                p[i][j] = 1;
            }                
        }
    cout << d[n-1][m-1] << endl;
    recout(n-1, m-1);
    return 0;
}
