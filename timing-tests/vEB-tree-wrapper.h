#ifndef VEB_TREE_WRAPPER
#define VEB_TREE_WRAPPER

#include <vector>
#include <../vEB-tree.h>
using namespace std;

class VebTreeWrapper {
	public:
		VebTreeWrapper(const std::vector<double>& weights);

		~VebTreeWrapper();

		bool contains(int key) const;

	private:
		VebTree tree; // The actual data structure
};
#endif
