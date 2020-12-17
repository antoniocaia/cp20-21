#include <iostream>
#include <vector>
#include <algorithm>

// REMAP 
std::vector<int64_t> remap(std::vector<int64_t> v) {
	std::vector<int64_t> remap = v;
	sort(remap.begin(), remap.end());
	std::vector<int64_t>::iterator tmp = std::unique(remap.begin(), remap.end());
	int64_t new_size = std::distance(remap.begin(), tmp);
	remap.resize(new_size);

	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < remap.size(); j++) {
			if (remap[j] == v[i]) v[i] = j;
		}
	}
	return remap;
}