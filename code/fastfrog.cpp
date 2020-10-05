#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

/*

Wrong answer test 3

*/

// Mosq
struct mosq
{
	long pos;
	long size;

	mosq(long x, long s)
	{
		pos = x;
		size = s;
	}
};

bool operator<(const mosq& a, const mosq& b) {
	return a.pos < b.pos;
}

// Frog
struct frog
{
	int id;
	long pos;
	long tongue;
	int mos_c;

	int sx;
	int dx;

	frog(int i, long x, long t)
	{
		id = i;
		pos = x;
		tongue = t;
		mos_c = 0;
		sx = -1;
		dx = -1;
	}

	void update_frog(long s) {
		mos_c++;
		tongue += s;
	}

	void frog_eat(std::set<mosq>& mosqs) {
		std::set<mosq>::iterator mit;
		for (mit = mosqs.begin(); mit != mosqs.end(); ++mit) {
			mosq m = *mit;
			if (m.pos >= pos && m.pos <= pos + tongue) {
				update_frog(m.size);
				mosqs.erase(m);
				frog_eat(mosqs);
				break;
			}
		}
	}
};

bool frog_by_pos(frog a, frog b) {
	return a.pos < b.pos;
}

bool frog_by_id(frog a, frog b) {
	return a.id < b.id;
}

void insert_frog(frog f, int i, std::vector<frog>& frogs)
{
	if (f.pos < frogs[i].pos) {
		if (frogs[i].sx == -1) {
			frogs.push_back(f);
			frogs[i].sx = frogs.size() - 1;
		}
		else
			insert_frog(f, frogs[i].sx, frogs);
	}
	else {
		if (frogs[i].dx == -1) {
			frogs.push_back(f);
			frogs[i].dx = frogs.size() - 1;
		}
		else
			insert_frog(f, frogs[i].dx, frogs);
	}
}

void search_near_frog(int m_pos, int i, int& bt, std::vector<frog>& frogs) {
	if (m_pos >= frogs[i].pos && m_pos <= frogs[i].pos + frogs[i].tongue)
		bt = i;

	if (frogs[i].sx != -1) search_near_frog(m_pos, frogs[i].sx, bt, frogs);
	if (bt == -1) {
		if (frogs[i].dx != -1) search_near_frog(m_pos, frogs[i].dx, bt, frogs);
	}
}

// Main
int main()
{
	int f_n;
	int m_n;
	std::cin >> f_n;
	std::cin >> m_n;

	std::vector<frog> frogs;
	frogs.reserve(f_n);

	for (int i = 0; i < f_n; i++) {
		long x;
		long t;
		std::cin >> x;
		std::cin >> t;

		struct frog f = { i, x, t };
		if(frogs.size() == 0) frogs.push_back(f);
		else insert_frog(f, 0, frogs);
	}

	std::set<mosq> mosqs;
	for (int t = 0; t < m_n; t++) {
		long x;
		long s;
		std::cin >> x;
		std::cin >> s;

		int i = -1;
		search_near_frog(x, 0, i, frogs);

		if (i == -1)
		{
			struct mosq m = { x, s };
			mosqs.insert(m);
		}
		else
		{
			//std::cout << "\nR: " << i << " - " << frogs[i].range[0] << "  " << frogs[i].range[1] << "\n";
			frogs[i].update_frog(s);
			frogs[i].frog_eat(mosqs);
		}
	}

	// sort before output
	sort(frogs.begin(), frogs.end(), frog_by_id);

	for (int i = 0; i < f_n; i++)
	{
		std::cout << frogs[i].mos_c << " " << frogs[i].tongue << "\n";
	}
}