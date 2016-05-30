#include <set>
#include <iostream>

using namespace std;

#include <stdlib.h>
#include "btree_set.h"
#include "vEB-tree.h"

bool contains(set<double>& s, double n) {
  return s.find(n) != s.end();
}

bool contains(btree::btree_set<double>& s, double n) {
  return s.find(n) != s.end();
}

int main(int argc, char* argv[]) {
  vector<double> v;
  set<double> s;
  for (int i = 1; i <= 2000; i++) {
    v.push_back(i *2.0);
    s.insert(i * 2.0);
  }
  VebTree t(v);

  //btree::btree_set<int> s;
  //set<int> s;
  //for (int i = 1000; i < 10000; i++) {
    //s.insert(i*2);
  //}
  int errors = 0;
  int found = 0;
  for (int n = 0; n < 20000; n++) {
    double r = random() % 5000;
    //if (contains(s, r) != (2000 <= r && r <= 20000 && r % 2 == 0)) {
    if (t.contains(r) != contains(s, r)) {
      cout << "ERROR: searched for " << r << "..."  << t.contains(r) << endl;
      errors++;
    }
    if (contains(s, r)) {
      found++;
    }

  }
  cout << "Done! (errors: " << errors << ")" << endl;
  cout << "found: " << found << endl;
  return 0;
}
