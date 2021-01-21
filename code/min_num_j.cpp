#include <iostream>
#include <vector>
#include <limits>

int minJumps(int arr[], int n) {
	int64_t long_max = std::numeric_limits<int64_t>::max();
	std::vector<int64_t> jumps(n, long_max);
	jumps[0] = 0;

	for (int i = 0; i < n - 1; i++) {
		if (jumps[i] != long_max) {
			int64_t dist = arr[i];
			for (int j = i + 1; j < i + 1 + dist; j++) {
				if (j < n)
					jumps[j] = std::min(jumps[j], jumps[i] + 1);
			}
		}
	}

	return jumps[n - 1];
}

int main() {
	int a[] = { 1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9 };
	std::cout << minJumps(a, 11);
}