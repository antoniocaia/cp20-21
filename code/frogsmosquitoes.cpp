#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

/*

*/

// Mosq
struct mosq
{
	int pos;
	int size;

	mosq(int x, int s)
	{
		pos = x;
		size = s;
	}
};

inline bool operator<(const mosq &a, const mosq &b)
{
	return a.pos < b.pos;
}

bool mosq_by_pos(const mosq &a, const mosq &b)
{
	return a.pos < b.pos;
}

// Frog
struct frog
{
	int id;
	int pos;
	int tongue;
	int mos_c;

	frog(int i, int x, int t)
	{
		id = i;
		pos = x;
		tongue = t;
		mos_c = 0;
	}

	void update_frog(int s)
	{
		mos_c++;
		tongue += s;
	}

	void frog_eat(std::set<mosq> &mosqs)
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

// main
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
		int x;
		int t;
		std::cin >> x;
		std::cin >> t;

		struct frog f = {i, x, t};
		frogs.push_back(f);
	}

	// Sorts the frogs by their position for a greedy solution
	sort(frogs.begin(), frogs.end(), frog_by_pos);

	std::set<mosq> mosqs;
	for (int t = 0; t < m_n; t++)
	{
		int x;
		int s;
		std::cin >> x;
		std::cin >> s;

		int i = 0;
		while (i < f_n && !(x >= frogs[i].pos && x <= frogs[i].pos + frogs[i].tongue))
		{
			i++;
		}

		if (i == f_n)
		{
			struct mosq m = {x, s};
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
	for(int i = 0; i < f_n; i++){
		std::cout << frogs[i].mos_c << " " << frogs[i].tongue << "\n";
	}
}