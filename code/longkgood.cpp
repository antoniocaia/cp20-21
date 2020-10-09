#include <iostream>
#include <vector>
#include <map>

int main()
{
	int n;
	int k;
	scanf("%d", &n);
	scanf("%d", &k);

	std::vector<int> num;
	num.reserve(n);

	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		num.push_back(x);
	}

	int s = 0;
	int e = 0;
	int top_s = 0;
	int top_e = 0;

	std::map<int, int> map;
	std::map<int, int>::iterator it;

	for (int i = 0; i < n; i++) {
		it = map.find(num[i]);

		if (it != map.end()) {
			it->second += 1;

			if (it->second < k) {
				e = i;
				if (e - s > top_e - top_s) {
					top_e = e;
					top_s = s;
				}
			}
			else if (it->second > k) {
				s = e = i;
				map.clear();
				map.insert({ num[i], 0 });
			}
			else {
				std::cout << s + 1 << " " << e + 1;
				return 0;
			}
		}
		else {
			map.insert({ num[i], 0 });
			e = i;
			if (e - s > top_e - top_s) {
				top_e = e;
				top_s = s;
			}
		}
	}
	std::cout << (top_s + 1) << " " << (top_e + 1);
}