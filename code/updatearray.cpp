#include <iostream>
#include <vector>
#include <algorithm>

/*

Time complexity: O
Space complexity: O
*/

int main()
{
	int tc;
	std::cin >> tc;

	for (int t = 0; t < tc; t++) {
		int n, u;
		std::cin >> n >> u;
		std::vector<int64_t> num(n + 1);

		for (int i = 0; i < u; i++) {
			int64_t l, r, v;
			std::cin >> l >> r >> v;

			num[l] += v;
			num[r + 1] += -v;
		}

		std::vector<int64_t> prefix;
		prefix.reserve(n);
		prefix.push_back(num[0]);
		for (int i = 1; i < n; i++) {
			int64_t tmp = prefix[i - 1] + num[i];
			prefix.push_back(tmp);
		}

		int q;
		std::cin >> q;

		for (int i = 0; i < q; i++) {
			int ind;
			std::cin >> ind;
			std::cout << prefix[ind] << "\n";
		}
	}

}