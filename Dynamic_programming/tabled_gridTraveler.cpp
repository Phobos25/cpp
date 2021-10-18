// Say that you are a traveler on a 2D grid. You begin
// in the top-left corner and your goal is to travel to the
// bottom-right corner. You may only move down or right.

#include <iostream>
#include <vector>

using namespace std;

int GridTraveler(int m, int n){
    // create 2d vector
    vector<vector<int>> grid(
                m+1,
                vector<int> (n+1, 0));
    grid[1][1] = 1;
    for (int i=0; i<=m; ++i){
        for (int j=0; j<=n; ++j){
            auto current = grid[i][j];
            if (j+1 <= n ){
                grid[i][j+1] += current;
            }
            if (i+1 <= m){
                grid[i+1][j] += current;
            }            
        }
    }
    return grid[m][n];
}
int main() {   
    cout << GridTraveler(1,1) << endl;
    cout << GridTraveler(2,3) << endl;
    cout << GridTraveler(3,2) << endl;
    cout << GridTraveler(3,3) << endl;
    cout << GridTraveler(10,10) << endl;
    return 0;
}