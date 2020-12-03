/*
// { Driver Code Starts

#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
*/



class Solution {

private:
	int64_t checkShortestSubsequence(int n, std::vector<int> nums, int i, std::vector<int64_t>& lis) {
		int64_t max = 0;
		for (int j = n - 1; j > i; j--) {
			if (nums[j] < nums[i] && lis[j] > max) {
				max = lis[j];
			}
		}
		return max + 1;
	}

private:
	void shortestSubsequence(int n, std::vector<int> nums, std::vector<int64_t>& lis) {
		for (int i = n - 1; i >= 0; i--) {
			lis[i] = checkShortestSubsequence(n, nums, i, lis);
		}
	}

private:
	int64_t checkLongestSubsequence(int n, std::vector<int> nums, int i, std::vector<int64_t>& lis) {
		int64_t max = 0;
		for (int j = 0; j < i; j++) {
			if (nums[j] < nums[i] && lis[j] > max) {
				max = lis[j];
			}
		}
		return max + 1;
	}
private:
	void longestSubsequence(int n, std::vector<int> nums, std::vector<int64_t>& lis) {
		for (int i = 0; i < n; i++) {
			lis[i] = checkLongestSubsequence(n, nums, i, lis);
		}
	}

public:
	int LongestBitonicSequence(vector<int> nums)
	{
		int n = nums.size();
		nums.push_back(0);

		std::vector<int64_t> lis(n + 1);
		longestSubsequence(n, nums, lis);

		std::vector<int64_t> sis(n + 1);
		shortestSubsequence(n, nums, sis);

		int top = 0;
		for (int i = 0; i < n + 1; i++) {
			for (int j = i + 1; j < n + 1; j++) {
				int tmp = lis[i] + sis[j];
				if (nums[i] > nums[j]) {
					if (tmp > top)
						top = tmp;
				}
			}
		}
		return top;
	}
};

/*
// { Driver Code Starts.
int main() {
	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		vector<int>nums(n);
		for (int i = 0; i < n; i++)
			cin >> nums[i];
		Solution ob;
		int ans = ob.LongestBitonicSequence(nums);
		cout << ans << "\n";
	}
	return 0;
}  // } Driver Code Ends

*/