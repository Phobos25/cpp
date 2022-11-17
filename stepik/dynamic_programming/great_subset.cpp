// Наибольшая общая подпоследовательность
// Даны две последовательности. Нужно найти их наибольшую об-
// щую подпоследовательность, то есть совпадающую подпоследо-
// вательность наибольшей длины.
// Найдите длину наибольшей общей подпоследовательности по-
// следовательностей.
// 1 2 3 4
// 3 1 4 5 3 1 2 4

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 4;
    int m = 8;
    vector<vector<int>> d(n+1, vector<int>(m+1));
    vector<int> a{1, 2, 3, 4};    
    vector<int> b{3, 1, 4, 5, 3, 1, 2, 4};

    for (size_t i = 0; i <= n; i++){
        d[i][0] = 0;
    }
    for (size_t j = 0; j <= m; j++){
        d[0][j] = 0;
    }
    
    for (size_t i = 1; i <= n; i++){
        for (size_t j = 1; j <= m; j++){
           d[i][j] = max(d[i-1][j], d[i][j-1]);
           if (a[i-1] == b[j-1]) d[i][j] = max(d[i][j], d[i-1][j-1]+1);
        }        
    }
    cout << d[n][m] << endl;
    return 0;
}