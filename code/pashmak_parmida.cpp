#include <iostream>
#include <vector>
#include <algorithm>
#include <set> 
using namespace std;

#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <algorithm>
/*
Time complexity:
Space complexity:


*/

struct fenwick_tree {
	std::vector<int64_t> t;

	fenwick_tree(int64_t n) : t(n + 1) { }

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
	int64_t n;
	std::cin >> n;

	std::vector<int64_t> v;
	v.reserve(n);
	for (int i = 0; i < n; i++) {
		int64_t x;
		std::cin >> x;
		v.push_back(x);
	}

	// Remap
	std::vector<int64_t> remap = v;
	sort(remap.begin(), remap.end());
	std::vector<int64_t>::iterator tmp = std::unique(remap.begin(), remap.end());
	int64_t new_size = std::distance(remap.begin(), tmp);
	remap.resize(new_size);

	for (int i = 0; i < v.size(); i++) {
		for(int j = 0; j < remap.size(); j ++) {
			if(remap[j] == v[i]) v[i] = j;
		}
	}

	std::vector<int64_t> suffix_counter(v.size());

	return 0;
}	