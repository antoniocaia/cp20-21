#include <iostream>
#include <vector>

struct bst {
	std::vector<int64_t> b;

	bst(size_t n) : b(2 * n, -1) { }

	void insert(int64_t x) {
		int i = 0;
		while (b[i] != -1) {
			if (x > b[i])
				i = i * 2 + 2;
			else
				i = i * 2 + 1;
		}
		b[i] = x;
	}
};
