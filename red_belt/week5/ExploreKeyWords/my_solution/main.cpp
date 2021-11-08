#include "test_runner.h"
//#include "profile.h"

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Stats {
  map<string, int> word_frequences;

  map<string, int>& operator += (const Stats& other){
    for (auto& [key, value]:other.word_frequences){
      if (word_frequences.count(key) != 0){
        word_frequences[key] += value;
      } else {
        word_frequences[key] = value;
      }
    }
    return word_frequences;
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
  Stats stats;
  stringstream ss(line);
  while (ss){
    string word;
    ss >> word;
    if (key_words.find(word) != key_words.end()){
      ++stats.word_frequences[word];
    }
    // cout << word << " ";
  }
  // cout << endl;
  return stats;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  // Реализуйте эту функцию
  string line;
  Stats stats;
  while (input){
    getline(input, line, '\n');
    stats += ExploreLine(key_words, line);
  }


  return stats;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

// void MyTest(){
//   const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

//   stringstream ss;
//   ss << "this new yangle service really rocks\n";
//   ss << "It sucks when yangle isn't available\n";
//   ss << "10 reasons why yangle is the best IT company\n";
//   ss << "yangle rocks others suck\n";
//   ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
//   const auto stats = ExploreKeyWords(key_words, ss);
//   cout << "yangle: " << stats.word_frequences.at("yangle") << endl;
//   cout << "rocks: "  << stats.word_frequences.at("rocks") << endl;
//   cout << "sucks: "  << stats.word_frequences.at("sucks") << endl;
// }

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
  // MyTest();
}
