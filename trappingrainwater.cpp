#include <iostream>
#include <vector>
#include <string>

int count_water(std::vector<int> l, int p, int &water)
{
	int total = 0;
	int heigth = l[p];
	int tmp_max = -1;
	int tmp_pos = -1;

	int i;
	for (i = p + 1; i < l.size(); i++)
	{
		if (l[i] > tmp_max)
		{
			tmp_max = l[i];
			tmp_pos = i;
			if (tmp_max > heigth)
			{
				tmp_max = heigth;
				break;
			}
		}
	}

	for (int j = p + 1; j < tmp_pos; j++)
	{
		water += tmp_max - l[j];
	}

	return tmp_pos;
}

int main()
{
	int test_case;
	std::cin >> test_case;

	for (int i = 0; i < test_case; i++)
	{
		int size;
		std::cin >> size;
		std::vector<int> l;
		l.reserve(size);

		for (int j = 0; j < size; ++j)
		{
			int input = 0;
			std::cin >> input;
			l.push_back(input);
		}

		// logic 
		
		int water = 0;
		int j = 0;
		while (j < size - 1)
		{
			j = count_water(l, j, water);
		}
		std::cout << water << "\n";
	}
}