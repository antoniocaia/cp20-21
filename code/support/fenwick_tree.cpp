#include <iostream>
#include <vector>

struct fenwick_tree {
	std::vector<int64_t> t;

	fenwick_tree(std::vector<int64_t> v) {
		t.reserve(v.size());
		for (int64_t x : v)
			t.push_back(x);
	}

	void insert(int64_t x) {
		t.push_back(x);
	}

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

	void print() {
		std::cout << "[ ";
		for (int i = 0; i < t.size(); i++) {
			std::cout << t[i] << " ";
		}
		std::cout << "]\n";
	}
};