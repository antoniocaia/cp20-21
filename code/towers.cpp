#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	int size;
	std::cin >> size;
	std::vector<int> v;
	v.reserve(size);

	for (int j = 0; j < size; j++)
	{
		int input = 0;
		std::cin >> input;
		v.push_back(input);
	}

	std::sort(v.begin(), v.end());

	int max = 0;
	int tw = 0;

	int i = 0;
	while (i < size)
	{
		int elem = 1;
		int j = i + 1;
		while (j < size && v[i] == v[j])
		{
			elem++;
			j++;
		}
		if (max < elem)
			max = elem;

		tw++;
		i = j;
	}

	std::cout << max << " " << tw << "\n";
}