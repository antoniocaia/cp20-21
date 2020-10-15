#include <iostream>
#include <vector>
#include <string>

/*


Time complexity: O(N)
Space complexity: O(N)
*/

int main()
{
	std::string in;
	std::cin >> in;
	int n = in.length();

	std::vector<int> sum_prefix;
	sum_prefix.reserve(n);
	int tmp_sum = 0;

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

		std::cout << sum_prefix[e - 1] - sum_prefix[s - 1] << "\n";
	}

	return 0;
}