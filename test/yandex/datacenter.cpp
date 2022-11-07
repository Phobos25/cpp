#include <iostream>
#include <vector>

using namespace std;

vector<int> c;
vector<int> servers;

void Disable(const int i, const int j, vector<vector<int>>& d){
    if (d[i][j] != 0){
        servers[i]--;
        d[i][j] = 0; // O(1)
    }   
}

void Reset(const int i, vector<vector<int>>& d){
    for (unsigned k=0; k<d[i].size(); ++k){
        d[i][k] = 1; // O(m)        
    }
    servers[i] = d[i].size();
    c[i] += 1;
}

int Getmax(vector<vector<int>>& d){
    int s = 0;
    int num = 0;
    s = c[0]*servers[0];
    for (unsigned i=0; i<c.size(); ++i){
        if (c[i]*servers[i] > s){
            s = c[i]*servers[i];
            num = i;
        }
    }
    return num+1;
}

int Getmin(vector<vector<int>>& d){// O(m)          
    int s = 0;
    int num = 0;
    s = c[0]*servers[0];
    for (unsigned i=0; i<c.size(); ++i){
        if (c[i]*servers[i] < s){
            s = c[i]*servers[i];
            num = i;
        }
    }
    return num+1;
}

void get_command(const string& com, vector<vector<int>>& d){
    if (com == "DISABLE"){
        int i, j;
        cin >> i >> j;
        Disable(i-1, j-1, d);
    }
    if (com == "RESET"){
        int i;
        cin >> i;
        Reset(i-1, d);
    }
    if (com == "GETMAX"){
        cout << Getmax(d) << endl;
    }
    if (com == "GETMIN"){
        cout << Getmin(d) << endl;
    }
}

int main() {
    int n = 0;
    int m = 0;
    cin >> n >> m;
    vector<vector<int>> d(n, vector<int>(m, 1));
    for(unsigned i=0; i<n; ++i){
        c.push_back(0);
        servers.push_back(m);
    }
    int q;
    cin >> q;
    for (int i = 0; i<q; ++i){
        string com;         
        cin >> com;       
        get_command(com, d);
    }
    return 0;
}