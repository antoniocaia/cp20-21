#include <iostream>
#include <vector>
#include <cmath>

/*
time complexity: O(n log n)
space complexity: O(n)

We use a vector m to store the index of the elements
such that the elements result ordered.
We start to build the lsi from the first element of the array.
When scanning a new element we use a binary search to
find in m the smaller element bigger then the
current one. If no element is found, the new one is add in m;
otherwise we replace the element with the current one.
With this approach we are sure that we always have in m a
sequence containing the smallest values possible, thus with more
potential.

Example: [0 8 9 3 4...]
Both [0 8 9] and [0 3 4] are valid sequence, but it's pointless to
keep track of [0 8 9]  when [0 3 4] admit more possible values.
*/

int longestSubsequence(int n, int a[])
{
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
	}
	return lis_leng;
}