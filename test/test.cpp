#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <future>
#include <sstream>
using namespace std;

void ReadLines(stringstream& ss){
  vector<string> words; 
  string line;
  string line2;
  getline(ss, line, '\n');  
  stringstream linestream(line);
  while (linestream){
    string temp;
    linestream >> temp;
    words.push_back(temp);
  }
  for (const auto& w:words){
    cout << w << " ";
  }
  cout << endl;
  
  getline(ss, line, '\n');
  stringstream ls2(line);
  while (ls2){
    string temp;
    ls2 >> temp;
    words.push_back(temp);
  }
  for (const auto& w:words){
    cout << w << " ";
  }
  cout << endl;
}

int main() {

    stringstream ss;
    ss << "this new yangle service really rocks\n";    
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
    ReadLines(ss);
}

