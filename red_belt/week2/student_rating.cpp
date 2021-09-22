#include "process.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Student {
  string first_name;
  string last_name;
  map<string, double> marks;
  double rating;

  bool operator < (const Student& other) const {
    return GetName() < other.GetName();
  }

  bool Less(const Student& other) const {
    return rating > other.rating;
  }

  string GetName() const {
    return first_name + " " + last_name;
  }
};

bool Compare(Student first, Student second) {
  return first.Less(second);
}

int main (){

    return 0;
}