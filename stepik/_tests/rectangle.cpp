#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(){
  int n, m; // size of rectangle
  ifstream in_file("rectangle.in");
  ofstream out_file;
  in_file >> n >> m; 
  vector<vector<int>> a(n+1, vector<int> (m+1)); // array
  vector<vector<int>> s(n+1, vector<int> (m+1)); // matrix of sums
  // zero column must be 0
  for (int i = 0; i < n+1; i++){
    s[i][0] = 0;
  }
  
  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= m; j++){
      in_file >> a[i][j]; // fill our array
      s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1]+a[i][j];
    }    
  }
  int q; // number of queries
  in_file >> q;
  out_file.open ("rectangle.out");
  long result = 0;
  for (int i = 0; i < q; i++){
    int x1, x2, y1, y2; 
    in_file >> x1 >> x2 >> y1 >> y2; 
    out_file << s[x2][y2] - s[x1-1][y2] - s[x2][y1-1]+s[x1-1][y1-1];
    out_file << endl;
    result += s[x2][y2] - s[x1-1][y2] - s[x2][y1-1]+s[x1-1][y1-1];
  }
  out_file << result << endl;
  out_file.close();
  
  return 0;
}