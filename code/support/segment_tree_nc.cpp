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
		if (lq > rn || rq < ln) return;
		t[i] += v;
		if (rn == ln)  return;
		int64_t mid = (ln + rn) / 2;
		_add(lq, rq, v, ln, mid, LEFT(i));
		_add(lq, rq, v, mid + 1, rn, RIGHT(i));
	}
	void add(int64_t lq, int64_t rq, int64_t v) { _add(lq, rq, v, 0, size - 1, 0); }
	void add(int64_t q, int64_t v) { _add(q, q, v, 0, size - 1, 0); }

	int64_t _sum(int64_t lq, int64_t rq, int64_t ln, int64_t rn, int64_t i) {
		if (lq > rn || rq < ln) return 0;
		if (lq == ln && rq == rn) return t[i];
		int64_t mid = (ln + rn) / 2;
		return _sum(lq, std::min(mid, rq), ln, mid, LEFT(i)) + _sum(std::max(mid + 1, lq), rq, mid + 1, rn, RIGHT(i));
	}
	int64_t sum(int64_t l, int64_t r) {	return _sum(l, r, 0, size - 1, 0); }
};