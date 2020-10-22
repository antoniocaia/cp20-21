#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

/*
Time complexity: O(N log N)
Space complexity: O(N)

Sorting the input triplets using the "strength" field takes O(N log N) time, 
then we pick each team starting from the couple with greater strength.
After each pick, we keep track of the people already in a team using an unordered_set
(worst case scanario using "find()" takes linear time).
*/

struct team
{
	int a;
	int b;
	int strn;

	team(int aa, int bb, int s){
		a = aa;
		b = bb;
		strn = s;
	}
};

bool comparator(team t1, team t2)
{
	return t1.strn > t2.strn;
}

int main()
{
	int n;
	std::cin >> n;

	// Input
	std::vector<team> ts;
	int size = n * (n - 1) / 2;
	ts.reserve(size);

	for (int i = 1; i < 2 * n; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			int s;
			std::cin >> s;
			struct team t = {i, j, s};
			ts.push_back(t);
		}
	}

	// Sorting the input based on the strenght of each couple
	sort(ts.begin(), ts.end(), comparator);

	// Keep track of people already in a team
	std::unordered_set<int> done;

	// Result vector
	std::vector<int> re;
	re.reserve(2 * n + 1);

	for (struct team &t : ts)
	{
		if (done.find(t.a) == done.end() && done.find(t.b) == done.end())
		{
			re[t.a] = t.b + 1;
			re[t.b] = t.a + 1;

			done.insert(t.a);
			done.insert(t.b);
		}
	}

	for (int i = 0; i < n * 2; i++)
		std::cout << re[i] << " ";

	std::cout << "\n";

	return 0;
}
