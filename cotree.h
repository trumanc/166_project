#ifndef _COBTREE_H
#define _COBTREE_H

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

namespace cotree {

// A helper type used to provide compare, is_present, and absent_value
// functions. A user can specify these functions by doing:
//
//   struct cotree::MyDatatypeParams : public cotree::cotree_params_tag {
//       static int compare(const MyDatatype& a, const MyDatatype& b) {
//           return a.compare(b);
//       }
//       static bool is_present(const MyDatatype& a) {
//           return a.is_present();
//       }
//       static const MyDatatype& absent_value() {
//           return MyDatatype::empty()
//       }
//   };
//
struct cotree_params_tag {};

// The Cache-Oblivious B-Tree type, as described by Brodal et al. in 2002.
template<typename Params>
class cotree {
public:
	typedef typename Params::value_type value_type;

private:

	// The tree contents.
	struct tree {
		typedef typename Params::value_type value_type;

		tree() : _H(0), _BTD(nullptr), _values(nullptr), _n(0) {}

		// The height of the tree.
		size_t       _H;
		// The B, T, and D arrays from brodal2002cache.
		size_t *     _BTD;
		// The value array.
		value_type * _values;
		// The number of values in the dynamic tree.
		size_t       _n;
	};

	// A cursor is a stateful pointer into a position in the tree.
	struct cursor {
	typedef typename Params::value_type value_type;
	private:
		const tree& _tree;
		// The position of each ancestor on the path, 1-indexed by depth.
		size_t      _Pos[8 * sizeof(size_t)];
	public:
		// The current path, represented as the BFS index of the current node.
		// The current node is a left child if and only if (path & 1) == 0.
		unsigned path;
		// The current depth.
		unsigned depth;

	public:
		// Creates a cursor starting at the root.
		cursor(const tree& tree) : _tree(tree), _Pos{1}, path(1), depth(1) {}

		// Creates a cursor starting at the root.
		cursor(const cursor& cursor) : _tree(cursor._tree), path(cursor.path), depth(cursor.depth) {
			for (unsigned i = 0; i < depth; i++) {
				_Pos[i] = cursor._Pos[i];
			}
		}

		// Return a reference to the current value.
		value_type& cur() const {
			return _tree._values[_Pos[depth - 1] - 1];
		}

		// Returns true if the current value is present.
		bool is_present() const {
			return Params::is_present(cur());
		}

		// Compares the other value to the current one.
		int compare(const value_type& other) const {
			return Params::compare(other, cur());
		}

		// Navigate down the left subtree.
		void left() {
			assert(depth < _tree._H);
			depth++;
			path <<= 1;
			calculate();
		}

		// Navigate down the right subtree.
		void right() {
			assert(depth < _tree._H);
			depth++;
			path <<= 1;
			path |= 1;
			calculate();
		}

		// Navigate up to the current node's parent.
		void up() {
			assert(depth > 1);
			depth--;
			path >>= 1;
		}

		// Navigate to the first slot in this subtree.
		void first_slot() {
			while (depth < _tree._H) {
				left();
			}
		}

		// Navigate to the immediate successor in the static tree.
		bool next_slot(size_t max_H) {
			if (depth < _tree._H) {
				right();
				first_slot();
			} else {
				while (depth > max_H && (path & 1) == 1) {
					up();
				}
				if (depth == max_H) {
					return false;
				} else {
					up();
				}
			}
			return true;
		}

		// Navigate to the first slot in this subtree.
		void last_slot() {
			while (depth < _tree._H) {
				right();
			}
		}

		// Navigate to the immediate predecessor in the static tree.
		bool prev_slot(size_t max_H) {
			if (depth < _tree._H) {
				left();
				last_slot();
			} else {
				while (depth > max_H && (path & 1) == 0) {
					up();
				}
				if (depth == max_H) {
					return false;
				} else {
					up();
				}
			}
			return true;
		}

