// test.cc
//

#include "cotree.h"
#include "vEB-tree.h"
#include <vector>
#include <list>
#include <set>
#include <cassert>
#include <algorithm>
#include <iostream>

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

size_t randint(size_t max) {
	return ((((size_t)rand() << 15) ^ ((size_t)rand() << 30) ^ ((size_t)rand() << 45)) % max) + 1;
}

std::vector<int> rand_vector(size_t size) {
	std::vector<int> v(size, 0);
	int base = -1;
	for (size_t i = 0; i < size; i++) {
		base += randint(20);
		v[i] = base;
		assert(base >= 0);
	}
	return v;
}

template<class T>
void test_sanity() {
	int array[] = { 0, 2, 17, 19, 38 };
	std::vector<int> vec(array, array + 5);
	T tree(vec);
	assert(tree.contains(0));
	assert(!tree.contains(4));
	assert(tree.contains(38));
	assert(!tree.contains(37));
}

template<class T>
void test_construction() {
	for (unsigned size = 2; size < 1384; size++) {
		std::vector<int> v = rand_vector(size);
		T tree(v);
		int end = v[size - 1] + 2;
		for (int i = 0; i < end; i++) {
			bool contains = tree.contains(i);
			bool present = std::binary_search(v.begin(), v.end(), i);
			assert(contains == present);
		}
	}
}

template<class T>
void test_insertion() {
	std::set<int> set;
	T tree;
	size_t size = 5000;
	for (unsigned i = 0; i < 2 * size; i++) {
		int value = randint(size);
		set.insert(value);
		tree.insert(value);
		for (int i = 0; i < size + 2; i++) {
			bool contains = tree.contains(value);
			bool present = set.find(value) != set.end();
			assert(contains == present);
		}
	}
}

void test_correctness() {
	typedef cotree::cotree<IntParams> cotree;

	std::cout << "Testing cotree sanity..." << std::flush;
	test_sanity<cotree>();
	std::cout << " done" << std::endl;

	std::cout << "Testing cotree construction..." << std::flush;
	test_construction<cotree>();
	std::cout << " done" << std::endl;

	std::cout << "Testing cotree insertion..." << std::flush;
	test_insertion<cotree>();
	std::cout << " done" << std::endl;
	
	std::cout << "Testing VebTree sanity..." << std::flush;
	test_sanity<VebTree>();
	std::cout << " done" << std::endl;
	
	std::cout << "Testing VebTree construction..." << std::flush;
	test_construction<VebTree>();
	std::cout << " done" << std::endl;

}

int main(int argc, const char * argv[]) {
	srand(time(NULL));
	test_correctness();
	std::cout << "pass" << std::endl;
	return 0;
}
