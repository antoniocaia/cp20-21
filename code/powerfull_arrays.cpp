#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath> 

int64_t solution = 0;
// s = int value of element in the sub-array
// Ks = number of occurence of s in the sub-array
// pow = Ks * Ks * s = value to calculate for each distinct value in the sub-array
// r = sum of every pow calculated

// Sort based on index of the query
bool order_sort(std::pair<int64_t, int64_t> a, std::pair<int64_t, int64_t> b) {
	if (a.second < b.second) return true;
	return false;
}

// Sort based on the left index 
bool l_sort(std::pair<std::pair<int64_t, int64_t>, int64_t> a, std::pair<std::pair<int64_t, int64_t>, int64_t> b) {
	if (a.first.first < b.first.first) return true;
	else if (a.first.first == b.first.first) {
		if (a.first.second < b.first.second)
			return true;
	}
	return false;
}

// Sort based on the rigth index 
bool r_sort(std::pair<std::pair<int64_t, int64_t>, int64_t> a, std::pair<std::pair<int64_t, int64_t>, int64_t> b) {
	if (a.first.second < b.first.second) return true;
	else if (a.first.second == b.first.second) {
		if (a.first.first < b.first.first)
			return true;
	}
	return false;
}

// void _add(std::map<int64_t, int64_t>& m, int64_t x) {
// 	std::map<int64_t, int64_t>::iterator it;
// 	it = m.find(x);
// 	if (it != m.end()) {
// 		solution += x * (2 * it->second + 1);
// 		it->second += 1;
// 	}
// 	else {
// 		solution += x;
// 		m.insert({ x, 1 });
// 	}
// }

void _add(std::vector<int64_t>& m, int64_t x) {

	if (m[x] != INT64_MAX) {
		solution += x * (2 * m[x] + 1);
		m[x] += 1;
	}
	else {
		solution += x;
		m[x] = 1;
	}
}


// void _remove(std::map<int64_t, int64_t>& m, int64_t x) {
// 	std::map<int64_t, int64_t>::iterator it;
// 	it = m.find(x);
// 	if (it != m.end()) {
// 		it->second -= 1;
// 		solution -= x * (2 * it->second + 1);
// 	}
// 	else {
// 		solution -= x;
// 		m.insert({ x, -1 });
// 	}
// }

void _remove(std::vector<int64_t>& m, int64_t x) {
	if (m[x] != INT64_MAX) {
		m[x] -= 1;
		solution -= x * (2 * m[x] + 1);
	}
	else {
		solution -= x;
		m[x] = -1;
	}
}


// REMAP 
// std::vector<int64_t> remap(std::vector<int64_t> v) {
// 	std::vector<int64_t> remap = v;
// 	sort(remap.begin(), remap.end());
// 	std::vector<int64_t>::iterator tmp = std::unique(remap.begin(), remap.end());
// 	int64_t new_size = std::distance(remap.begin(), tmp);
// 	remap.resize(new_size);

// 	for (int i = 0; i < v.size(); i++) {
// 		for (int j = 0; j < remap.size(); j++) {
// 			if (remap[j] == v[i]) v[i] = j;
// 		}
// 	}
// 	return remap;
// }

int main() {

	// input
	int64_t n, q;
	std::cin >> n >> q;

	// ns
	std::vector<int64_t> in;
	in.reserve(n);
	for (int64_t i = 0; i < n; i++) {
		int64_t x;
		std::cin >> x;
		in.push_back(x);
	}

	// qs
	std::vector<std::pair<std::pair<int64_t, int64_t>, int64_t>> query;
	query.reserve(q);
	for (int64_t i = 0; i < q; i++) {
		int64_t l, r;
		std::cin >> l >> r;
		l -= 1;
		r -= 1;

		query.push_back(std::make_pair(std::make_pair(l, r), i));
	}

	// MO
	std::sort(query.begin(), query.end(), l_sort);
	int64_t buck_size = std::sqrt(n) + 1;

	std::vector<std::vector<std::pair<std::pair<int64_t, int64_t>, int64_t>>> buckets;
	buckets.reserve(buck_size);
	for (int i = 0; i < buck_size; i++) {
		std::vector<std::pair<std::pair<int64_t, int64_t>, int64_t>> tmp;
		tmp.reserve(q);
		buckets.push_back(tmp);
	}

	for (int i = 0; i < q; i++) {
		std::pair<int64_t, int64_t> qu = query[i].first;
		int64_t pos = qu.first / buck_size;
		buckets[pos].push_back(query[i]);
	}

	for (int i = 0; i < buck_size; i++) {
		std::vector<std::pair<std::pair<int64_t, int64_t>, int64_t>> bucket = buckets[i];
		sort(bucket.begin(), bucket.end(), r_sort);
	}

	// Sol
	std::vector<std::pair<int64_t, int64_t>> sol;
	sol.reserve(q);

	//std::map<int64_t, int64_t> ks;
	std::vector<int64_t> ks(n + 1, INT64_MAX);
	int64_t c_l = -1;
	int64_t c_r = -1;
	for (int j = 0; j < buckets.size(); j++) {
		std::vector<std::pair<std::pair<int64_t, int64_t>, int64_t>> bucket = buckets[j];
		for (int i = 0; i < bucket.size(); i++) {
			std::pair<int64_t, int64_t> qu = bucket[i].first;
			while (c_l < qu.first) {
				if (c_l > -1) _remove(ks, in[c_l]);
				c_l++;
			}
			while (c_l > qu.first) {
				c_l--;
				_add(ks, in[c_l]);
			}
			while (c_r < qu.second) {
				c_r++;
				_add(ks, in[c_r]);
			}
			while (c_r > qu.second) {
				_remove(ks, in[c_r]);
				c_r--;
			}

			sol.push_back(std::make_pair(solution, bucket[i].second));
		}
	}

	std::sort(sol.begin(), sol.end(), order_sort);

	for (int i = 0; i < q; i++) {
		std::cout << sol[i].first << "\n";
	}
}