		// Navigate to the first value in this subtree.
		void first_value() {
			while (depth < _tree._H) {
				left();
				if (!is_present()) {
					up();
					break;
				}
			}
		}

		// Navigate to the immediate successor in the dynamic tree.
		bool next_value(size_t max_H) {
			if (depth < _tree._H) {
				right();
				if (!is_present()) {
					up();
					goto leaf;
				}
				first_value();
			} else {
		leaf:
				while (depth > max_H && (path & 1) == 1) {
					up();
				}
				if (depth == max_H) {
					return false;
				} else {
					up();
				}
			}
			return true;
		}

		// Navigate to the last value in this subtree.
		void last_value() {
			while (depth < _tree._H) {
				right();
				if (!is_present()) {
					up();
					break;
				}
			}
		}

		// Navigate to the immediate predecessor in the dynamic tree.
		bool prev_value(size_t max_H) {
			if (depth < _tree._H) {
				left();
				if (!is_present()) {
					up();
					goto leaf;
				}
				last_value();
			} else {
		leaf:
				while (depth > max_H && (path & 1) == 0) {
					up();
				}
				if (depth == max_H) {
					return false;
				} else {
					up();
				}
			}
			return true;
		}

	private:
		// Calculate the position of the cursor.
		void calculate() {
			size_t * BTD = _tree._BTD + 3 * (depth - 2);
			_Pos[depth - 1] = _Pos[BTD[2] - 1] + BTD[1] + (path & BTD[1]) * BTD[0];
		}
	};

private:
	static constexpr double _tau1 = 0.9;
	static constexpr double _gamma1 = 0.35;
	static constexpr double _gammaH = 0.3;

private:
	// The tree.
	tree _tree;

public:
	// Construct an empty CO B-Tree.
	cotree() : _tree() {}

	// Construct a CO B-Tree from a given random-access iterator range.
	template<typename Iterator,
	         typename = typename std::enable_if<
	                 std::is_base_of<std::forward_iterator_tag,
	                                 typename std::iterator_traits<Iterator>::iterator_category
	                                >::value
	                                           >::type>
	cotree(Iterator begin, Iterator end) : _tree() {
		_tree._H = height(end - begin);
		resize(_tree._H);
		_tree._n = end - begin;
		if (_tree._n > 0) {
			cursor c(_tree);
			distribute(c, _tree._n, begin);
		}
	}

	// Construct a CO B-Tree from a sorted vector of values.
	cotree(const std::vector<value_type>& values) : cotree(values.begin(), values.end()) {}

	// The destructor.
	~cotree() {
		delete[] _tree._BTD;
		delete[] _tree._values;
	}

	// Insert the value into the tree.
	bool insert(const value_type& value) {
		assert(Params::is_present(value));
		size_t new_H = height(_tree._n + 1);
		if (new_H > _tree._H) {
			resize(new_H);
		}
		assert(_tree._H > 0);
		cursor c(_tree);
		int comp;
		while (true) {
			if (!c.is_present()) {
				c.cur() = value;
				_tree._n++;
				return true;
			}
			comp = c.compare(value);
			if (comp == 0) {
				return false;
			}
			if (c.depth == _tree._H) {
				break;
			}
			if (comp < 0) {
				c.left();
			} else {
				c.right();
			}
		}
		// Find the rebalance point, compact the elements, and then redistribute them.
		value_type local_value = value;
		size_t count = find_rebalance_point(c);
		cursor values = compact(c, local_value);
		_tree._n++;
		distribute(c, count, values, c.depth);
		return true;
	}

	// Remove the value from the tree.
	bool remove(const value_type& value) {
		// TODO
		return false;
	}

