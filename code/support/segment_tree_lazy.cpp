#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

/*
Prop: Circular, Lazy
Op: Min,  Add
*/

#define LEFT(i)     (2 * i + 1)
#define RIGHT(i)    (2 * i + 2)

struct segment_tree {
	std::vector<int64_t> t;
	std::vector<int64_t> lazy;
	int64_t size;
	int64_t max = std::numeric_limits<int64_t>::max();

	segment_tree(size_t n) : t(pow(2, ceil(log2(n * 2 - 1)))) { lazy = t; size = n; }

	void _add(int64_t lq, int64_t rq, int64_t v, int64_t ln, int64_t rn, int64_t i) {
		if (lazy[i] != 0) {
			t[i] += lazy[i];

			if (rn != ln) {
				lazy[LEFT(i)] += lazy[i];
				lazy[RIGHT(i)] += lazy[i];
			}
			lazy[i] = 0;
		}

		if (lq > rn || rq < ln) return;
		if (ln >= lq && rn <= rq) {
			t[i] += v;

			if (rn != ln) {
				lazy[LEFT(i)] += v;
				lazy[RIGHT(i)] += v;
			}
			return;
		}

		int64_t mid = (ln + rn) / 2;
		_add(lq, rq, v, ln, mid, LEFT(i));
		_add(lq, rq, v, mid + 1, rn, RIGHT(i));

		t[i] = std::min(t[LEFT(i)], t[RIGHT(i)]);
	}

	void add(int64_t lq, int64_t rq, int64_t v) {
		if (lq <= rq)
			_add(lq, rq, v, 0, size - 1, 0);
		else {
			_add(0, rq, v, 0, size - 1, 0);
			_add(lq, size - 1, v, 0, size - 1, 0);
		}
	}

	void add(int64_t q, int64_t v) {
		_add(q, q, v, 0, size - 1, 0);
	}

	// Min value in a sub-array
	int64_t _min(int64_t lq, int64_t rq, int64_t ln, int64_t rn, int64_t i) {
		if (lazy[i] != 0) {
			t[i] += lazy[i];
			if (ln != rn) {
				lazy[LEFT(i)] += lazy[i];
				lazy[RIGHT(i)] += lazy[i];
			}
			lazy[i] = 0;
		}

		if (lq > rn || rq < ln) return max;									// query range and vector segment don't overlap
		if (lq == ln && rq == rn) return t[i];								// query range and vector segment perfectly overlap

		int64_t mid = (ln + rn) / 2; 										// query range and vector segment partially overlap
		return std::min(_min(lq, std::min(mid, rq), ln, mid, (i + 1) * 2 - 1), _min(std::max(mid + 1, lq), rq, mid + 1, rn, (i + 1) * 2));
	}

	int64_t min(int64_t l, int64_t r) {
		if (l <= r)
			return _min(l, r, 0, size - 1, 0);
		return std::min(_min(0, r, 0, size - 1, 0), _min(l, size - 1, 0, size - 1, 0));
	}
};