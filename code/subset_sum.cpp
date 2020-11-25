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

		bool m[N + 1][sol + 1];

		for (int i = 0; i <= N; i++)
			m[i][0] = true;

		for (int i = 1; i <= sol; i++)
			m[0][i] = false;

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= sol; j++) {
				if (j < arr[i - 1])
					m[i][j] = m[i - 1][j];
				if (j >= arr[i - 1])
					m[i][j] = m[i - 1][j] || m[i - 1][j - arr[i - 1]];
			}
		}

		return m[N][sol];
	}
};

int main() {
	Solution s = Solution();
	int a[] = { 3, 2 ,5, 0 };
	std::cout << s.equalPartition(4, a);
}