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
  set<int> s;
  bool VEB = (string(argv[1]) == "vebtree");
  if (VEB) {
    cout << "Using the vEB tree" << endl;
    for (int i = 1; i <= 65536; i++) {
      v.push_back(i *2);
    }
  }
  v.push_back(200000);
  v.push_back(200001);
  VebTree t(v);
  
  btree::btree_set<int, std::less<int>, std::allocator<int>, 64> bts;
  if (!VEB) {
    cout << "Using the B-tree" << endl;
    for (int i = 1; i <= 65536; i++) {
      bts.insert(i *2);
    }
    bts.insert(200000);
    bts.insert(200001);
  }
  int errors = 0;
  int found = 0;
  
  if (string(argv[2]) == "query") {
    cout << "Querying..." << endl;
    int numTrials = 1 << 21;
    for (int n = 0; n < numTrials; n++) {
      int r = random() % 140000;
      //if (contains(s, r) != (2000 <= r && r <= 20000 && r % 2 == 0)) {
      if (VEB) {
        if (t.contains(r)) found++;
      } else {
        if (bts.find(r) != bts.end()) found++;
      }
    }
  }
  cout << "found: " << found << endl;
  return 0;
}
