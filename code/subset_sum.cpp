#include <iostream>
#include <vector>

class Solution {
public:
	int equalPartition(int N, int arr[])
	{
		int64_t sol = 0;
		for (int64_t i = 0; i < N; i++) {
			sol += arr[i];
		}

		if (sol % 2 != 0) return 0;
		else sol = sol / 2;

		int64_t m[N + 1][sol + 1];

		// col 0
		for (int64_t i = 0; i < N + 1; i++) {
			m[i][0] = 1;
		}

		// row 0
		for (int64_t j = 1; j < sol + 1; j++) {
			m[0][j] = 0;
		}

		for (int64_t i = 1; i < N + 1; i++) {
			for (int64_t j = 1; j < sol + 1; j++) {
				int t = j - arr[i - 1];
				if (t >= 0)
					m[i][j] = m[i - 1][t] || m[i - 1][j];
				else
					m[i][j] = m[i - 1][j];

			}
		}

		for (int64_t i = 0; i < N + 1; i++) {
			if (m[i][sol] == 1) return 1;
		}

		return 0;
	}
};

int main() {
	Solution s = Solution();
	int a[] = { 3, 2 ,5, 0 };
	std::cout << s.equalPartition(4, a);
}