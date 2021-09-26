#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// РћР±СЉСЏРІР»СЏРµРј Group<String> РґР»СЏ РїСЂРѕРёР·РІРѕР»СЊРЅРѕРіРѕ С‚РёРїР° String
// СЃРёРЅРѕРЅРёРјРѕРј vector<String>.
// Р‘Р»Р°РіРѕРґР°СЂСЏ СЌС‚РѕРјСѓ РІ РєР°С‡РµСЃС‚РІРµ РІРѕР·РІСЂР°С‰Р°РµРјРѕРіРѕ Р·РЅР°С‡РµРЅРёСЏ
// С„СѓРЅРєС†РёРё РјРѕР¶РЅРѕ СѓРєР°Р·Р°С‚СЊ РЅРµ РјР°Р»РѕРїРѕРЅСЏС‚РЅС‹Р№ РІРµРєС‚РѕСЂ РІРµРєС‚РѕСЂРѕРІ,
// Р° РІРµРєС‚РѕСЂ РіСЂСѓРїРї вЂ” vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Р•С‰С‘ РѕРґРёРЅ С€Р°Р±Р»РѕРЅРЅС‹Р№ СЃРёРЅРѕРЅРёРј С‚РёРїР°
// РїРѕР·РІРѕР»СЏРµС‚ РІРјРµСЃС‚Рѕ РіСЂРѕРјРѕР·РґРєРѕРіРѕ typename String::value_type
// РёСЃРїРѕР»СЊР·РѕРІР°С‚СЊ Char<String>
template <typename String>
using Char = typename String::value_type;
template <typename String>
using Key = String;

template <typename String>
Key<String> ComputeStringKey (const String& string){
  String chars = string;
  sort(begin(chars), end(chars));
  chars.erase(unique(begin(chars), end(chars)), end(chars));
  return chars;
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
  map<Key<String>, Group<String>> groups_map;
  for (String& string:strings){
    groups_map[ComputeStringKey(string)].push_back(move(string));
  }
  vector<Group<String>> groups;
  for (auto& [key, group]:groups_map){
    groups.push_back(move(group));
  }
  return groups;
}