	// Returns true if the tree contains the given value.
	bool contains(const value_type& value) const {
		if (_tree._n == 0) {
			return false;
		}
		cursor c(_tree);
		assert(c.is_present());
		while (c.is_present()) {
			int comp = c.compare(value);
			if (comp == 0) {
				return true;
			}
			if (c.depth == _tree._H) {
				break;
			}
			if (comp < 0) {
				c.left();
			} else {
				c.right();
			}
		}
		return false;
	}

private:
	cotree(const cotree&) = delete;
	void operator=(const cotree&) = delete;

public:
	// Return the height of a tree containing n nodes.
	static size_t height(size_t n) {
		return std::ceil(std::log2(n/_tau1 + 1));
	}

public: /* DEBUG */
	void print_tree() const {
		std::cout << "_n\t" << _tree._n << std::endl;
		std::cout << "_H\t" << _tree._H << std::endl;
		std::cout << "_BTD\t" << _tree._BTD << std::endl;
		std::cout << "_vals\t" << _tree._values << std::endl;
		print_inorder();
		check_invariants();
	}

	void print_inorder() const {
		if (_tree._n) {
			cursor c(_tree);
			std::cout << "  inorder: ";
			c.first_value();
			do {
				std::cout << c.cur() << " ";
			} while (c.next_value(1));
			std::cout << std::endl;
			std::cout << "  tree:";
			c.first_slot();
			do {
				std::cout << c.cur() << " ";
			} while (c.next_slot(1));
			std::cout << std::endl;
		}
	}

	void check_invariants() const {
		assert(_tree._n < 2 || _gammaH * ((1 << _tree._H) - 1) <= _tree._n);
		assert(_tree._n <= _tau1 * ((1 << _tree._H) - 1));
		assert(((1 << _tree._H) - 1) == (1 << _tree._H) - 1);
		assert(_tree._H <= std::log2(_tree._n + 1) + 2);

		assert(0.5 <= _tau1);
		assert(_tau1 == _tau(1));
		assert(_tree._H == 0 || _tau(1) <= _tau(_tree._H));
		assert(_tree._H == 0 || _tau(_tree._H) == 1);
		assert(_tree._H >= std::log2(_tree._n / _tau1 + 1));

		assert(0 <= _gammaH);
		assert(_tree._H == 0 || _gammaH == _gamma(_tree._H));
		assert(_gammaH < _gamma1);
		assert(_gamma(1) == _gamma1);
		assert(_gamma1 < _tau1);
	}

private:
	// Precompute the BTD arrays.
	void precompute_BTD() {
		_tree._BTD = new size_t[3 * _tree._H - 1];
		if (_tree._H > 1) {
			precompute_BTD_rec(1, _tree._H);
		}
	}

	// Precompute the BTD array entries for depths between d_top and
	// d_bottom in the van Emde Boas static tree, inclusive.
	void precompute_BTD_rec(unsigned d_top, unsigned d_bottom) {
		unsigned height = d_bottom - d_top + 1;
		unsigned h_top = (height + 1) / 2;
		unsigned d_bottom_half = d_top + h_top;
		unsigned base = 3 * (d_bottom_half - 2);
		_tree._BTD[base + 0] = (1 << (height - h_top)) - 1;
		_tree._BTD[base + 1] = (1 << h_top) - 1;
		_tree._BTD[base + 2] = d_top;
		if (d_top < d_bottom_half - 1) {
			precompute_BTD_rec(d_top, d_bottom_half - 1);
		}
		if (d_bottom_half < d_bottom) {
			precompute_BTD_rec(d_bottom_half, d_bottom);
		}
	}

	// Compute tau(d) for 1-indexed depth d.
	double _tau(unsigned d) const {
		return _tau1 + (d - 1) * (1 - _tau1) / (_tree._H - 1);
	}

	// Compute gamma(d) for 1-indexed depth d.
	double _gamma(unsigned d) const {
		return _gamma1 - (d - 1) * (_gamma1 - _gammaH) / (_tree._H - 1);
	}

