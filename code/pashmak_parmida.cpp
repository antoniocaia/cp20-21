#include <iostream>
#include <vector>
#include <algorithm>

/*
Time complexity: 
Space complexity:


*/

struct fenwick_tree {
	std::vector<int64_t> t;

	fenwick_tree(std::vector<int64_t> v) {
		t.reserve(v.size());
		for (int64_t x : v)
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
};

int main() {
	int n;
	std::cin >> n;

	std::vector<int64_t> v;
	v.reserve(n);
	for (int i = 0; i < n; i++)
	{
		int64_t x;
		std::cin >> x;
		v.push_back(x);
	}

	

	return 0;
}