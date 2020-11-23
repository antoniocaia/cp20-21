#include <iostream>
#include <vector>
#include <cmath>

/*
	Sum of elements in a sub-array [i, j]
	Add v to all elements in a sub-array [i, j]
*/

struct segment_tree {
	std::vector<std::vector<int64_t>> t;
	int64_t size;

	segment_tree(size_t n) : t(pow(2, ceil(log2(n * 2 - 1))) - 1) {
		size = n;
		for (int i = 0; i < t.size(); i++) {
			t[i].reserve(n);
			for (int j = 0; j < n; j++) {
				t[i].push_back(0);
			}
		}
	}

	void _add(int64_t lq, int64_t rq, int64_t v, int64_t ln, int64_t rn, int64_t i) {
		if (lq > rn || rq < ln) return;				// query range and vector segment don't overlap

		if (rn == ln) { 							// query range and vector segment perfectly overlap
			for (int j = 0; j < size; j++) {
				if (v <= j)
					t[i][j] = 1;
			}
			return;
		}

		for (int j = 0; j < size; j++) {
			if (v <= j)
				t[i][j] += 1;
		} 									// query range and vector segment partially overlap
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


	int64_t _sum(int64_t lq, int64_t rq, int64_t ln, int64_t rn, int64_t i, int64_t j) {
		if (lq > rn || rq < ln) return 0;  			// query range and vector segment don't overlap
		if (lq == ln && rq == rn) return t[i][j]; 		// query range and vector segment perfectly overlap

		int64_t mid = (ln + rn) / 2; 				// query range and vector segment partially overlap
		return _sum(lq, std::min(mid, rq), ln, mid, (i + 1) * 2 - 1, j) + _sum(std::max(mid + 1, lq), rq, mid + 1, rn, (i + 1) * 2, j);
	}

	int64_t sum(int64_t l, int64_t r, int64_t j) {
		return _sum(l, r, 0, size - 1, 0, j);
	}
};


int main() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int64_t> in;
	in.reserve(n);
	segment_tree t = segment_tree(n);

	for (int i = 0; i < n; i++) {
		int64_t x;
		std::cin >> x;
		in.push_back(x);
		t.add(i, x);
	}

	for (int i = 0; i < m; i++) {
		int64_t l, r, x;
		std::cin >> l >> r >> x;
		std::cout << t.sum(l, r, x) << "\n\n\n";
	}
}