#include <iostream>
#include <vector>

void missing_number(std::vector<int> l)
{
	int n = l.size();
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += l[i];
	}

	n++;
	int missing = n * (n + 1) / 2 - sum;
	std::cout << missing;
}

int main()
{
	int test_case;
	std::cin >> test_case;

	for (int t = 0; t < test_case; t++)
	{
		int size;
		std::cin >> size;
		size--;

		std::vector<int> l;
		l.reserve(size);

		for (int i = 0; i < size; i++)
		{
			int input = 0;
			std::cin >> input;
			l.push_back(input);
		}

		missing_number(l);
		std::cout << "\n";
	}
}