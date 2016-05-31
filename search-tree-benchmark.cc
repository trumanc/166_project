#include <cstdlib>

#include "btree_set.h"
#include "vEB-tree.h"
#include "cotree.h"
#include <set>
#include <unordered_set>

using namespace std;

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
  BTreeType,
  StdSetType,
  StdUnorderedSetType
};

bool parse_tree_type(const char * str, TreeType& type) {
  string s = string(str);
  if (s == "VebTree") {
    type = VebTreeType;
  } else if (s == "COTree") {
    type = COTreeType;
  } else if (s == "BTree") {
    type = BTreeType;
  } else if (s == "std::set") {
    type = StdSetType;
  } else if (s == "std::unordered_set") {
    type = StdUnorderedSetType;
  } else {
    return false;
  }
  return true;
}

void usage(int argc, char* argv[]) {
  cout << "Usage: " << argv[0] << " <tree-size> <num-queries> <tree-type>" << endl;
  exit(1);
}

typedef long value_type;

struct COParams : public cotree::cotree_params_tag {
  typedef value_type value_type;
  static value_type compare(value_type a, value_type b) {
    return a - b;
  }
  static bool is_present(value_type a) {
    return a != absent_value();
  }
  static value_type absent_value() {
    return -1;
  }
};

typedef cotree::cotree<COParams> COTree;

#define DENSE_BTREE 0

class BTree {
  typedef btree::btree_set<value_type> btree;
  btree tree;
public:
#if DENSE_BTREE
  BTree(vector<value_type> v) : tree(v.begin(), v.end()) {}
#else
  BTree(vector<value_type> v) {
    // Inserting in stages like this will force the btree implementation to
    // actually split nodes, meaning its nodes are no longer densely packed.
    // This might be more realistic if the tree has insertions and deletions.
    for (size_t i = 0; i < v.size(); i += 3) {
      tree.insert(i);
    }
    for (size_t i = 2; i < v.size(); i += 3) {
      tree.insert(i);
    }
    for (size_t i = 1; i < v.size(); i += 3) {
      tree.insert(i);
    }
  }
#endif
  bool contains(value_type v) {
    return tree.find(v) != tree.end();
  }
};

class StdSet {
  std::set<value_type> set;
public:
  StdSet(vector<value_type> v) : set(v.begin(), v.end()) {}
  bool contains(value_type v) {
    return set.find(v) != set.end();
  }
};

class StdUnorderedSet {
  std::unordered_set<value_type> set;
public:
  StdUnorderedSet(vector<value_type> v) : set(v.begin(), v.end()) {}
  bool contains(value_type v) {
    return set.find(v) != set.end();
  }
};

template<class Tree>
size_t run(size_t tree_size, size_t num_queries) {
  vector<value_type> v(tree_size, 0);
  for (value_type i = 0; i < tree_size; i++) {
    v[i] = 2 * i;
  }
  Tree tree(v);
  v = vector<value_type>();
  size_t found = 0;
  for (value_type n = 0; n < num_queries; n++) {
    value_type r = random() % (2 * tree_size);
    if (tree.contains(r)) {
      found++;
    }
  }
  return found;
}

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
  int found;
  switch (type) {
    case VebTreeType:
      found = run<VebTree>(tree_size, num_queries);
      break;
    case COTreeType:
      found = run<COTree>(tree_size, num_queries);
      break;
    case BTreeType:
      found = run<BTree>(tree_size, num_queries);
      break;
    case StdSetType:
      found = run<StdSet>(tree_size, num_queries);
      break;
    case StdUnorderedSetType:
      found = run<StdUnorderedSet>(tree_size, num_queries);
      break;
  }
  return (found & ~0xFF) | sizeof(value_type);
}
