#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <vector>

vector<string> SplitIntoWords(const string& line) {  
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }
  
  index = move(new_index);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {  
  for (string current_query; getline(query_input, current_query); ) {
    // { LOG_DURATION("Split into words: ");
    //   for (int i=0; i<10'000; ++i){
    //     const auto words = SplitIntoWords(current_query); // O(1)      
    //   }      
    // }    
    const auto words = SplitIntoWords(current_query); // O(1)
    // { LOG_DURATION("docid count: ");
    //   for (int i=0; i<10'000; ++i){
    //     // map<size_t, size_t> docid_count; 
    //     for (const auto& word : words) { // O(m)
    //       for (const size_t docid : index.Lookup(word)) {// O(n)
    //         docid_count[docid]++;
    //       }
    //     }  
    //   }
    // }
    // map <size_t, size_t> docid_count;     
    vector<size_t> docid_count(50000, 0);       
    for (const auto& word : words) { // O(m)
      for (const size_t docid : index.Lookup(word)) {// O(n)
        docid_count[docid]++;
      }
    }    
    
    // { LOG_DURATION("sort: ");
    //   for (int i=0; i<10'000; ++i){
    //     vector<pair<size_t, size_t>> search_results(
    //       docid_count.begin(), docid_count.end()
    //     );    
    //     sort(    // O(nlog(n))
    //       begin(search_results),
    //       end(search_results),
    //       [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
    //         int64_t lhs_docid = lhs.first;
    //         auto lhs_hit_count = lhs.second;
    //         int64_t rhs_docid = rhs.first;
    //         auto rhs_hit_count = rhs.second;
    //         return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
    //       }
    //     );    
    //       }
    // }
    
    // O(n)
    vector<pair<size_t, size_t>> search_results(
      docid_count.begin(), docid_count.end()
    );    
    sort(    // O(nlog(n))
      begin(search_results),
      end(search_results),
      [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
        int64_t lhs_docid = lhs.first;
        auto lhs_hit_count = lhs.second;
        int64_t rhs_docid = rhs.first;
        auto rhs_hit_count = rhs.second;
        return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
      }
    );

    // { LOG_DURATION("prepare result: ");
    //   for (int i=0; i<10'000; ++i){
    //     search_results_output << current_query << ':'; //O(5)
    //     for (auto [docid, hitcount] : Head(search_results, 5)) {
    //       search_results_output << " {"
    //         << "docid: " << docid << ", "
    //         << "hitcount: " << hitcount << '}';
    //     }
    //     search_results_output << endl;
    //   }
    // }

    search_results_output << current_query << ':'; //O(5)
    for (auto [docid, hitcount] : Head(search_results, 5)) {
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
  }
}

void InvertedIndex::Add(const string& document) {
  docs.push_back(document);

  const size_t docid = docs.size() - 1;
  for (const auto& word : SplitIntoWords(document)) {
    index[word].push_back(docid);
  }
}

list<size_t> InvertedIndex::Lookup(const string& word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}
