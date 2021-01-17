#include <iostream>
#include <vector>
#include <map>

/*
Time complexity: O(n log x)
Space complexity: O(x)

We use two index to keep track of the start and end of a sub-array.
To keep track of the number of element in a sub-array we use a map
that associate a value with the number of its occurrences.
When we reach the limit of different value k,
we can start to shrink the window moving to the right the starting index
and removing the value that aren't int he window.
We remove an element from the map only when the number of occurrences is zero.

Because each iteration we move at least one index to the rigth,
and the strating index can't be biggere then the ending one,
we have a complexity of O(n log x) where O(log x) is the cost of calling find() on the map.
*/


void update_map(int v, std::map<long, int>& freq) {
	std::map<long, int>::iterator it = freq.find(v);
	it->second--;
	if (it->second == 0)
		freq.erase(v);
}


int main() {

	int n;
	int k;
	scanf("%d", &n);
	scanf("%d", &k);

	std::vector<long> num;
	num.reserve(n);

	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		num.push_back(x);
	}

	int s = 0;
	int e = 0;

	std::map<long, int> freq;
	std::map<long, int>::iterator it;

	int s_r = 0;
	int e_r = 0;

	while (e < n) {
		it = freq.find(num[e]);
		if (it != freq.end()) { // If the element is already in the map
			it->second += 1;
			e++;
		}
		else { // If the element isn't in the map
			if (freq.size() < k) {	// If the number of elements is smaller than k
				freq.insert({ num[e], 1 });
				e++;
			}
			else { // If the number of elements is already k
				while (freq.size() >= k) {
					update_map(num[s], freq);
					s++;
				}
				freq.insert({ num[e], 1 });
				e++;
			}
		}

		if (e - s > e_r - s_r) {
			e_r = e;
			s_r = s;
		}
	}

	printf("%d %d", s_r + 1, e_r);
}