#include <iostream>
#include <vector>
#include <algorithm>

/*
Time complexity: O
Space complexity: O

*/

int main()
{
	int n;
	std::cin >> n;

	std::vector<int64_t> num;
	num.reserve(n);
	std::vector<int64_t> c(n);

	for (int i = 0; i < n; i++) {
		int64_t x;
		std::cin >> x;
		num.push_back(x);
	}

	// Sum of all elements
	int64_t tot = 0;
	for (int i = 0; i < n; i++) {
		tot += num[i];
	}

	// Check if a solution exists
	if (tot % 3 != 0) {
		std::cout << 0;
		return 0;
	}
	// Sum of 1/3 array
	int64_t s = tot / 3;

	int64_t res = 0;
	int64_t sum = 0;

	for (int i = n - 1; i >= 0; i--) {
		sum += num[i];
		if (sum == s)
			c[i] = 1;
	}

	for (int i = n - 2; i >= 0; i--)
		c[i] += c[i + 1];

	sum = 0;
	for (int i = 0; i < n - 2; i++) {
		sum += num[i];
		if (sum == s) res += c[i + 2];
	}


	std::cout << res;
	return 0;
}