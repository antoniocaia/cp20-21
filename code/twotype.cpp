#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

/*


Time complexity: 
Space complexity: 
*/

std::map<long, long> to_dup;
std::map<long, long> no_dup;
int fire_in_max = 0;
int n_fire = 0;

long long sum = 0;

void update_sets(long t, long p) {
	if (t != 0) { // lighting
		if (!no_dup.empty()) {
			long max = no_dup.rbegin()->first;

			if (p > max) {
				to_dup.insert({ p, t });
				sum += p * 2;
			}
			else {
				long t_tmp = no_dup.rbegin()->second;
				no_dup.erase(max);
				to_dup.insert({ max, t_tmp });

				no_dup.insert({ p, t });

				if (t_tmp == 0) fire_in_max++;

				sum += max;
				sum += p;
			}
		}
		else {
			to_dup.insert({ p, t });
			sum += p * 2;
		}
	}
	else { // fire
		n_fire++;
		if (!to_dup.empty()) {
			long min = to_dup.begin()->first;

			if (p < min) {
				no_dup.insert({ p, t });
				sum += p;
			}
			else {
				long t_tmp = to_dup.begin()->second;
				to_dup.erase(min);
				no_dup.insert({ min, t_tmp });

				to_dup.insert({ p, t });

				fire_in_max++;
				if (t_tmp == 0) fire_in_max--;

				sum -= min;
				sum += p * 2;
			}
		}
		else {
			no_dup.insert({ p, t });
			sum += p;
		}
	}
}

void remove_sets(int t, long p) {
	if (t != 0) { // lighting
		std::map<long, long>::iterator it;
		it = to_dup.find(p);

		if (it != to_dup.end()) { // if is in to_dup
			to_dup.erase(p);

			sum -= p * 2;
		}
		else { // if is in no_dup
			no_dup.erase(p);

			long min_tmp = to_dup.begin()->first;
			long t_tmp = to_dup.begin()->second;
			to_dup.erase(min_tmp);
			no_dup.insert({ min_tmp, t_tmp });

			if (t_tmp == 0) fire_in_max--;

			sum -= p;
			sum -= min_tmp;
		}
	}
	else { // fire
		n_fire--;
		std::map<long, long>::iterator it;
		it = to_dup.find(p);

		if (it != to_dup.end()) { // if is in to_dup
			to_dup.erase(p);
			fire_in_max--;

			long max_tmp = no_dup.rbegin()->first;
			long t_tmp = no_dup.rbegin()->second;
			no_dup.erase(max_tmp);
			to_dup.insert({ max_tmp, t_tmp });

			if (t_tmp == 0) fire_in_max++;

			sum -= p * 2;
			sum += max_tmp;
		}
		else { // if is in no_dup
			no_dup.erase(p);
			sum -= p;
		}
	}
}


int main()
{
	int test_case;
	std::cin >> test_case;

	for (int t = 0; t < test_case; t++)
	{
		long type;
		long pow;

		std::cin >> type;
		std::cin >> pow;

		if (pow > 0)
			update_sets(type, pow);
		else
			remove_sets(type, pow * -1);

		// Adjustement for corner cases
		long long tmp_s = sum;
		if (fire_in_max == 0 && n_fire != 0) {
			if (!to_dup.empty() && !no_dup.empty()) {
				tmp_s -= to_dup.begin()->first;
				tmp_s += no_dup.rbegin()->first;
			}
		}
		else if (n_fire == 0) {
			tmp_s -= to_dup.begin()->first;
		}

		std::cout << tmp_s << "\n";
	}
}
