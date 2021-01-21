#include <iostream>
#include <vector>
#include <algorithm>

/*
time complexity: O(n * c)
space complexity: O(n * c)

First, we sort the items by increasing size.
Then, we build a matrix [n][c + 1].
Each time we try to put a new item in the subset
we keep track of the result for all the possible 
capacity in the range 0..c. 
When the weight of the new value is bigger than 
the avaiable capacity we simply copy the result of
the previous subset.  
When the weight of the new value is smaller or equals
than the avaiable capacity we select the max between:
- the result of the prevous subset 
- the value of the new items plus the result from the 
prevous sub set for the remaining space given the new item
*/

bool comp(std::pair<int64_t, int64_t> a, std::pair<int64_t, int64_t> b) {
	return a.first < b.first ? true : (a.first == b.first ? true : false);
}

int main()
{
	int64_t c, n;
	std::cin >> c >> n;

	std::vector<std::pair<int64_t, int64_t>> in;
	in.reserve(n);

	for (int j = 1; j < n + 1; j++) {
		int64_t size, val;
		std::cin >> size >> val;
		in.push_back(std::make_pair(size, val));
	}
	std::sort(in.begin(), in.end(), comp);

	// Init
	int64_t m[n][c + 1];

	// weigth 0
	for (int i = 0; i < n; i++) {
		m[i][0] = 0;
	}

	// first row
	for (int j = 0; j < c + 1; j++) {
		if (j < in[0].first) m[0][j] = 0;
		else  m[0][j] = in[0].second;;
	}

	// solution
	for (int i = 1; i < n; i++) {
		int64_t size = in[i].first;
		int64_t value = in[i].second;
		for (int j = 1; j < c + 1; j++) {
			if (j > size)
				m[i][j] = std::max(value + m[i - 1][j - size], m[i - 1][j]);
			else
				m[i][j] = m[i - 1][j];
		}
	}
	std::cout << m[n - 1][c];
	return 0;
}