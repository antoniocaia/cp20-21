#include <iostream>
#include <vector>
#include <cstdlib>

/*
time complexity: O(n)
space complexity: O(1)

The allowed operations let us modify only the suffix of a given index.
This means that we can edit the first element of the array only increasing 
or decreasing the element of index 0 (and is suffix).
When we are done with the first element, we can adjust the second one, 
but we have to treat it as the "new" first element of the array because 
we don't want edit the previous elements. 
After changing an index, its suffix as the same value. 
For this reason, we can calculate the number of operation as the 
difference between elements.
*/

int main() {
	int64_t n;
	std::cin >> n;
	std::vector<int64_t> v;
	v.reserve(n);

	for (int i = 0; i < n; i++) {
		int64_t x;
		std::cin >> x;
		v.push_back(x);
	}

	int64_t r = std::abs(v[0]);
	for (int64_t i = 0; i < v.size() - 1; i++) {
		r += std::abs(v[i + 1] - v[i]);				
	}
	std::cout << r;
}