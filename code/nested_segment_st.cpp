#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

/*
Time complexity: O(N log N)
Space complexity: O( pow(2, ceil(log2(n * 2 - 1))) - 1 )


*/

// Store the left and right index of a segment
struct segment {
	int64_t l;
	int64_t r;

	segment(int64_t ll, int64_t rr) {
		l = ll;
		r = rr;
	}
};

bool comp_se(segment a, segment b) {
	return a.l < b.l;
};

/* Support struct that memorize:
   - the type of and index (left 0, rigth 1)
   - the index of the corrispondenting segment
   - the value of the index */
struct  support {
	int t;
	int ind;
	int64_t val;

	support(int tt, int i, int v) {
		t = tt;
		ind = i;
		val = v;
	}
};

bool comp_su(support a, support b) {
	return a.val < b.val;
};

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
};

int main() {
	int n;
	std::cin >> n;

	// Map the segments index in a 0..2n-1 range
	std::vector<support> sup;
	sup.reserve(2 * n);
	std::vector<segment> input;
	input.reserve(n);
	for (int i = 0; i < n; i++)
	{
		int64_t l, r;
		std::cin >> l >> r;
		sup.push_back(support(0, i, l));
		sup.push_back(support(1, i, r));
		input.push_back(segment(l, r));
	}

	sort(sup.begin(), sup.end(), comp_su);
	for (int i = 0; i < sup.size(); i++) {
		if (sup[i].t == 0)
			input[sup[i].ind].l = i;
		else
			input[sup[i].ind].r = i;

		sup[i].val = i;
	}

	// Segment tree
	segment_tree st = segment_tree(2 * n);
	// Increasing the rigth index allow us to count how many segment ends before each one
	for (int i = 0; i < n; i++) {
		st.add(input[i].r, 1);
	}

	std::vector<segment> res;
	res.reserve(n);
	/* Using a sweep line approach we evaluate the number of nested segment
	   and reduce the rigth index (all the following nested segment will ignore it) */
	for (int i = 0; i < sup.size(); i++) {
		if (sup[i].t == 0) {
			int64_t ind = sup[i].ind;
			st.add(input[ind].r, -1);
			// segment in this case is used to store the solution with the proper index, it's not actually a segment
			res.push_back(segment(ind, st.sum(0, input[ind].r)));
		}
	}

	sort(res.begin(), res.end(), comp_se);

	for (int i = 0; i < res.size(); i++) {
		std::cout << res[i].r << "\n";
	}

	return 0;
}