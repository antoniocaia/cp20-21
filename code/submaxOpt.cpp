#include <iostream>
#include <vector>
#include <deque>

void sliding_window(std::vector<int> v, int sub)
{
	std::deque<int> d_pos;

	for (int i = 0; i < v.size(); i++)
	{
		while (!d_pos.empty() && d_pos.front() <= i - sub)
		{
			d_pos.pop_front();
		}

		while (!d_pos.empty() && v[d_pos.back()] <= v[i])
		{
			d_pos.pop_back();
		}
		d_pos.push_back(i);

		if (i > sub - 2)
			std::cout << v[d_pos.front()] << " ";
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

		int sub_size;
		std::cin >> sub_size;

		for (int j = 0; j < size; j++)
		{
			int input = 0;
			std::cin >> input;
			l.push_back(input);
		}

		sliding_window(l, sub_size);
		std::cout << "\n";
	}
}
