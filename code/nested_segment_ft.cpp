#include <iostream>
#include <vector>
#include <algorithm>

/*
time complexity: O(n log n)
space complexity: O(n)

We map the value in a range 0..2n-1.
Using a Fenwick tree we keep track and increase the rigth index, 
allowing us to count how many segment ends before each one.
Using a sweep line approach we evaluate the number of nested segment
and reduce the rigth index (all the following nested segment will ignore it) 
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

struct fenwick_tree {
	std::vector<int64_t> t;

	fenwick_tree(size_t n) : t(n + 1) {}

	int64_t sum(int i) {
		int64_t sum = 0;
		i++;
		while (i > 0) {
			sum += t[i];
			i -= i & -i;
		}
		return sum;
	}

	void add(int i, int64_t v) {
		i++;
		while (i < t.size()) {
			t[i] += v;
			i += i & -i;
		}
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

	// Fenwick tree
	fenwick_tree ft = fenwick_tree(2 * n);
	// Increasing the rigth index allow us to count how many segment ends before each one
	for (int i = 0; i < n; i++) {
		ft.add(input[i].r, 1);
	}

	std::vector<segment> res;
	res.reserve(n);
	/* Using a sweep line approach we evaluate the number of nested segment
	   and reduce the rigth index (all the following nested segment will ignore it) */
	for (int i = 0; i < sup.size(); i++) {
		if (sup[i].t == 0) {
			int64_t ind = sup[i].ind;
			ft.add(input[ind].r, -1);
			//!!! segment in this case is used to store the solution with the rigth index, it's not actually a segment
			res.push_back(segment(ind, ft.sum(input[ind].r)));
		}
	}

	sort(res.begin(), res.end(), comp_se);

	for (int i = 0; i < res.size(); i++) {
		std::cout << res[i].r << "\n";
	}

	return 0;
}