#include "synonyms.h"
#include "tests.h"
#include <exception>
#include <vector>

using namespace std;
// comment
int main() {
  TestAll();
	int q ; 
	cin >> q;

	map<string, set<string>> synonyms;

	for (int i=0; i<q; ++i){
		string operation_code;
		cin >> operation_code;

		if (operation_code == "ADD"){
			string first_word, second_word;
			cin >> first_word >> second_word;
			AddSynonyms(synonyms, first_word, second_word);
		}else if(operation_code == "COUNT"){
			string word;
			cin >> word;
			cout << GetSynonymCount(synonyms, word) << endl;			
		}else if (operation_code == "CHECK"){
			string first_word, second_word;
			cin >> first_word >> second_word;
			if (AreSynonyms(synonyms, first_word, second_word)){
				cout << "YES" << endl;
			}else {
				cout << "NO" << endl;
			}
		}
	}

	return 0;
}