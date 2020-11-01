#include <iostream>
#include <vector>
#include <cmath>

struct segment_tree {
	std::vector<int64_t> t;
	int64_t size;

	segment_tree(size_t n) : t(pow(2, ceil(log2(n * 2 - 1))) - 1) { size = n; }

	void aadd(int64_t q, int64_t v, int64_t ln, int64_t rn, int64_t i) {
		if (q > rn || q < ln) return; 

		if (rn == ln && rn == q) {
			t[i] += v;
			return;
		}

		t[i] += v;
		int64_t mid = (ln + rn) / 2;
		aadd(q, v, ln, mid, (i + 1) * 2 - 1);
		aadd(q, v, mid + 1, rn, (i + 1) * 2);
	}

	void add(int64_t q, int64_t v) {
		aadd(q, v, 0, size - 1, 0);
	}


	int64_t ssum(int64_t lq, int64_t rq, int64_t ln, int64_t rn, int64_t i) {
		if (lq > rn || rq < ln) return 0;
		if (lq == ln && rq == rn) return t[i];

		int64_t mid = (ln + rn) / 2;
		return ssum(lq, std::min(mid, rq), ln, mid, (i + 1) * 2 - 1) + ssum(std::max(mid + 1, lq), rq, mid + 1, rn, (i + 1) * 2);
	}

	int64_t sum(int64_t l, int64_t r) {
		return ssum(l, r, 0, size - 1, 0);
	}

	void print() {
		std::cout << "[ ";
		for (int i = 0; i < t.size(); i++) {
			std::cout << t[i] << " ";
		}
		std::cout << "]\n";
	}
};

