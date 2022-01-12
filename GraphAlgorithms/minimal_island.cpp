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

int ExploreSize(vector<vector<string>>& grid, int r, int c, set<Cell>& visited){
    bool rowBounds = ((r>= 0) && (r < grid.size())) ? true : false;
    bool colBounds = ((c>= 0) && (c < grid[0].size())) ? true : false;
    if ((rowBounds != true) || (colBounds != true) ) {
        return 0;
    }
    if (grid[r][c] == "W"){
        return 0;
    }

    Cell pos(r, c);
    if (visited.find(pos) != visited.end()){
        return 0;
    } else {
        visited.insert(pos);
    }      

    int size = 1;
    size += ExploreSize(grid, r-1, c, visited);
    size += ExploreSize(grid, r+1, c, visited);
    size += ExploreSize(grid, r, c-1, visited);
    size += ExploreSize(grid, r, c+1, visited);

    return size;
}

int MinimalIsland(vector<vector<string>>& grid){
    set<Cell> visited;    
    int min_size = INT_MAX;
    for (int r=0; r<grid.size(); ++r){
        for (int c=0; c<grid[0].size(); ++c){
            int size = ExploreSize(grid, r,c, visited);                
            if ((size > 0) && (size < min_size)){
                min_size = size;
            }
        }
    }

    return min_size;
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
        cout << MinimalIsland(grid) << endl; // -> 3
    }

    {
        vector<vector<string>> grid ({
        vector<string>({"L", "W", "W", "L", "W"}),
        vector<string>({"L", "W", "W", "L", "L"}),
        vector<string>({"W", "L", "W", "L", "W"}),
        vector<string>({"W", "W", "W", "W", "W"}),
        vector<string>({"W", "W", "L", "L", "L"}),
        });

        cout << MinimalIsland(grid) << endl; // -> 4
    }

    {
        vector<vector<string>> grid ({
        vector<string>({"W", "W", "W", "W", "W"}),
        vector<string>({"W", "W", "W", "W", "W"}),
        vector<string>({"W", "W", "W", "W", "W"}),
        vector<string>({"W", "W", "W", "W", "W"}),
        vector<string>({"W", "W", "W", "W", "W"}),
        });

        cout << MinimalIsland(grid) << endl; // -> 0
    }
}
int main() {
    MyTest();
    return 0;
}