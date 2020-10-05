#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

/*

Wrong answer test 5

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

bool operator<(const mosq& a, const mosq& b)
{
	return a.pos < b.pos;
}

// Frog
struct frog
{
	int id;
	long pos;
	long tongue;
	int mos_c;

	frog(int i, long x, long t)
	{
		id = i;
		pos = x;
		tongue = t;
		mos_c = 0;
	}

	void update_frog(long s)
	{
		mos_c++;
		tongue += s;
	}

	void frog_eat(std::set<mosq>& mosqs)
	{
		std::set<mosq>::iterator mit;
		for (mit = mosqs.begin(); mit != mosqs.end(); ++mit)
		{
			mosq m = *mit;
			if (m.pos >= pos && m.pos <= pos + tongue)
			{
				update_frog(m.size);
				mosqs.erase(m);
				frog_eat(mosqs);
				break;
			}
		}
	}
};

bool frog_by_pos(frog a, frog b)
{
	return a.pos < b.pos;
}

bool frog_by_id(frog a, frog b)
{
	return a.id < b.id;
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

	for (int i = 0; i < f_n; i++)
	{
		long x;
		long t;
		std::cin >> x;
		std::cin >> t;

		struct frog f = { i, x, t };
		frogs.push_back(f);
	}

	// Sorts the frogs by their position for a greedy solution
	sort(frogs.begin(), frogs.end(), frog_by_pos);

	std::set<mosq> mosqs;
	for (int t = 0; t < m_n; t++)
	{
		long x;
		long s;
		std::cin >> x;
		std::cin >> s;

		int i = 0;
		while (i < f_n && !(x >= frogs[i].pos && x <= frogs[i].pos + frogs[i].tongue))
			i++;

		struct mosq m = { x, s };
		mosqs.insert(m);

		//std::cout << "\nR: " << i << " - " << frogs[i].range[0] << "  " << frogs[i].range[1] << "\n";
		frogs[i].frog_eat(mosqs);
	}

	// sort before output
	sort(frogs.begin(), frogs.end(), frog_by_id);

	for (int i = 0; i < f_n; i++) {
		std::cout << frogs[i].mos_c << " " << frogs[i].tongue << "\n";
	}
}