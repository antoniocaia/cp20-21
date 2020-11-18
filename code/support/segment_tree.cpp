#include <iostream>
#include <vector>
#include <cmath>

/*
	Sum of elements in a sub-array [i, j]
	Add v to all elements in a sub-array [i, j]
*/

struct segment_tree {
	std::vector<int64_t> t;
	int64_t size;

	segment_tree(size_t n) : t(pow(2, ceil(log2(n * 2 - 1))) - 1) { size = n; }

	void _add(int64_t lq, int64_t rq, int64_t v, int64_t ln, int64_t rn, int64_t i) {
		if (lq > rn || rq < ln) return;				// query range and vector segment don't overlap

		if (rn == ln) { 							// query range and vector segment perfectly overlap
			t[i] += v;
			return;
		}

		t[i] += v; 									// query range and vector segment partially overlap
		int64_t mid = (ln + rn) / 2;
		_add(lq, rq, v, ln, mid, (i + 1) * 2 - 1);
		_add(lq, rq, v, mid + 1, rn, (i + 1) * 2);
	}

	void add(int64_t lq, int64_t rq, int64_t v) {
		_add(lq, rq, v, 0, size - 1, 0);
	}

	void add(int64_t q, int64_t v) {
		_add(q, q, v, 0, size - 1, 0);
	}


	int64_t _sum(int64_t lq, int64_t rq, int64_t ln, int64_t rn, int64_t i) {
		if (lq > rn || rq < ln) return 0;  			// query range and vector segment don't overlap
		if (lq == ln && rq == rn) return t[i]; 		// query range and vector segment perfectly overlap

		int64_t mid = (ln + rn) / 2; 				// query range and vector segment partially overlap
		return _sum(lq, std::min(mid, rq), ln, mid, (i + 1) * 2 - 1) + _sum(std::max(mid + 1, lq), rq, mid + 1, rn, (i + 1) * 2);
	}

	int64_t sum(int64_t l, int64_t r) {
		return _sum(l, r, 0, size - 1, 0);
	}

	void print() {
		std::cout << "\n[ ";
		for (int i = 0; i < t.size(); i++) {
			std::cout << t[i] << " ";
		}
		std::cout << "]\n";
	}
};

