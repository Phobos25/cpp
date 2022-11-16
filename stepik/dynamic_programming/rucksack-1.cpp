// Задача о рюкзаке
// Имеется n предметов, для которых известны веса wi и стоимости
// ci, i = 1, . . . , n. Рюкзак вмещает вес не более W . Нужно набрать
// в него предметы максимальной суммарной стоимости.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    //  vector<int> c {10, 20, 30};
    //  vector<int> w {2, 5, 10};
    //  int W = 10;

    
    vector<int> w{2, 5, 10};
    vector<int> c{10, 20, 30};

    int n = 3;
    int W = 10;

    vector<vector<int>> d(n+1, vector<int>(W+1));
    
    for (int j=0;j<=W; ++j){
        d[0][j] = 0;
    }
    for (int i=1; i<= n; ++i){
        for(int j=0; j<= W; ++j){
            d[i][j] = d[i-1][j];
            if (j - w[i] >= 0) d[i][j] = max(d[i][j], d[i-1][j-w[i]] + c[i]);
        }
    }
    for (int i=1; i<= n; ++i){
        for(int j=0; j<= W; ++j){            
            cout << d[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}