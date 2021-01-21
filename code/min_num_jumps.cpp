#include <iostream>

/*
time complexity: O(n)
space complexity: O(i)

While moving forward we store the best candidate for the next jump, 
ie the position that let us move further. Moving forward we need to reduce both 
the current avaiable jumps and the jumps avaiable after we decide where to 
move.

*/

int minJumps(int arr[], int n) {
	int64_t avaiable_jumps = 0;
	int64_t total_jumps = 0;
	int64_t next_jumps = 0;

	for (int64_t i = 0; i < n; i++) {
		if (avaiable_jumps < arr[i])	// Keep track of the next best jump to perform
			next_jumps = next_jumps < arr[i] ? arr[i] : next_jumps;

		if (avaiable_jumps == 0) {		// When we can't advance anymore...
			avaiable_jumps = next_jumps;
			next_jumps = 0;
			total_jumps++;
			if (n - avaiable_jumps - i - 1 <= 0) return total_jumps;  // After updating the range, check if we can reach the end
			if (avaiable_jumps <= 0) return -1;	// If we can't move anymore, return -1
		}

		avaiable_jumps--;	// Simulate a step forward
		next_jumps--;
	}
	return total_jumps;
}