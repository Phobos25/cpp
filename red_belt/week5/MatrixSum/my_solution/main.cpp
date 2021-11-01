#include "test_runner.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
using namespace std;

template <typename Iterator>
class IteratorRange {
private:    
    Iterator first, last;
public:
    IteratorRange (Iterator f, Iterator l)
        : first(f)
        , last(l)
        {            
        }

    Iterator begin() const {
        return first;
    }
    Iterator end() const {
        return last;
    }
    size_t size() const {
      return last - first;
    }
};

template <typename Iterator>
class Paginator {
public:
  Paginator(Iterator begin, Iterator end, size_t page_size){    
    auto min_value = [&](Iterator itr) 
        {   
            return std::min<size_t>(std::distance(itr, end), page_size); 
        };
    for (auto it = begin; it != end; it= next(it, min_value(it))){
      pages.push_back(IteratorRange(it, next(it, min_value(it))));
    }
  }
  auto begin() const {
    return pages.begin();
  }
  auto end() const {
    return pages.end();
  }
  size_t size() const {
    return pages.size();
  }
private:  
  vector<IteratorRange<Iterator>> pages;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(c.begin(), c.end(), page_size);
}

template <typename Container>
int64_t AccumulateTwoVector(const Container& submatrix){
    int64_t result = 0;
    for (const auto& vec: submatrix){
      result += accumulate(vec.begin(), vec.end(), 0);
    }     
    return result;
}


int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  // Реализуйте эту функцию  
  int64_t result = 0;  
  vector<future<int64_t>> futures;    
  for (const auto& page:Paginate(matrix, 1000)){
      // cout << "page size: "<<page.size() << endl;
      futures.push_back(async([=] {
        return AccumulateTwoVector(page);
    }));
  }    
  for (auto& f:futures){
    result += f.get();
  }
  return result;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
