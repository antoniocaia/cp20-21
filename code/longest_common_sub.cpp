/* 
// { Driver Code Starts
#include<bits/stdc++.h>
const int mod = 1e9 + 7;
using namespace std;

int lcs(int, int, string, string);

int main()
{
	int t, n, k, x, y;

	cin >> t;
	while (t--)
	{
		cin >> x >> y;          // Take size of both the strings as input
		string s1, s2;
		cin >> s1 >> s2;        // Take both the string as input

		cout << lcs(x, y, s1, s2) << endl;
	}
	return 0;
}
// } Driver Code Ends 
*/

// function to find longest common subsequence

int lcs(int x, int y, string s1, string s2) {
	int l1 = s1.length() + 1;
	int l2 = s2.length() + 1;

	int m[l1][l2];
	for (int i = 0; i < l1; i++) {
		m[i][0] = 0;
	}
	for (int i = 0; i < l2; i++) {
		m[0][i] = 0;
	}
	for(int i = 1; i < l1; i ++) {
		for(int j = 1; j < l2; j ++) {
			if(s1.at(i - 1) == s2.at(j - 1))
				m[i][j] = m[i-1][j-1] + 1;
			else 
				m[i][j] = std::max(m[i][j-1], m[i-1][j]);
		}
	}
	return m[l1-1][l2-1];
}