#include <iostream>
#include <vector>

/*
time complexity: O(n^2)
space complexity: O(n)

This solution calculate the longest increasing
and decreasing sequence for each position, and
then put togheter the information in linear time
to find the longest bitonic sequence.
*/

class Solution {

private:
	void subsequences(int n, std::vector<int> nums, std::vector<int64_t>& li, std::vector<int64_t>& ld) {
		for (int i = 0; i < n; i++) {
			int64_t inc = 0;
			int64_t dec = 0;
			for (int j = 0; j < i; j++) {
				if (nums[j] < nums[i] && li[j] > inc) inc = li[j];
				if (nums[n - 1 - j] < nums[n - 1 - i] && ld[n - 1 - j] > dec) dec = ld[n - 1 - j];
			}
			li[i] = inc + 1;
			ld[n - 1 - i] = dec + 1;
		}
	}

public:
	int LongestBitonicSequence(std::vector<int> nums)
	{
		int n = nums.size();
		nums.push_back(0);

		std::vector<int64_t> li(n + 1);
		std::vector<int64_t> ld(n + 1);
		subsequences(n, nums, li, ld);

		int top = 0;
		for (int i = 0; i < n + 1; i++) {
			int tmp = li[i] + ld[i] - 1;
			if (tmp > top)
				top = tmp;
		}
		return top;
	}
};