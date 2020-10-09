#include <iostream>
#include <vector>
#include <algorithm>

// Mosq
struct mosq
{
	long pos;
	long size;

	mosq(long x, long s)
	{
		pos = x;
		size = s;

		int sx;
		int dx;
	}
};


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
};

bool frog_by_id(frog a, frog b) {
	return a.id < b.id;
}

void insert_frog(frog f, int i, std::vector<frog>& frogs)
{
	if (frogs.empty())
		frogs.push_back(f);
	else {
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
}

void update_frog_tree(frog f, int i, std::vector<frog>& frogs) {

	if(frogs[i].sx != -1) update_frog_tree(f, frogs[i].sx, frogs);
	if(frogs[i].dx != -1) update_frog_tree(f, frogs[i].dx, frogs);

	long range_i = frogs[i].pos + frogs[i].tongue;
	long range_f = f.pos + f.tongue;

	if(f.pos > frogs[i].pos && range_f < range_i) {
		// delete f;
	} else if(f.pos < frogs[i].pos && range_f > range_i) {
		// delete frogs[i]
	} else if(f.pos > frogs[i].pos && range_f > range_i){
		// reduce size of f
		f.pos = range_i + 1; // not sure about +1
	} else if(f.pos < frogs[i].pos && range_f < range_i){
		// reduce size of frogs[i]
		frogs[i].pos = range_f + 1;
	}
}

void remove_frog(int i, std::vector<frog>& frogs)
{

}


void precedessor(int pos, int i, int& i_pr, std::vector<frog> frogs) {
	if (i == -1) return;
	if (pos == frogs[i].pos) {
		i_pr = i;
		return;
	}

	if (frogs[i].pos <= pos && (frogs[i].pos > frogs[i_pr].pos || i_pr == -1))
		i_pr = i;

	if (pos < frogs[i].pos) {
		return precedessor(pos, frogs[i].sx, i_pr, frogs);
	}
	else {
		return precedessor(pos, frogs[i].dx, i_pr, frogs);
	}
}


// ----

bool eat_mosq(int frog_ind, mosq m, std::vector<frog> frogs) {
	if (frogs[frog_ind].pos + frogs[frog_ind].tongue > m.pos) {
		frogs[frog_ind].update_frog(m.size);
		update_frog_tree(frogs[frog_ind], 0, frogs);
		return true;
	}
	return false;
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
		insert_frog(f, 0, frogs);
	}

	std::vector<mosq> mosqs;
	for (int t = 0; t < m_n; t++) {
		long x;
		long s;
		std::cin >> x;
		std::cin >> s;
		mosq m = { x, s };

		int frog_ind = -1;
		precedessor(m.pos, 0, frog_ind, frogs);

		if (frog_ind == -1 || eat_mosq(frog_ind, m, frogs)) {

		}
		//insert_mosq(m, mosqs);

	}

	// sort before output
	sort(frogs.begin(), frogs.end(), [](frog a, frog b) { return a.id < b.id; });

	for (int i = 0; i < f_n; i++)
	{
		std::cout << frogs[i].mos_c << " " << frogs[i].tongue << "\n";
	}
}