#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int lcs(std::string s1, std::string s2) {
	int l1 = s1.length() + 1;
	int l2 = s2.length() + 1;

	int m[l1][l2];
	for (int i = 0; i < l1; i++) {
		m[i][0] = 0;
	}
	for (int i = 0; i < l2; i++) {
		m[0][i] = 0;
	}
	for (int i = 1; i < l1; i++) {
		for (int j = 1; j < l2; j++) {
			if (s1.at(i - 1) == s2.at(j - 1))
				m[i][j] = m[i - 1][j - 1] + 1;
			else
				m[i][j] = std::max(m[i][j - 1], m[i - 1][j]);
		}
	}
	return m[l1 - 1][l2 - 1];
}


int main() {
	int t;
	std::cin >> t;

	for (int i = 0; i < t; i++) {
		std::string s1;
		std::cin >> s1;

		std::string s2 = s1;
		std::reverse(s2.begin(), s2.end());

		int r = lcs(s1, s2);
		std::cout << r << "\n";
	}
}