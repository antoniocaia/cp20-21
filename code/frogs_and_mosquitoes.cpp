#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

// Frog
struct frog {
	int64_t id;
	int64_t pos;
	int64_t tongue;
	int mos_count;

	int64_t l;
	int64_t r;

	frog() {
		id = -1;
		pos = -1;
		tongue = -1;
		mos_count = -1;

		l = 0;
		r = 0;
	}

	frog(int i, int64_t x, int64_t t) {
		id = i;
		pos = x;
		tongue = t;
		mos_count = 0;

		l = 0;
		r = 0;
	}

	void update_frog(long s) {
		mos_count++;
		tongue += s;
	}

	void feast(std::map<int64_t, int64_t> ms) {
		auto it = ms.begin();
		while (it != ms.end()) {
			bool can_eat = pos <= it->first && pos + tongue >= it->first;
			if (can_eat) {
				update_frog(it->second);
				it = ms.erase(it);
			}
			else {
				return;
			}
		}
	}
};

bool frog_by_id(frog a, frog b) {
	return a.id < b.id;
}


// Insert
void insert_frog(std::vector<frog>& frogs, frog& f, int64_t v_i) {
	frog node = frogs[1];
	int64_t crr = 1;
	int64_t prc = -1;

	while (node.id != -1) {
		prc = crr;
		if (f.pos < node.pos) {
			crr = node.l;
			node = frogs[node.l];
		}
		else {
			crr = node.r;
			node = frogs[node.r];
		}
	}
	frogs[v_i] = f;

	if (prc != -1) {
		if (frogs[prc].pos < f.pos)
			frogs[prc].r = v_i;
		else
			frogs[prc].l = v_i;
	}
}

void find_frog(std::vector<frog> &frogs, int i, int m_pos, int& f_i) {
	// No more frogs to check, end
	if (frogs[i].id == -1) return;

	// Check if current frog is best candidate
	bool can_eat = frogs[i].pos <= m_pos && frogs[i].pos + frogs[i].tongue >= m_pos;
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

// Main
int main()
{
	int f_n, m_n;
	std::cin >> f_n >> m_n;

	std::vector<frog> frogs(f_n + 1);
	int64_t free_pos = 1;

	for (int i = 0; i < f_n; i++) {
		int64_t x, t;
		std::cin >> x >> t;

		struct frog f = { i, x, t };
		insert_frog(frogs, f, free_pos++);
	}

	std::map<int64_t, int64_t> mosqs;
	for (int t = 0; t < m_n; t++) {
		int64_t x, s;
		std::cin >> x >> s;

		int f_eat = -1;
		find_frog(frogs, 1, x, f_eat);

		if (f_eat != -1) {
			// Frog f_eat can eat
			frogs[f_eat].update_frog(s);
			// Check for more mosq
			frogs[f_eat].feast(mosqs);
		}
		else {
			// not eaten, store the mosq
			mosqs.insert({ x,s });
		}
	}

	// sort before output
	sort(frogs.begin(), frogs.end(), [](frog a, frog b) { return a.id < b.id; });

	for (int i = 1; i < f_n + 1; i++) {
		std::cout << frogs[i].mos_count << " " << frogs[i].tongue << "\n";
	}

	return 0;
}