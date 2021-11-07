#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <queue>
using namespace std;

// to put it into a set of visited cells
struct Cell{
    int r;
    int c;
    Cell(int r_ = 0, int c_ = 0){
        r = r_;
        c = c_;
    }
};

bool operator < (const Cell& lhs, const Cell& rhs){
    return make_pair(lhs.r, lhs.c) < make_pair(rhs.r, rhs.c);
}

bool Explore(vector<vector<string>>& grid, int r, int c, set<Cell>& visited){
    bool rowBounds = ((r>= 0) && (r < grid.size())) ? true : false;
    bool colBounds = ((c>= 0) && (c < grid[0].size())) ? true : false;
    if ((rowBounds != true) || (colBounds != true) ) {
        return false;
    }
    if (grid[r][c] == "W"){
        return false;
    }

    Cell pos(r, c);
    if (visited.find(pos) != visited.end()){
        return false;
    } else {
        visited.insert(pos);
    }     

    Explore(grid, r-1, c, visited);
    Explore(grid, r+1, c, visited);
    Explore(grid, r, c-1, visited);
    Explore(grid, r, c+1, visited);

    return true;
}

int IslandCount(vector<vector<string>>& grid){
    set<Cell> visited;
    int count = 0;
    for (int r=0; r<grid.size(); ++r){
        for (int c=0; c<grid[0].size(); ++c){
            if (Explore(grid, r,c, visited)){
                ++count;
            }
        }
    }

    return count;
}

void MyTest() {
    {
        vector<vector<string>> grid ({
        vector<string>({"W", "L", "W", "W", "W"}),
        vector<string>({"W", "L", "W", "W", "W"}),
        vector<string>({"W", "W", "W", "L", "W"}),
        vector<string>({"W", "W", "L", "L", "W"}),
        vector<string>({"L", "W", "W", "L", "L"}),
        vector<string>({"L", "L", "W", "W", "W"}),
        });
        cout << IslandCount(grid) << endl; // -> 3
    }

    {
        vector<vector<string>> grid ({
        vector<string>({"L", "W", "W", "L", "W"}),
        vector<string>({"L", "W", "W", "L", "L"}),
        vector<string>({"W", "L", "W", "L", "W"}),
        vector<string>({"W", "W", "W", "W", "W"}),
        vector<string>({"W", "W", "L", "L", "L"}),
        });

        cout << IslandCount(grid) << endl; // -> 4
    }

    {
        vector<vector<string>> grid ({
        vector<string>({"W", "W", "W", "W", "W"}),
        vector<string>({"W", "W", "W", "W", "W"}),
        vector<string>({"W", "W", "W", "W", "W"}),
        vector<string>({"W", "W", "W", "W", "W"}),
        vector<string>({"W", "W", "W", "W", "W"}),
        });

        cout << IslandCount(grid) << endl; // -> 0
    }
}
int main() {
    MyTest();
    return 0;
}