#include <cstdlib>

#include "btree_set.h"
#include "vEB-tree.h"
#include "cotree.h"

using namespace std;

struct IntParams : public cotree::cotree_params_tag {
  typedef int value_type;
  static int compare(int a, int b) {
    return a - b;
  }
  static bool is_present(int a) {
    return a != absent_value();
  }
  static int absent_value() {
    return -1;
  }
};

bool calculate_unsigned(const char * str, size_t& value) {
  const int stack_max = 4;
  size_t stack[stack_max + 1];
  int p = -1;
  const char * s = str;
  char * end;

  // Implement little RPN calculator.
  while (*s) {
    switch (*s) {
    case '^':
      if (p < 0) {
        return false;
      }
      stack[p] = 1 << stack[p];
      s++;
      break;
    case '+':
      if (--p < 0) {
        return false;
      }
      stack[p] += stack[p + 1];
      s++;
      break;
    case '-':
      if (--p < 0) {
        return false;
      }
      stack[p] -= stack[p + 1];
      s++;
      break;
    case '*':
      if (--p < 0) {
        return false;
      }
      stack[p] *= stack[p + 1];
      s++;
      break;
    case '/':
      if (--p < 0) {
        return false;
      }
      stack[p] /= stack[p + 1];
      s++;
      break;
    default:
      if (p == stack_max) {
        return false;
      }
      stack[++p] = strtoull(s, &end, 0);
      assert(s != end);
      s = end;
    }
  }
  if (p != 0) {
    return false;
  }
  value = stack[0];
  return true;
}

enum TreeType {
  VebTreeType,
  COTreeType,
  BTreeType
};

bool parse_tree_type(const char * str, TreeType& type) {
  string s = string(str);
  if (s == "VebTree") {
    type = VebTreeType;
  } else if (s == "COTree") {
    type = COTreeType;
  } else if (s == "BTree") {
    type = BTreeType;
  } else {
    return false;
  }
  return true;
}

void usage(int argc, char* argv[]) {
  cout << "Usage: " << argv[0] << " <tree-size> <num-queries> <tree-type>" << endl;
  exit(1);
}

typedef cotree::cotree<IntParams> COTree;
typedef btree::btree_set<int, std::less<int>, std::allocator<int>, 64> BTree;

int main(int argc, char* argv[]) {
  size_t tree_size;
  size_t num_queries;
  TreeType type;
  if (argc != 4 ||
      !calculate_unsigned(argv[1], tree_size) ||
      !calculate_unsigned(argv[2], num_queries) ||
      !parse_tree_type(argv[3], type)) {
    usage(argc, argv);
  }

  vector<int> v(tree_size, 0);
  for (int i = 0; i < tree_size; i++) {
    v[i] = (i+1) * 2;
  }

  VebTree vebtree(v);
  BTree btree(v.begin(), v.end());
  COTree cotree(v);

  int found = 0;
  for (int n = 0; n < num_queries; n++) {
    int r = random() % (2 * tree_size);
    switch (type) {
      case VebTreeType:
        if (vebtree.contains(r)) found++;
        break;
      case COTreeType:
        if (cotree.contains(r)) found++;
        break;
      case BTreeType:
        if (btree.find(r) != btree.end()) found++;
        break;
    }
  }
  return found;
}
