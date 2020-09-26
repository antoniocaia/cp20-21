#include <iostream>
#include <vector>

/*
Find the minum k (the bigger gap between two pole), and simulate all the jumps. If you can't complete with k, you can for sure solve it with k+1

O(N)
*/

int min_strenght(std::vector<int> v)
{
	int n = v.size();
	if (n == 1)
	{
		return v[0];
	}

	int max_gap = v[0];
	std::vector<int> g;
	g.reserve(n);
	g.push_back(v[0]);

	for (int i = 1; i < n; i++)
	{
		int gap = v[i] - v[i - 1];
		g.push_back(gap);
		if (max_gap < gap)
			max_gap = gap;
	}

	int tg = max_gap;
	for (int i = 0; i < n; i++)
	{
		if (tg < g[i])
		{
			return max_gap + 1;
		}
		else if (tg == g[i])
			tg--;
	}

	return max_gap;
}

int main()
{
	int test_case;
	std::cin >> test_case;
	std::vector<int> r;
	r.reserve(test_case);

	for (int t = 0; t < test_case; t++)
	{
		int size;
		std::cin >> size;

		std::vector<int> l;
		l.reserve(size);

		for (int i = 0; i < size; i++)
		{
			int input = 0;
			std::cin >> input;
			l.push_back(input);
		}
		r.push_back(min_strenght(l));
	}


	for (int i = 0; i < test_case; i++)
	{
		std::cout << "Case " << i + 1 << ": " << r[i] << "\n";
	}
}