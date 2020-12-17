#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

/*


Time complexity:
Space complexity:
*/

std::map<long, long> to_dup;					// to_dup keeps track of the spells we want to duplicate the power of (using lighting spells) 
std::map<long, long> no_dup;					// no_dup keeps track of all spells that aren't in to_dup
int fire_in_max = 0;							// fire_in_max keeps track of how many fire spell are going to be duplicated
int n_fire = 0;									// n_fire keeps track of how many fire spell we have 

long long sum = 0;								// sum keeps track of the possible max damage

void update_sets(long t, long p) {
	if (t != 0) {
		/* Lighting spell, meaning that we have the opportunity to double another spell power.
		   To accomplish that, we have to check which spell between the new one and the those already processed has the highest power */
		if (!no_dup.empty()) {
			long max = no_dup.rbegin()->first;			// take the spell with the highest power between those that aren't already going to be doubled

			if (p > max) {								// insert in to_dup the spell with the higher power ...
				to_dup.insert({ p, t });
				sum += p * 2;
			}
			else {										// ... update the maps and the sum
				long t_tmp = no_dup.rbegin()->second;
				no_dup.erase(max);
				to_dup.insert({ max, t_tmp });

				no_dup.insert({ p, t });

				if (t_tmp == 0) fire_in_max++;

				sum += max;
				sum += p;
			}
		}
		// If there aren't any spells that can be doubled, we assume that we are going to double this one (corner cases are going to be handled at the end!)
		else {
			to_dup.insert({ p, t });
			sum += p * 2;
		}
	}
	else { 
		// Fire spell. In this scenario, we check if we can replace the smaller spell that is going to be duplicated with this new fire one
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
	if (t != 0) { 
		// We remove a lighting spell, meaning that we can't double another spell anymore.
		std::map<long, long>::iterator it;
		it = to_dup.find(p);

		/* If the lighting spell is in to_dup, removing it means that we are also reducing the number of doubled spells by one.
		   This means that the spell that was doubled by the one that we are removing is going to be doubled 
		   by the one that was doubling the one that we are removing.
		Es:
		to_doub: (l, 3) (f, 4) 
		no_doub: (l, 1) (f, 2)

		The order of casting is (f, 2) (l,1) (l, 3) (f, 4)
		If we remove (l, 3)
		The order of casting is (f, 2) (l,1) (f, 4)

		*/
		if (it != to_dup.end()) {
			to_dup.erase(p);
			sum -= p * 2;
		}
		else { 
			// If the lighting spell is in no_dup, we have to stop doubling the smaller spell in to_dup
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
	else { 
		// Fire spell
		n_fire--;
		std::map<long, long>::iterator it;
		it = to_dup.find(p);

		// If the fire spell is in to_dup, we have to replace it with the strongest spell in no_dup	
		if (it != to_dup.end()) { 
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

		// Select or remove the current spell
		if (pow > 0)
			update_sets(type, pow);
		else
			remove_sets(type, pow * -1);

		// Adjustement for corner cases:
		long long tmp_s = sum;
		if (fire_in_max == 0 && n_fire != 0) {
			/* - We processed some fire spell
			   - No fire spell is going to be doubled 
			   This imply that all the spells in to_dup are ligthing spell.
			   The solution rigth now is wrong: the smallest spell in to_dup can't be doubled because 
			   its precedessor is a fire spell. To solve this problem, we swap the weakest ligthing spell (to_dup)
			   with the strongest fire spell (no_dup) */
			if (!to_dup.empty() && !no_dup.empty()) {
				tmp_s -= to_dup.begin()->first;
				tmp_s += no_dup.rbegin()->first;
			}
		}
		else if (n_fire == 0) {
			/* - We processed only lighting spells
			   Similar to the previous case, we can't double the weakest spell, so we have to halve is power */
			tmp_s -= to_dup.begin()->first;
		}

		std::cout << tmp_s << "\n";
	}
}
