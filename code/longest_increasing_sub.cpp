/*
// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

int longestSubsequence(int, int[]);

int main()
{
	//taking total testcases
	int t, n;
	cin >> t;
	while (t--)
	{
		//taking size of array
		cin >> n;
		int a[n];

		//inserting elements to the array
		for (int i = 0;i < n;i++)
			cin >> a[i];

		//calling method longestSubsequence()
		cout << longestSubsequence(n, a) << endl;
	}
}
// } Driver Code Ends
*/

/*
Time: 0.29

*/

int64_t check(int n, int a[], int i, std::vector<int64_t> &lis) {
	int64_t max = 0;
	for (int j = 0; j < i; j++) {
		if (a[j] < a[i] && lis[j] > max) {
			max = lis[j];
		}
	}
	return max + 1;
}

int longestSubsequence(int n, int a[])
{
	std::vector<int64_t> lis(n);
	for (int i = 0; i < n; i++) {
		lis[i] = check(n, a, i, lis);
	}

	// looks for max sol
	int64_t max = lis[0];
	for (int i = 1; i < n; i++) {
		if (max < lis[i]) max = lis[i];
	}
	return max;
}