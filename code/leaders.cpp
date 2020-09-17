#include <iostream>
#include <vector>

void find_leader(std::vector<int> l)
{
	int n = l.size();
	std::vector<int> lead;
	lead.reserve(n);

	int max = l[n - 1];
	lead.push_back(l[n - 1]);
	int c = 1;

	for (int i = n - 2; i >= 0; i--)
	{
		if (l[i] >= max)
		{
			lead.push_back(l[i]);
			max = l[i];
			c++;
		}
	}

	for (int i = c - 1; i >= 0; i--)
	{
		std::cout << lead[i] << " ";
	}
}

int main()
{
	int test_case;
	std::cin >> test_case;

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

		find_leader(l);
		std::cout << "\n";
	}
}