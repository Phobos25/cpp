// Задача о замощении полосы доминошками
// Имеется полоса размера 2 × n. Нужно найти число способов за-
// мостить ее доминошками размера 1 × 2. Доминошки не должны
// пересекаться и выходить за пределы полосы.

#include <iostream>
#include <vector>

using namespace std;

int ans = 0;

void rec(int sum, int n){
    if (sum > n) return;
    if (sum == 0){
        ans++;
        return;
    }
    rec(sum + 1, n);
    rec(sum + 2, n);
}

int main(){
    int n = 10;
    vector<long long> d (n+1);
    d[0] = d[1] = d[2] = 1; 
    for ( int i=3; i<=n+1; ++i){
        d[i] = d[i-1] + d[i-3];
    }
    cout << d[n] << endl;
    return 0;    
}