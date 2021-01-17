#include <iostream>
#include <vector>
#include <string>

/*
Time complexity: O(n)
Space complexity: O(n)

We scan the string comparing consecutive char.
Every time two consecutive char are identical, 
we increase a counter. For each iteration, 
we update the prefix sum array pushing the current 
value of the counter.

To process a query, we take the two value indicated 
in the query and subtract them.
*/

int main()
{
	// Input
	std::string in;
	std::cin >> in;
	int n = in.length();

	std::vector<int> sum_prefix;
	sum_prefix.reserve(n);
	int tmp_sum = 0;

	/* Scan the string, and if two consecutive char are identical increase the counter 
	   and push it in the prefix_sum array */
	sum_prefix.push_back(0);
	for (int i = 0; i < n - 1; i++) {
		if (in[i] == in[i + 1])
			tmp_sum += 1;

		sum_prefix.push_back(tmp_sum);
	}

	int tests;
	std::cin >> tests;

	for (int t = 0; t < tests; t++)
	{
		int s;
		int e;
		std::cin >> s;
		std::cin >> e;

		// Query processing
		std::cout << sum_prefix[e - 1] - sum_prefix[s - 1] << "\n";
	}

	return 0;
}