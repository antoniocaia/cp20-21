#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath> 

using lli = long long int;

lli solution = 0;
lli bck_size;
// s = int value of element in the sub-array
// Ks = number of occurence of s in the sub-array
// pow = Ks * Ks * s = value to calculate for each distinct value in the sub-array
// r = sum of every pow calculated

// Sort based on the left index 
bool l_sort(std::pair<std::pair<lli, lli>, lli> a, std::pair<std::pair<lli, lli>, lli> b) {
	double a_l = a.first.first / bck_size;
	double b_l = b.first.first / bck_size;
	if (a_l != b_l)
		return a.first.first < b.first.first;

	return a.first.second < b.first.second;
}

void add(std::vector<lli>& m, lli x) {
	solution += x * (2 * m[x] + 1);
	m[x] += 1;
}

void remove(std::vector<lli>& m, lli x) {
	solution -= x * (2 * m[x] - 1);
	m[x] -= 1;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	// input
	lli n, q;
	scanf("%lld", &n);
	scanf("%lld", &q);

	// ns
	std::vector<lli> in;
	in.reserve(n);
	for (lli i = 0; i < n; i++) {
		lli x;
		scanf("%lld", &x);
		in.push_back(x);
	}

	// qs
	std::vector<std::pair<std::pair<lli, lli>, lli>> queries;
	queries.reserve(q);
	for (lli i = 0; i < q; i++) {
		lli l, r;
		scanf("%lld", &l);
		scanf("%lld", &r);
		l -= 1;
		r -= 1;
		queries.push_back(std::make_pair(std::make_pair(l, r), i));
	}

	// MO
	bck_size = std::sqrt(n);
	std::sort(queries.begin(), queries.end(), l_sort);

	std::vector<lli> sol(q);
	std::vector<lli> ks(10000001, 0);
	lli c_l = 0;
	lli c_r = -1;

	for (int j = 0; j < q; j++) {
		std::pair<lli, lli> qu = queries[j].first;
		while (c_l < qu.first) {
			remove(ks, in[c_l]);
			c_l++;
		}
		while (c_l > qu.first) {
			c_l--;
			add(ks, in[c_l]);
		}
		while (c_r < qu.second) {
			c_r++;
			add(ks, in[c_r]);
		}
		while (c_r > qu.second) {
			remove(ks, in[c_r]);
			c_r--;
		}
		sol[queries[j].second] = solution;
	}

	for (int i = 0; i < q; i++) {
		printf("%lld\n", sol[i]);
	}
}