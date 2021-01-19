#include <iostream>
#include <string>
#include <algorithm>

/*
time complexity: O(n^2)
space complexity: O(n^2)

We use the same approach used to find the longest common 
subsequence between to string, but instead of using two strings
we scan the same string from the start to the end and from
the end to the start.
*/
int lcs(std::string s1) {
	int l1 = s1.length() + 1;

	int m[l1][l1];
	for (int i = 0; i < l1; i++) {
		m[i][0] = 0;
		m[0][i] = 0;
	}

	for (int i = 1; i < l1; i++) {
		for (int j = 1; j < l1; j++) {
			if (s1.at(i - 1) == s1.at(s1.length() - j))
				m[i][j] = m[i - 1][j - 1] + 1;
			else
				m[i][j] = std::max(m[i][j - 1], m[i - 1][j]);
		}
	}
	return m[l1 - 1][l1 - 1];
}


int main() {
	int t;
	std::cin >> t;

	for (int i = 0; i < t; i++) {
		std::string s1;
		std::cin >> s1;

		int r = lcs(s1);
		std::cout << r << "\n";
	}
}