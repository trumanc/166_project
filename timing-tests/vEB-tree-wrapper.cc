#include "vEB-tree-wrapper.h"
using namespace std;

VebTreeWrapper::VebTreeWrapper(const std::vector<double>& weights) : tree(std::vector<long>(2)) {
	std::vector<long> v;
	for (size_t i = 0; i < weights.size(); i++) {
		v.push_back(i);
	}
	tree = VebTree(v);
}

VebTreeWrapper::~VebTreeWrapper() {
	// noop
}

bool VebTreeWrapper::contains(long key) const {
	return tree.contains(key);
}

