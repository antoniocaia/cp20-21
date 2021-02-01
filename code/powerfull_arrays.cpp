#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath> 

/*
time complexity: O((n + q) n^1/2)
space complexity: O(10^6) To store the frequency we used an arry that covers all the possible values [1..10^6]

The critical step in this problem is to keep track of the frquencies 
so we don't have to recompute the solution for each query. To do so, 
we use an offline approach: we sort the queries so that we minimize the 
distance between their ends, meaning that we don't have to recompute 
the overlapping parts between queries and we minimize the number of 
shifts.
*/

using lli = long long int;
lli solution = 0;
lli bck_size;

// Sort based on the left and rigth index, perform the bucket sort
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

	// vector 
	std::vector<lli> in;
	in.reserve(n);
	for (lli i = 0; i < n; i++) {
		lli x;
		scanf("%lld", &x);
		in.push_back(x);
	}

	// queries
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

	// MO's alg
	bck_size = std::sqrt(n);
	std::sort(queries.begin(), queries.end(), l_sort);

	std::vector<lli> sol(q);
	std::vector<lli> ks(1000001, 0);
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