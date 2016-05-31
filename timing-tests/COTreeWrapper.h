#ifndef COTREE_WRAPPER
#define COTREE_WRAPPER

#include <vector>
#include "../cotree.h"
using namespace std;

class COTreeWrapper {

	typedef long value_type;

	struct COParams : public cotree::cotree_params_tag {
		typedef typename COTreeWrapper::value_type value_type;
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

	typedef cotree::cotree<COParams> tree_type;

	tree_type tree;

	static std::vector<value_type> make_vec(size_t size) {
		std::vector<value_type> vec(size);
		for (unsigned i = 0; i < vec.size(); i++) {
			vec[i] = i;
		}
		return vec;
	}

public:

	COTreeWrapper(const std::vector<double>& weights) : tree(make_vec(weights.size())) {}

	bool contains(value_type key) const {
		return tree.contains(key);
	}
};
#endif
