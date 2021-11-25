#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string> SplitIntoWords(const string& line) {  
  // может тут надо разделять? раз это самый медленный?
  // как жто можно сделать? 
  // как это работает? он берет один длинный стринг и делит его на 
  // отдельные слова и добавляет в вектор
  // щначит саму функцию надо запускать параллельно
  // и хранить большой вектор
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
    // auto fut1 = SplitIntoWords
    // auto fut2 = SplitIntoWords
    // auto fut3 = SplitIntoWords
    // auto fut4 = SplitIntoWords
  }
  
  // vector<string> all_words = fut1 + fut2 + fut3; 

  index = move(new_index);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
  for (string current_query; getline(query_input, current_query); ) {
    const auto words = SplitIntoWords(current_query); // O(1)

    map<size_t, size_t> docid_count; 
    for (const auto& word : words) { // O(m)
      for (const size_t docid : index.Lookup(word)) {// O(n)
        docid_count[docid]++;
      }
    }
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
