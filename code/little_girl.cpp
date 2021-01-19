#include <iostream>
#include <vector>
#include <algorithm>

/*
time complexity: O(n log n)
space complexity: O(n)

For each element in the array we count how many times
they are included in a query using prefix sum. 
For each query left-edge we increase a corresponding counter, 
and for each query rigth-edge we decrease a corresponding counter.
Computing the prefix sum of this frequencies let us know the most 
"popular" positions of the array. We order the array so that 
the bigger values match the popular positions. To do this
we simply order the arrays with a time complexity of O( n log n)
*/

int main()
{
	int n;
	int q;
	std::cin >> n;
	std::cin >> q;

	std::vector<int64_t> num;
	num.reserve(n);

	for (int i = 0; i < n; i++) {
		int64_t x;
		std::cin >> x;
		num.push_back(x);
	}

	std::sort(num.begin(), num.end());

	std::vector<int> q_ind(n + 1);

	for (int i = 0; i < q; i++) {
		int l;
		int r;
		std::cin >> l;
		std::cin >> r;

		q_ind[l - 1]++;
		q_ind[r]--;
	}

	std::vector<int64_t> prefix_sum;
	prefix_sum.reserve(n);

	prefix_sum.push_back(q_ind[0]);
	for (int i = 1; i < n; i++) {
		prefix_sum.push_back(q_ind[i] + prefix_sum[i - 1]);
	}

	std::sort(prefix_sum.begin(), prefix_sum.end());

	int64_t tot = 0;
	for (int i = 0; i < n; i++) {
		tot += prefix_sum[i] * num[i];
	}

	std::cout << tot;
	return 0;
}