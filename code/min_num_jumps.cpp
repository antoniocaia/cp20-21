#include <iostream>

/*
time complexity: O(n)
space complexity: O(1)

While moving forward we store the best candidate for the next jump, 
ie the position that let us move further. Moving forward we need to reduce both 
the current avaiable jumps and the jumps avaiable after we decide where to 
move. 
This solution works because it's pointless to jump in a position 
that offere us a reach that isn't the biggest one.
*/

int minJumps(int arr[], int n) {
	int64_t avaiable_reach = 0;
	int64_t total_jumps = 0;
	int64_t next_reach = 0;

	for (int64_t i = 0; i < n; i++) {
		if (avaiable_reach < arr[i])	// Keep track of the next best jump to perform
			next_reach = next_reach < arr[i] ? arr[i] : next_reach;

		if (avaiable_reach == 0) {		// When we can't advance anymore...
			avaiable_reach = next_reach;
			next_reach = 0;
			total_jumps++;
			if (n - avaiable_reach - i - 1 <= 0) return total_jumps;  // After updating the range, check if we can reach the end
			if (avaiable_reach <= 0) return -1;	// If we can't move anymore, return -1
		}

		avaiable_reach--;	// Simulate a step forward
		next_reach--;
	}
	return total_jumps;
}