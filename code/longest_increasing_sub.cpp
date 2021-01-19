#include <iostream>
#include <vector>

/*
time complexity: O(n^2)
space complexity: O(n)
*/

int64_t check(int a[], int i, std::vector<int64_t> &lis) {
	int64_t max = 0;
	for (int j = 0; j < i; j++) {
		if (a[j] < a[i] && lis[j] > max) {
			max = lis[j];
		}
	}
	return max + 1;
}

int longestSubsequence(int n, int a[])
{
	std::vector<int64_t> lis(n);
	for (int i = 0; i < n; i++) {
		lis[i] = check(a, i, lis);
	}

	// looks for max sol
	int64_t max = lis[0];
	for (int i = 1; i < n; i++) {
		if (max < lis[i]) max = lis[i];
	}
	return max;
}