#ifndef COTREE_WRAPPER
#define COTREE_WRAPPER

#include <vector>
#include "../cotree.h"
using namespace std;

class COTreeWrapper {

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

	typedef cotree::cotree<IntParams> tree_type;

	tree_type tree;

	static std::vector<int> make_vec(size_t size) {
		std::vector<int> vec(size);
		for (unsigned i = 0; i < vec.size(); i++) {
			vec[i] = i;
		}
		return vec;
	}

public:

	COTreeWrapper(const std::vector<double>& weights) : tree(make_vec(weights.size())) {}

	bool contains(int key) const {
		return tree.contains(key);
	}
};
#endif