	// Distribute the values from the given (forward) iterator into the
	// tree rooted at the given position.
	template<typename Iterator,
	         typename = typename std::enable_if<
	                 std::is_base_of<std::forward_iterator_tag,
	                                 typename std::iterator_traits<Iterator>::iterator_category
	                                >::value
	                                           >::type>
	void distribute(cursor& c, size_t n, Iterator& it) {
		size_t n_left = n / 2;
		size_t n_right = n - n_left - 1;
		if (n_left > 0) {
			c.left();
			distribute(c, n_left, it);
			c.up();
		}
		c.cur() = *it++;
		if (n_right > 0) {
			c.right();
			distribute(c, n_right, it);
			c.up();
		}
	}

	// Same thing, but where we're distributing from slots.
	void distribute(cursor& c, size_t n, cursor& v, size_t H) {
		size_t n_left = n / 2;
		size_t n_right = n - n_left - 1;
		if (n_left > 0) {
			c.left();
			distribute(c, n_left, v, H);
			c.up();
		}
		std::swap(c.cur(), v.cur());
		v.next_slot(H);
		if (n_right > 0) {
			c.right();
			distribute(c, n_right, v, H);
			c.up();
		}
	}

	// Resize the tree to a new height.
	void resize(size_t new_H) {
		tree old_tree = _tree;
		_tree._H = new_H;
		if (_tree._H > 0) {
			size_t N = (1 << _tree._H) - 1;
			_tree._values = new value_type[N];
			std::fill_n(_tree._values, N, Params::absent_value()); // TODO
			precompute_BTD();
		} else {
			_tree._values = nullptr;
			_tree._BTD = nullptr;
		}

		if (_tree._n > 0) {
			cursor values(old_tree);
			cursor slots(_tree);
			compact_into(values, slots);

			cursor tree(_tree);
			distribute(tree, _tree._n, slots, tree.depth);
		}

		delete[] old_tree._values;
		delete[] old_tree._BTD;
	}

	// Count the number of values in the subtree rooted at the cursor.
	size_t count(cursor c) {
		size_t total = 0;
		if (c.is_present()) {
			size_t H = c.depth;
			c.first_value();
			total++;
			while (c.next_value(H)) {
				total++;
			}
		}
		return total;
	}

	// Find the point at which we can rebalance and return the number of
	// elements in this subtree.
	size_t find_rebalance_point(cursor& c) {
		assert(c.depth == _tree._H);
		size_t nodes = 2; // The current (leaf) node and what will be its child.
		size_t size;
		double density;
		do {
			// Add the number of values in our sibling to the number of nodes.
			int path = c.path & 1;
			c.up();
			if (path == 0) {
				c.right();
			} else {
				c.left();
			}
			nodes += count(c) + 1;
			c.up();
			// Recalculate statistics.
			size = (1 << (_tree._H - c.depth + 1)) - 1;
			density = (double) nodes / size;
		} while (density > _tau(c.depth));
		return nodes;
	}

	// Compact the values in the given values cursor into the slots cursor.
	// The slots cursor must refer to a separate tree.
	static void compact_into(cursor& values, cursor& slots) {
		values.last_value();
		slots.last_slot();
		while (true) {
			std::swap(slots.cur(), values.cur());
			if (!values.prev_value(1)) {
				break;
			}
			slots.prev_slot(1);
		}
	}

	// Compact the subtree rooted at c into the rightmost section,
	// inserting value (whose original path would be path) along the way.
	static cursor compact(cursor values, value_type& extra) {
		// TODO: This is duplicate.
		size_t H = values.depth;
		cursor slots(values);
		values.last_value();
		slots.last_slot();
		while (true) {
			if (Params::is_present(extra) && values.compare(extra) > 0) {
				std::swap(slots.cur(), extra);
				if (slots.path == values.path && !values.prev_value(H)) {
					break;
				}
			} else {
				std::swap(slots.cur(), values.cur());
				if (!values.prev_value(H)) {
					break;
				}
			}
			slots.prev_slot(H);
		}
		if (Params::is_present(extra)) {
			slots.prev_slot(H);
			std::swap(slots.cur(), extra);
		}
		assert(!Params::is_present(extra));
		return slots;
	}
};

};

#endif
