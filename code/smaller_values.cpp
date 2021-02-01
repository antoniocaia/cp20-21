#include <iostream>
#include <vector>
#include <cmath>

/*
time complexity: O((n + m) n^1/2 log n)
space complexity: O(n)

We store for each node in the segment tree a vector vt. 
For each position j in vt we store the number of elements 
in the input array smaller than j.

When processing a query, se simply retrive from the vectors
vt the number of elements smaller than x.
*/

#define LEFT(i)     (2 * i + 1)
#define RIGHT(i)    (2 * i + 2)

struct segment_tree {
	std::vector<std::vector<int64_t>> t;
	int64_t size;

	segment_tree(size_t n) : t(pow(2, ceil(log2(n * 2 - 1))) - 1) {
		size = n;
		for (int i = 0; i < t.size(); i++) t[i] = std::vector<int64_t>(n);
	}

	void _add(int64_t q, int64_t x, int64_t ln, int64_t rn, int64_t i) {
		if (q > rn || q < ln) return;
		if (rn == ln) {
			for (int j = x; j < size; j++)
				t[i][j] = 1;
			return;
		}

		for (int j = x; j < size; j++)
				t[i][j] += 1;

		int64_t mid = (ln + rn) / 2;
		_add(q, x, ln, mid, LEFT(i));
		_add(q, x, mid + 1, rn, RIGHT(i));
	}
	void add(int64_t q, int64_t x) { _add(q, x, 0, size - 1, 0); }

	int64_t _smaller(int64_t lq, int64_t rq, int64_t ln, int64_t rn, int64_t i, int64_t x) {
		if (lq > rn || rq < ln) return 0;
		if (lq == ln && rq == rn) return t[i][x];

		int64_t mid = (ln + rn) / 2;
		return _smaller(lq, std::min(mid, rq), ln, mid, LEFT(i), x) + _smaller(std::max(mid + 1, lq), rq, mid + 1, rn, RIGHT(i), x);
	}
	int64_t smaller(int64_t l, int64_t r, int64_t x) { return _smaller(l, r, 0, size - 1, 0, x); }
};


int main() {
	int n, m;
	std::cin >> n >> m;
	segment_tree t = segment_tree(n);

	for (int i = 0; i < n; i++) {
		int64_t x;
		std::cin >> x;
		t.add(i, x);
	}

	for (int i = 0; i < m; i++) {
		int64_t l, r, x;
		std::cin >> l >> r >> x;
		std::cout << t.smaller(l, r, x) << "\n";
	}
}