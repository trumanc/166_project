#ifndef BTREE_WRAPPER
#define BTREE_WRAPPER

#include <vector>
#include "btree_set.h"
using namespace std;

class BTreeWrapper {

	typedef btree::btree_set<int, std::less<int>, std::allocator<int>, 64> tree_type;

	tree_type tree;

	static std::vector<int> make_vec(size_t size) {
		std::vector<int> vec(size);
		for (unsigned i = 0; i < vec.size(); i++) {
			vec[i] = i;
		}
		return vec;
	}

public:

	BTreeWrapper(const std::vector<double>& weights) {
		std::vector<int> vec = make_vec(weights.size());
		tree = tree_type(vec.begin(), vec.end());
	}

	bool contains(int key) const {
		return tree.find(key) != tree.end();
	}
};
#endif
