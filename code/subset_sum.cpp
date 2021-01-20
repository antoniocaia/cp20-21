#include <iostream>
#include <vector>

/*
time complexity: O(n * sum of elements)
space complexity: O(n * sum of elements)

First we divide the sum of the elements by two to
find the expected value s that each subset has to
reach. Then using a matrix of n + 1 rows and s + 1
columns we check for each subset which values can
be obtained. We start from the empty set, and for
each new element in the set we need two controls:
- if the element is bigger than the value that we
want reach we check in the previuos subset if the 
value is already present.
- if the element is smaller than the value that we
want reach we check in the previuos subset if the 
value is already present or if it's possible to 
obtain x such that x + element = value.
*/

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
				else 	if (j >= arr[i - 1])
					m[i][j] = m[i - 1][j] || m[i - 1][j - arr[i - 1]];
			}
			if (m[i][sol] == true) return true;		// As soon as we find a solution we can return true;
		}

		return m[N][sol];
	}
};
