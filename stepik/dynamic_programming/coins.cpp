// Задача о размене
// Имеются монеты n номиналов a1, a2, . . . , an и сумма s. Нуж-
// но набрать эту сумму наименьшим количеством монет. Можно
// использовать любое число монет каждого номинала.

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int MAX_SUM = 1e6;
vector<int> p(MAX_SUM+1);
vector<int> d(MAX_SUM+1);

void recout (int i){
    if (i==0) return;
    recout (i - p[i]);
    if (i-p[i] > 0) cout << "+";
    cout << p[i];
}

int main(){
    int n, s;
    cin >> n;    
    cin >> s;
    vector<int> a;
    for (int i=0; i<n; ++i){
        int l=0;
        cin >> l;
        a.push_back(l);
    }
    d[0] = 0;
    for (int i=1; i<=s; ++i){
        d[i] = numeric_limits<int>::max();
        for (int j =0; j<n; ++j){
            if (i - a[j] >= 0 && d[i-a[j]] + 1< d[i]){
                d[i] = d[i-a[j]] + 1;
                p[i] = a[j];
            }
        }
    }
    cout << d[s]<< endl;
    recout (s);
    return 0;
}