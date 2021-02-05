#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using li = long int;

// Frog
struct frog {
	li id;
	li pos;
	li tongue;
	li mos_count;

	frog() {
		id = -1;
		pos = -1;
		tongue = -1;
		mos_count = 0;
	}

	frog(li i, li x, li t) {
		id = i;
		pos = x;
		tongue = t;
		mos_count = 0;
	}
};

bool frog_by_id(frog a, frog b) { return a.id < b.id; }



void update_frog_tree(std::multimap<li, li>::iterator i, std::multimap<li, li>& fst, std::vector<frog>& fsl) {
	frog crn_f = fsl[i->second];
	auto ii = std::next(i);

	while (ii != fst.end()) {
		frog next_f = fsl[ii->second];
		if (next_f.pos + next_f.tongue <= crn_f.pos + crn_f.tongue) {
			fst.erase(ii);
			ii = std::next(i);
		}
		else if (next_f.pos <= crn_f.pos + crn_f.tongue) {
			li tmp_i = ii->second;
			fst.erase(ii);
			fst.insert({ crn_f.pos + crn_f.tongue + 1, tmp_i });
			return;
			//ii = std::next(i);
		}
		else {
			return;
		}
	}

}


void feast(std::multimap<li, li>& ms, std::multimap<li, li>::iterator i, std::multimap<li, li>& fst, std::vector<frog>& fsl) {
	frog f = fsl[i->second];
	auto to_eat = ms.lower_bound(f.pos);
	if (to_eat != ms.end() && to_eat->first >= f.pos && to_eat->first <= f.pos + f.tongue) {
		fsl[i->second].mos_count++;
		fsl[i->second].tongue += to_eat->second;

		ms.erase(to_eat);
		update_frog_tree(i, fst, fsl);
		return feast(ms, i, fst, fsl);
	}
}

// 30L + bacio accademico
std::multimap<li, li>::iterator find_kermit(li x, li s, std::multimap<li, li>& fst, std::vector<frog>& fsl) {
	auto i = fst.lower_bound(x);
	if (i->first == x) {
		frog f = fsl[i->second];
		if (x >= f.pos && x <= f.pos + f.tongue) {
			return i;
		}
		return fst.end();
	}
	else if (i != fst.begin()) {
		i = std::prev(i);
		frog f = fsl[i->second];
		if (x >= f.pos && x <= f.pos + f.tongue) {
			return i;
		}
		return fst.end();
	}
	return fst.end();
}

bool sort_f_pos(frog a, frog b) { return a.pos < b.pos; }

// Mainupd
int main()
{
	std::ios_base::sync_with_stdio(false);
	li f_n, m_n;
	scanf("%ld", &f_n);
	scanf("%ld", &m_n);

	std::vector<frog> frog_list;
	frog_list.reserve(f_n);


	for (li i = 0; i < f_n; i++) {
		li x, t;
		scanf("%ld", &x);
		scanf("%ld", &t);
		frog_list.push_back(frog(i, x, t));
	}

	std::sort(frog_list.begin(), frog_list.end(), sort_f_pos);
	std::multimap<li, li> frog_tree;

	li prev_pos = -1;

	for (li i = 0; i < f_n; i++) {
		if (frog_list[i].pos > prev_pos) {
			frog_tree.insert({ frog_list[i].pos, i });
			prev_pos = frog_list[i].pos + frog_list[i].tongue;
		}
		else {
			if (frog_list[i].pos + frog_list[i].tongue > prev_pos) {
				frog_tree.insert({ prev_pos + 1,  i });
				prev_pos = frog_list[i].pos + frog_list[i].tongue;
			}
		}
	}

	std::multimap<li, li> mosqs;

	for (li t = 0; t < m_n; t++) {
		li x, s;
		scanf("%ld", &x);
		scanf("%ld", &s);

		auto itr = find_kermit(x, s, frog_tree, frog_list);

		if (itr != frog_tree.end()) {
			frog_list[itr->second].mos_count++;
			frog_list[itr->second].tongue += s;

			update_frog_tree(itr, frog_tree, frog_list);
			feast(mosqs, itr, frog_tree, frog_list);
		}
		else {
			mosqs.insert({ x, s });
		}
	}

	sort(frog_list.begin(), frog_list.end(), [](frog a, frog b) { return a.id < b.id; });

	for (li i = 0; i < f_n; i++) {
		printf("%ld %ld\n", frog_list[i].mos_count, frog_list[i].tongue);
	}

	return 0;
}