#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

std::ofstream myfile;


std::map<long, long> to_dup;
std::map<long, long> no_dup;
int n_ligh = 0;
int fire_in_max = 0;
int n_fire = 0;

void update_sets(long t, long p) {
	if (t != 0) { // lighting
		n_ligh++;
		if (!no_dup.empty()) {
			long max = no_dup.rbegin()->first;

			if (p > max)
				to_dup.insert({ p, t });
			else {
				long t_tmp = no_dup.rbegin()->second;
				no_dup.erase(max);
				to_dup.insert({ max, t_tmp });

				no_dup.insert({ p, t });

				if (t_tmp == 0) fire_in_max++;
			}
		}
		else {
			to_dup.insert({ p, t });
		}
	}
	else { // fire
		n_fire++;
		if (!to_dup.empty()) {
			long min = to_dup.begin()->first;

			if (p < min)
				no_dup.insert({ p, t });
			else {
				long t_tmp = to_dup.begin()->second;
				to_dup.erase(min);
				no_dup.insert({ min, t_tmp });

				to_dup.insert({ p, t });

				fire_in_max++;
				if (t_tmp == 0) fire_in_max--;
			}
		}
		else {
			no_dup.insert({ p, t });
		}
	}
}

void remove_sets(int t, int p) {
	if (t != 0) { // lighting
		n_ligh--;
		std::map<long, long>::iterator it;
		it = to_dup.find(p);

		if (it != to_dup.end()) { // if is in to_dup
			to_dup.erase(p);
		}
		else { // if is in no_dup
			no_dup.erase(p);

			long min_tmp = to_dup.begin()->first;
			long t_tmp = to_dup.begin()->second;
			to_dup.erase(min_tmp);
			no_dup.insert({ min_tmp, t_tmp });

			if (t_tmp == 0) fire_in_max--;
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
		}
		else { // if is in no_dup
			no_dup.erase(p);
		}
	}
}


int main()
{
	//myfile.open("res.txt");
	int test_case;
	std::cin >> test_case;

	int c = 0;
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

		// std::map<long, long>::iterator ittt;
		// for (ittt = to_dup.begin(); ittt != to_dup.end(); ittt++) {
		// 	std::cout << "info to " << ittt->first << " " << ittt->second << "\n";
		// }
		// for (ittt = no_dup.begin(); ittt != no_dup.end(); ittt++) {
		// 	std::cout << "info no " << ittt->first << " " << ittt->second << "\n";
		// }

		int long long sum = 0;
		std::map<long, long>::iterator it;
		for (it = to_dup.begin(); it != to_dup.end(); it++)
			sum += it->first * 2;

		for (it = no_dup.begin(); it != no_dup.end(); it++)
			sum += it->first;

		//std::cout << "fr in max " << fire_in_max << " fr " << n_fire << "\n";

		if (fire_in_max == 0 && n_fire != 0) {
			if (!to_dup.empty() && !no_dup.empty()) {
				sum -= to_dup.begin()->first;
				sum += no_dup.rbegin()->first;
			}
		}
		else if (n_fire == 0) {
			sum -= to_dup.begin()->first;
		}

		//myfile << sum << "\n";
		std::cout << sum << "\n";
	}
	//myfile.close();
}
