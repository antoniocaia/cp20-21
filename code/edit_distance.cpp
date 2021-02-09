#include <iostream>
#include <string>

/*
time complexity: O(n^2)
space complexity: O(n^2)



*/

class Solution
{
public:
	int editDistance(std::string s, std::string t)
	{
		const int s_len = s.size();
		const int t_len = t.size();

		int m[s_len + 1][t_len + 1];
		std::fill(*m, *m + (s_len + 1) * (t_len + 1), 0);

		for (int i = 1; i <= s_len; i++) {
			m[i][0] = i;
		}
		for (int i = 1; i <= t_len ; i++) {
			m[0][i] = i;
		}

		for (int i = 1; i <= s_len; i++) {
			for (int j = 1; j <= t_len; j++) {
				if (s[i - 1] == t[j - 1])
					m[i][j] = m[i - 1][j - 1];
				else
					m[i][j] = std::min(std::min(m[i - 1][j], m[i][j - 1]), m[i - 1][j - 1]) + 1;
			}
		}
		return m[s_len][t_len];
	}
};