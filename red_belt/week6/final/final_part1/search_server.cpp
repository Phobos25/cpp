#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <vector>
#include <numeric>

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

ostringstream SearchServer::QuerySingleStream(
    string &current_query){  
  
  ostringstream search_results_output;
  const auto words = SplitIntoWords(current_query);
  vector<size_t> docid_count(50000, 0);       
  for (const auto& word : words) { // O(m)
    for (const size_t docid : index.Lookup(word)) {// O(n)
      docid_count[docid]++;
    }
  }    
            
  // O(n)    
  vector<size_t> indices(docid_count.size());
  iota(indices.begin(), indices.end(), 0);
  partial_sort(indices.begin(), indices.begin() + 5, indices.end(),
        [&](int64_t lhs, int64_t rhs) {
            return make_pair(docid_count[lhs], -lhs) > make_pair(docid_count[rhs], -rhs);
        });  
  
  vector<pair<size_t, size_t>> search_results;
  for (auto& i:indices){
    search_results.push_back(make_pair(i, docid_count[i]));
  }   
      
  search_results_output << current_query << ':'; //O(5)
  for (auto [docid, hitcount] : Head(search_results, 5)) {
    if (hitcount != 0){
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }      
  }
  search_results_output << endl;
  return search_results_output;
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {  
  for (string current_query; getline(query_input, current_query); ) {
        
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
