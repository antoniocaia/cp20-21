#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
	int n;
	std::cin >> n;

	std::vector<int64_t> num;
	num.reserve(n);

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

	// Check for the first 1/3
	int64_t part_sum = 0;
	int i = 0;
	while (part_sum != s) {
		part_sum += num[i];
		i++;
	}

	// Check for the second 1/3
	part_sum = 0;
	int j = n - 1;
	while (part_sum != s) {
		part_sum += num[i];
		i--;
	}

	// Check for all the possible combinations
	int res = 0;
	part_sum = 0;
	for(int x = i; x <= j; x++) {
		part_sum += num[x];
		if(part_sum == 0 || part_sum == s) {
			res += 2;
		}
	}

	std::cout << res;
	return 0;
}