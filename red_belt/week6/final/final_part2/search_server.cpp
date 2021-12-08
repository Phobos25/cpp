#include "search_server.h"
#include "synchronized.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <iostream>
#include <numeric>
#include <future>

using namespace std;

vector<string> SplitIntoWords(const string& line);
void UpdateIndex(istream& document_input, Synchronized<InvertedIndex>& index_);
void ProcessQueries(istream& query_input, ostream& search_results_output, Synchronized<InvertedIndex>& index_);

vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

void UpdateIndex(
      istream& document_input,
      Synchronized<InvertedIndex>& index_){

  InvertedIndex new_index;
  for (string current_document; getline(document_input, current_document);){
    new_index.Add(move(current_document));
  }

  swap(index_.GetAccess().ref_to_value, new_index);
}

void ProcessQueries(
              istream& query_input, 
              ostream& search_results_output, 
              Synchronized<InvertedIndex>& index_
) {  
  // start here
  for (string current_query; getline(query_input, current_query);){
    const auto words = SplitIntoWords(current_query);    
    auto access = index_.GetAccess();    
    // const auto docs_count = access.ref_to_value.GetDocuments().size();

    vector<size_t> docid_count(50000,0);    
    auto& index = access.ref_to_value;
    for (const auto& word : words) {
      for (const size_t docid : index.Lookup(word)) {
        docid_count[docid]++;
      }
    }

    vector<size_t> indices(50000);
    iota(indices.begin(), indices.end(), 0);
    partial_sort(indices.begin(), indices.begin() + 5, indices.end(), 
      [&](int64_t lhs, int64_t rhs) {
        return make_pair(docid_count[lhs], -lhs) > make_pair(docid_count[rhs], -rhs);
      }
    );

    vector<pair<size_t, size_t>> search_results;
    int count = 0;
    for (auto& id: indices){
      if (count >= 5) {break;}
      search_results.push_back(make_pair(id, docid_count[id]));
      ++count;
    }

    search_results_output << current_query << ':';
    for (auto [docid, hitcount] : Head(search_results, 5)) {
      if (hitcount != 0){
        search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
      }      
    }
    search_results_output << endl;
  }
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  async_tasks.push_back(async(UpdateIndex, ref(document_input), ref(index)));
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
  async_tasks.push_back(
    async(
      ProcessQueries, 
      ref(query_input), ref(search_results_output), ref(index)
  )    
  );
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
