#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <thread>
#include <future>

using namespace std;
template <typename It>
class IteratorRange {
public:
  IteratorRange(It first, It last) : first(first), last(last) {
  }

  It begin() const {
    return first;
  }

  It end() const {
    return last;
  }

  size_t size() const {
    return last - first;
  }

private:
  It first, last;
};

template <typename Container>
auto Head(Container& c, int top) {
  return IteratorRange(begin(c), begin(c) + min<size_t>(max(top, 0), c.size()));
}

template <typename Container>
string Join(char c, const Container& cont) {
  ostringstream os;
  for (const auto& item : Head(cont, cont.size() - 1)) {
    os << item << c;
  }
  os << *rbegin(cont);
  return os.str();
}

vector<string> SplitIntoWords(const string& line) {  

  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

template <typename ContainerOfVectors >
int64_t SumSingleThread(const ContainerOfVectors& matrix){
    int64_t sum = 0;
    for (const auto& row: matrix){
        for (auto item:row){
            sum += item;
        }
    }

    return sum; 
}

template <typename ContainerOfVectors >
void GenerateSingleThread(
    ContainerOfVectors& result,
    size_t first_row,
    size_t column_size) {

    for (auto& row : result) {
        row.reserve(column_size);
        for (size_t column = 0; column < column_size; ++column) {
            row.push_back(first_row ^ column);
        }
        ++first_row;
    }
}


vector <vector <int>> GenerateSingleThread(size_t size) {
    vector <vector <int>> result(size);
    GenerateSingleThread(result , 0, size);
    return result;
}

vector<vector<int>> GenerateMultiThread(
        size_t size, 
        size_t page_size){
    
    vector<vector<int>> result(size);
    vector<future<void>> futures;
    size_t first_row = 0;

    return result;

}


void myTest(istream& document_input){
    vector<future<vector<string>>> fut_strings;
    for (string current_document; getline(document_input, current_document); ) {
        fut_strings.push_back(async(SplitIntoWords, current_document));    
    }
    for (auto& f_s:fut_strings){
        cout << f_s.get()[0] << endl;
    }
}

int main() {    
    const vector<string> docs = {
        "we are ready to go",
        "come on everybody shake you hands",
        "i love this game",
        "just like exception safety is not about writing try catch everywhere in your code move semantics are not about typing double ampersand everywhere in your code",
        "daddy daddy daddy dad dad dad",
        "tell me the meaning of being lonely",
        "just keep track of it",
        "how hard could it be",
        "it is going to be legen wait for it dary legendary",
        "we dont need no education"
    };
    istringstream docs_input(Join('\n', docs));

    // vector<vector<string>> my_strings;
    LOG_DURATION("Total");
    const size_t matrix_size = 7000;
    vector<vector<int>> matrix;
    {
        LOG_DURATION("Single thread generation");
        matrix = GenerateSingleThread(matrix_size);
    }

    {
        LOG_DURATION("Single thread sum");
        cout << "Sum of matrix: "<<SumSingleThread(matrix) << endl;
    }
    myTest(docs_input);
    return 0;
}