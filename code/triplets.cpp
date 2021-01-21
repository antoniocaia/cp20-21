#include <iostream>
#include <vector>

/*
time complexity: O(n^2)
space complexity: O(n)

For each element x we count:
- how many elements greater than x are present in its suffix
- how many elements smaller than x are present in its prefix
We then calculate the number of triplets counting for each
element x all the combination assuming x as middle term.
*/

int main() {

	int64_t n = 0;
	std::cin >> n;

	std::vector<int64_t> in;
	in.reserve(n);

	for (int64_t i = 0; i < n; ++i) {
		int64_t x = 0;
		std::cin >> x;
		in.push_back(x);
	}

	std::vector<int64_t> l(n);
	std::vector<int64_t> r(n);

	for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (in[i] < in[j]) {
				l[i]++;
				r[j]++;
			}
		}
	}

	int64_t c = 0;

	for (int i = 0; i < n; ++i)
		c += l[i] * r[i];

	std::cout << c << "\n";
	return 0;
}