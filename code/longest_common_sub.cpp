#include <iostream>

/*
time complexity: O(n^2)
space complexity: O(n^2)

Using a DP approach we reduce the problem to the comparison 
of prefix. The element i,j in the matrix is the length 
of the longest common sequence between the sub-string 0..i of s1
and the sub-string 0..j of s2. When two elements are different, 
we simply propagate the length of the lcs.
When two elements are equal we increase the sequence checking the 
length of the lcs for the sub-strings 0..i-1 and 0..j-1.
*/

int lcs(int x, int y, std::string s1, std::string s2) {
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