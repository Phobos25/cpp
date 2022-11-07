#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>

using namespace std;

int returnVal(const string& s){
    unsigned n = s.length();
    char char_array[n + 1];
    strcpy(char_array, s.c_str());
    for (int i = 0; i < n; i++)
        cout << char_array[i];
    return 1;
    // return (int)x - 55;
}

string numeral(int base, int n) {
    
    string res = "";
    
    for (int i = 0; n > 0; i++) {
 
        if (n == base) {
            res = "10" + res;
            break;
        }
        
        else {
            if (n % base > 9) {
                res = char('A' + (n%base) - 10) + res;
            }
            else {
                res = char((n%base) + '0') + res;
            }
        }
         
        n /= base;
    }    
    return res;
}

int main(){
    vector<string> lhs;      
    vector<string> rhs;      
    bool flag = 0;
    string line;
    string x;
    getline(cin, line);
    istringstream stream(line);
    while (stream >> x){
        if (x == "="){
            flag = 1;
            continue;
        }
        if (flag == 0){
            lhs.push_back(x);
        } else {
            rhs.push_back(x);
        }        
    }
    returnVal(lhs[0]);
    // cout << numeral(16, 10) << endl;    
    // int a = 'A';
    // cout << returnVal(a) << endl;
    return 0;
}