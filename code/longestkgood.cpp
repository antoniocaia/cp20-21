#include <iostream>
#include <vector>
#include <map>

/*


Time complexity: O(N)
Space complexity: 
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
		if (it != freq.end()) {
			it->second += 1;
			e++;
		}
		else {
			if (freq.size() < k) {
				freq.insert({ num[e], 1 });
				e++;
			}
			else {
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