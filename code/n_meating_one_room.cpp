#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

/*
time complexity: O(n log n)
space complexity: O(n)

We store each meeting as a tuple <start_time, end_time>.
Then we sort the meeting by increasing end_ime.
Then we start "greadly" picking meeting starting from the first one,
and we pick only the meeting with a start_time greater then 
the_end time of the last meeting picked.
*/

bool sort_second(std::tuple<int64_t, int64_t> a, std::tuple<int64_t, int64_t> b) {
	return std::get<1>(a) < std::get<1>(b);
}

int maxMeetings(int start[], int end[], int n) {
	std::vector<std::tuple<int64_t, int64_t>> t;
	t.reserve(n);
	for (int i = 0; i < n; i++) {
		t.push_back(std::make_pair(start[i], end[i]));
	}

	std::sort(t.begin(), t.end(), sort_second);

	int64_t r = 1, i = 1;
	int64_t last_end = std::get<1>(t[0]);
	while (i < n) {
		if (std::get<0>(t[i]) > last_end) {
			r++;
			last_end = std::get<1>(t[i]);
		}
		i++;
	}
	return r;
}