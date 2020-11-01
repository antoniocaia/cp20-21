#include <iostream>
#include <vector>

/*


Time complexity: O(N)
Space complexity: O(N)
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

int main()
{
	int tc;
	std::cin >> tc;

	for (int t = 0; t < tc; t++) {
		int n, u;
		std::cin >> n >> u;

		std::vector<int64_t> tmp(n + 2);
		fenwick_tree ft(tmp);

		for (int i = 0; i < u; i++) {
			int64_t l, r, v;
			std::cin >> l >> r >> v;

			ft.add(l, v);
			ft.add(r + 1, -v);
		}

		int q;
		std::cin >> q;

		for (int i = 0; i < q; i++) {
			int ind;
			std::cin >> ind;
			std::cout << ft.sum(ind) << "\n";
		}
	}

}