#include <iostream>
#include <vector>
#include <cmath>

#define LEFT(i)     (2 * i + 1)
#define RIGHT(i)    (2 * i + 2)

struct segment_tree {
	std::vector<int64_t> t;
	size_t size;

	segment_tree(size_t n) :t(pow(2, ceil(log2(n * 2 - 1))) - 1) {	size = n; }

	void _add(int64_t lq, int64_t rq, int64_t v, int64_t ln, int64_t rn, int64_t i) {
		// Query range and vector segment don't overlap: no update required
		if (lq > rn || rq < ln) return;
		// With a total or partial overlap we increase the current element
		t[i] += v;
		// Leaf: no more update required 
		if (rn == ln)  return;
		// General case
		int64_t mid = (ln + rn) / 2;
		_add(lq, rq, v, ln, mid, LEFT(i));
		_add(lq, rq, v, mid + 1, rn, RIGHT(i));
	}
	// Update the values in the range [lq,rq]
	void add(int64_t lq, int64_t rq, int64_t v) { _add(lq, rq, v, 0, size - 1, 0); }
	//update a single value q
	void add(int64_t q, int64_t v) { _add(q, q, v, 0, size - 1, 0); }

	int64_t _sum(int64_t lq, int64_t rq, int64_t ln, int64_t rn, int64_t i) {
		// Query range and vector segment don't overlap
		if (lq > rn || rq < ln) return 0;
		// Query range and vector segment perfectly overlap
		if (lq == ln && rq == rn) return t[i];
		// Query range and vector segment partially overlap
		int64_t mid = (ln + rn) / 2;
		return _sum(lq, std::min(mid, rq), ln, mid, LEFT(i)) + _sum(std::max(mid + 1, lq), rq, mid + 1, rn, RIGHT(i));
	}
	// Get the sum of the elements in the range [l,r]
	int64_t sum(int64_t l, int64_t r) {	return _sum(l, r, 0, size - 1, 0); }
};