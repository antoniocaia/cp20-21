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

	li l; // left index for the bst
	li r; // rigth index for the bst

	frog() {
		id = -1;
		pos = -1;
		tongue = -1;
		mos_count = 0;

		l = 0;
		r = 0;
	}

	frog(li i, li x, li t) {
		id = i;
		pos = x;
		tongue = t;
		mos_count = 0;

		l = 0;
		r = 0;
	}

	void update_frog(li s) {
		mos_count++;
		tongue += s;
	}
	// Check if frog can eat any of the stored mosq. The mosq are ordered in increasing position.
	void feast(std::multimap<li, li>& ms) {
		auto to_eat = ms.lower_bound(pos);
		if (to_eat != ms.end() && to_eat->first >= pos && to_eat->first <= pos + tongue) {
			update_frog(to_eat->second);
			ms.erase(to_eat);
			return feast(ms);
		}
	}
};

bool frog_by_id(frog a, frog b) { return a.id < b.id; }

void insert_frog(std::vector<frog>& frogs, li id, li pos, li tongue, li v_i) {
	li crr = 1;
	li prc = -1;
 
	while (frogs[crr].id != -1) {
		prc = crr;
		if (pos < frogs[crr].pos)
			crr = frogs[crr].l;
		else
			crr = frogs[crr].r;
	}
	frogs[v_i].id = id;
	frogs[v_i].pos = pos;
	frogs[v_i].tongue = tongue;
 
	if (prc != -1) {
		if (frogs[prc].pos < pos)
			frogs[prc].r = v_i;
		else
			frogs[prc].l = v_i;
	}
}

// OK!
void find_frog(std::vector<frog>& frogs, li i, li m_pos, li& f_i) {
	// No more frogs to check, end
	if (frogs[i].id == -1) return;

	// Check if current frog is best candidate
	bool can_eat = frogs[i].pos <= m_pos && (frogs[i].pos + frogs[i].tongue) >= m_pos;
	bool most_left = f_i == -1 || frogs[i].pos < frogs[f_i].pos;


	if (can_eat && most_left) { 					// If the frog match the requisites update index and check for leftmost frogs
		f_i = i;
		find_frog(frogs, frogs[i].l, m_pos, f_i);
	}
	else if (m_pos < frogs[i].pos) {				// If the mosq is to the left size of the current frog, check only leftmost frogs
		find_frog(frogs, frogs[i].l, m_pos, f_i);
	}
	else {											// General case
		find_frog(frogs, frogs[i].l, m_pos, f_i);
		find_frog(frogs, frogs[i].r, m_pos, f_i);
	}
}

// void find_frog2(std::multimap<my_type, frog>& frog_tree, my_type m_pos, my_type m_s) {
// 	auto gonna_eat = frog_tree.lower_bound(m_pos);
// 	auto f = gonna_eat->second;
// 	if (gonna_eat != frog_tree.end() && m_pos <= gonna_eat->second.pos + gonna_eat->second.tongue) {
// 		gonna_eat->second.update_frog(m_s);
// 	}
// }

// Main
int main()
{
	std::ios_base::sync_with_stdio(false);
	li f_n, m_n;
	scanf("%ld", &f_n);
	scanf("%ld", &m_n);

	std::vector<frog> frogs(f_n + 1);
	li free_pos = 1;

	for (li i = 0; i < f_n; i++) {
		li x, t;
		scanf("%ld", &x);
		scanf("%ld", &t);
		
		insert_frog(frogs, i, x, t, free_pos++);
	}

	std::multimap<li, li> mosqs;

	for (li t = 0; t < m_n; t++) {
		li x, s;
		scanf("%ld", &x);
		scanf("%ld", &s);

		li f_eat = -1;
		find_frog(frogs, 1, x, f_eat);

		if (f_eat != -1) {
			frogs[f_eat].update_frog(s);
			frogs[f_eat].feast(mosqs);
		}
		else {
			mosqs.insert({ x, s });
		}
	}

	sort(frogs.begin(), frogs.end(), [](frog a, frog b) { return a.id < b.id; });

	for (li i = 1; i < f_n + 1; i++) {
		printf("%ld %ld\n", frogs[i].mos_count, frogs[i].tongue);
	}

	return 0;
}