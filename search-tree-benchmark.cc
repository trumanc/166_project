#include <set>
#include <iostream>

using namespace std;

#include <stdlib.h>
#include "btree_set.h"
#include "vEB-tree.h"

bool contains(set<int>& s, int n) {
  return s.find(n) != s.end();
}

bool contains(btree::btree_set<int>& s, int n) {
  return s.find(n) != s.end();
}

int main(int argc, char* argv[]) {
  vector<int> v;
  for (int i = 1; i <= 16; i++) {
    v.push_back(i);
  }
  VebTree t(v);

  btree::btree_set<int> s;
  //set<int> s;
  for (int i = 1000; i < 2000; i++) {
    s.insert(i);
  }

  for (int n = 0; n < 1000; n++) {
    int r = random() % 4000;
    if (contains(s, r) != (1000 <= r && r < 2000)) {
      cout << "ERROR" << endl;
    }
  }
  cout << "Done!" << endl;
  return 0;
}
