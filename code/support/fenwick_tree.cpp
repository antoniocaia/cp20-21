#include <iostream>
#include <vector>

struct fenwick_tree {
	std::vector<int64_t> t;

	fenwick_tree(size_t n) : t(n + 1) {}

	int64_t sum(int64_t i) {
		int64_t sum = 0;
		i++;
		while (i > 0) {
			sum += t[i];
			i -= i & -i;
		}
		return sum;
	}
	
	void add(int64_t i, int64_t v) {
		i++;
		while (i < t.size()) {
			t[i] += v;
			i += i & -i;
		}
	}
};