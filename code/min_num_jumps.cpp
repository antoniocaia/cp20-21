#include <iostream>
#include <vector>
#include <limits>

/*
time complexity: O(n)
space complexity: O(1)


*/

int64_t minJumps(int arr[], int n) {
	int64_t avaiable_jumps = arr[0];
	int64_t total_jumps = 1;
	int64_t max_jumps = 0;

	for (int64_t i = 1; i < n; i++) {
		if (n - avaiable_jumps - i<= 0) return total_jumps; // Solution
		avaiable_jumps--;
		max_jumps--;
		if (avaiable_jumps < arr[i])
			max_jumps = max_jumps < arr[i] ? arr[i] : max_jumps;
		if (avaiable_jumps == 0) {
			avaiable_jumps = max_jumps;
			max_jumps = 0;
			total_jumps++;
		}
		if (avaiable_jumps <= 0) return -1;
	}
	return total_jumps;
}