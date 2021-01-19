#include <iostream>
#include <vector>
#include <algorithm>

/*
time complexity: O(n)
space complexity: O(n)

We scan the vector from rigth to left and from left to rigth,
looking for all the possible sequence where the sum is 1/3 of the total.
Using prefix sum we can keep track of how many valid sequence 
we have until a given index.
With this approach we don't have to worry about the middle segment,
because if a solution exists, and the left and rigth segments are 1/3 of the total, 
then also the middle segment will be 1/3 of the total.
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
		if (sum == s) res += c[i + 2]; // +2 because at least 1 element is for the middle segment
	}


	std::cout << res;
	return 0;
}