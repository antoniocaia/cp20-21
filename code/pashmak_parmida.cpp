#include <iostream>
#include <vector>
#include <unordered_map> 

/*
f(l,r,x) -> numero di indice i tc:
- l <= i <= r
- v[i] = x

calcolare il numero di coppie i,j con i < j tc:
f(1, i, v[i]) > f(j, n v[j])
*/


/*
Time complexity: O(n log n)
Space complexity: O(n).

We store in fi all the result from the operatio f(1, i v[i]) with i in range [1..n-1], 
and in fj all the result from the operatio f(j, n, v[j]) with j in range [2..n].

We use a Fennwick Tree to keep a counter for how many solution of a give value are in vj
until a certain position in the vector:
- when we perform an add(j, 1) in the FT we basically increase the counter for the element j
- when we perform a sum(i), we check how many value are produced by vj that are 
smaller than i.
*/

struct fenwick_tree {
	std::vector<int64_t> t;

	fenwick_tree(int64_t n) : t(n + 1) { }

	int64_t sum(int i) {
		int64_t sum = 0;
		i++;
		while (i > 0) {
			sum += t[i];
			i -= i & -i;
		}
		return sum;
	}

	void add(int i, int64_t v) {
		i++;
		while (i < t.size()) {
			t[i] += v;
			i += i & -i;
		}
	}
};

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

	std::vector<int64_t> fi(n);
	std::vector<int64_t> fj(n);
	std::unordered_map<int64_t, int64_t> mi;
	std::unordered_map<int64_t, int64_t> mj;

	for (int64_t i = 0; i < n; i++) {
		int64_t j = v.size() - 1 - i;
		int64_t xi = v[i];
		int64_t xj = v[j];

		std::unordered_map<int64_t, int64_t>::iterator it = mi.find(xi);
		if (it != mi.end()) {
			it->second++;
			fi[i] = it->second;
		}
		else {
			mi.insert({ xi, 1 });
			fi[i] = 1;
		}

		it = mj.find(xj);
		if (it != mj.end()) {
			it->second++;
			fj[j] = it->second;
		}
		else {
			mj.insert({ xj, 1 });
			fj[j] = 1;
		}
	}

	fenwick_tree t(n);
	int64_t sol = 0;
	int64_t j = n - 1;
	int64_t i = j - 1;
	while (i >= 0) {
		t.add(fj[j] + 1, 1);
		sol += t.sum(fi[i]);
		i--;
		j--;
	}

	std::cout << sol;
	return 0;
}