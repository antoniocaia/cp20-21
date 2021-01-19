#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

/*
time complexity: O(n log n)
space complexity: O(n)

This solution calculate the longest increasing
and decreasing sequence for each position, and
then put togheter the information in linear time
to find the longest bitonic sequence.
*/

class Solution {

private:
	void longest_subsequence(int n, std::vector<int> a, std::vector<int64_t>& li) {
		std::vector<int64_t> m(n + 1, 0);
		int64_t lis_leng = 0;

		for (int64_t i = 0; i < n; i++) {
			int64_t l = 1;
			int64_t r = lis_leng;

			while (l <= r) {
				int64_t mid = std::ceil((l + r) / 2);
				if (a[m[mid]] < a[i])
					l = mid + 1;
				else
					r = mid - 1;
			}
			m[l] = i;
			if (l > lis_leng)
				lis_leng = l;

			li[i] = l;
		}
	}

public:
	int LongestBitonicSequence(std::vector<int> nums) {
		int n = nums.size();

		std::vector<int64_t> li(n);
		longest_subsequence(n, nums, li);

		std::reverse(nums.begin(), nums.end());
		std::vector<int64_t> ld(n);
		longest_subsequence(n, nums, ld);

		int top = 0;
		for (int i = 0; i < n; i++) {
			int tmp = li[i] + ld[n - 1 - i] - 1;
			if (tmp > top)
				top = tmp;
		}
		return top;
	}
};