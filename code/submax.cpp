#include <iostream>
#include <vector>
#include <string>

void get_max(int s, int e, std::vector<int> l, int &m, int &m_i)
{
	m = l[s];
	m_i = s;
	for (int i = s; i <= e; i++)
	{
		if (l[i] >= m)
		{
			m = l[i];
			m_i = i;
		}
	}
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

		int sub_size;
		std::cin >> sub_size;

		for (int j = 0; j < size; ++j)
		{
			int input = 0;
			std::cin >> input;
			l.push_back(input);
		}

		// logic

		int start = 0;
		int end = sub_size - 1;
		int max = -1;
		int max_ind = -1;

		while (end < l.size())
		{
			if (l[end] >= max && max_ind >= start)
			{
				max = l[end];
				max_ind = end;
			}
			else if (max_ind < start)
			{
				get_max(start, end, l, max, max_ind);
			}

			std::cout << max << " ";
			start++;
			end++;
		}

		std::cout << "\n";
	}
}
