#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

struct mosq {
	int64_t x;
	int64_t s;

	int64_t l; // left index for the bst
	int64_t r; // rigth index for the bst

	mosq(int64_t pos, int64_t size) {
		x = pos;
		s = size;
		l = 0;
		r = 0;
	}

	mosq() {
		x = -1;
		s = -1;
		l = 0;
		r = 0;
	}
};

// Frog
struct frog {
	int64_t id;
	int64_t pos;
	int64_t tongue;
	int64_t mos_count;

	int64_t l; // left index for the bst
	int64_t r; // rigth index for the bst

	frog() {
		id = -1;
		pos = -1;
		tongue = -1;
		mos_count = 0;

		l = 0;
		r = 0;
	}

	frog(int64_t i, int64_t x, int64_t t) {
		id = i;
		pos = x;
		tongue = t;
		mos_count = 0;

		l = 0;
		r = 0;
	}

	void update_frog(int64_t s) {
		mos_count++;
		tongue += s;
	}
	// Check if frog can eat any of the stored mosq. The mosq are ordered in increasing position.
	void feast(std::multimap<int64_t, int64_t>& ms) {
		auto to_eat = ms.lower_bound(pos);
		if (to_eat != ms.end() && to_eat->first >= pos && to_eat->first <= pos + tongue) {
			update_frog(to_eat->second);
			ms.erase(to_eat);
			return feast(ms);

		}
	}
};

bool sort_m_pos(mosq a, mosq b) { return a.x < b.x; }
bool frog_by_id(frog a, frog b) { return a.id < b.id; }

void insert_frog(std::vector<frog>& frogs, frog& f, int64_t v_i) {
	int64_t crr = 1;
	int64_t prc = -1;

	while (frogs[crr].id != -1) {
		prc = crr;
		if (f.pos < frogs[crr].pos)
			crr = frogs[crr].l;
		else
			crr = frogs[crr].r;
	}
	frogs[v_i].id = f.id;
	frogs[v_i].pos = f.pos;
	frogs[v_i].tongue = f.tongue;

	if (prc != -1) {
		if (frogs[prc].pos < f.pos)
			frogs[prc].r = v_i;
		else
			frogs[prc].l = v_i;
	}
}

// OK!
void find_frog(std::vector<frog>& frogs, int64_t i, int64_t m_pos, int64_t& f_i) {
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

// void find_frog(std::vector<frog>& frogs, int64_t i, int64_t m_pos, int64_t& f_i) {
// 	// No more frogs to check, end
// 	//if (frogs[i].id == -1) return;
// 	for (int i = 0; i < frogs.size(); i++) {
// 		if((frogs[i].pos <= m_pos && frogs[i].pos + frogs[i].tongue >= m_pos) && (f_i == -1 || frogs[i].pos < frogs[f_i].pos)) {
// 			f_i = i;
// 		}
// 	}
// }

// Main
int main()
{
	int64_t f_n, m_n;
	std::cin >> f_n >> m_n;

	std::vector<frog> frogs(f_n + 1);
	int64_t free_pos = 1;

	for (int64_t i = 0; i < f_n; i++) {
		int64_t x, t;
		std::cin >> x >> t;

		struct frog f = { i, x, t };
		insert_frog(frogs, f, free_pos++);
	}

	//std::vector<mosq> mosqs(m_n + 1);
	std::multimap<int64_t, int64_t> mosqs;
	//int64_t free_m_pos = 1;

	for (int64_t t = 0; t < m_n; t++) {
		int64_t x, s;
		std::cin >> x >> s;

		int64_t f_eat = -1;
		find_frog(frogs, 1, x, f_eat);

		if (f_eat != -1) {
			// Frog f_eat can eat
			frogs[f_eat].update_frog(s);
			// Check for more mosq
			frogs[f_eat].feast(mosqs);
		}
		else {
			// not eaten, store the mosq
			//mosqs.push_back(mosq(x, s));
			//sort(mosqs.begin(), mosqs.end(), sort_m_pos);
			mosqs.insert({ x, s });
		}
	}

	sort(frogs.begin(), frogs.end(), [](frog a, frog b) { return a.id < b.id; });

	for (int64_t i = 1; i < f_n + 1; i++) {
		std::cout << frogs[i].mos_count << " " << frogs[i].tongue << "\n";
	}

	return 0;
}