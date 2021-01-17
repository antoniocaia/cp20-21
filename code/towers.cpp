#include <iostream>
#include <vector>
#include <algorithm>

/*
time complexity: O(n log n)
space complexity: O(1)

The main difficulty in this problem is to find bars of the same height.
Sorting the bars by their heigth has a cost of n log n, 
but doing so make it's possible to iterate and confront 
the elements in the vector with only n steps.
*/

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

	int max = 0; 							// max height between all towers
	int tw = 0;	 							// towers counter

	int i = 0;
	while (i < size)
	{
		int elem = 1; 						//every tower will be have at least one bar
		int j = i + 1;
		while (j < size && v[i] == v[j]) 	// until bars with the same height are found, we keep "stacking" them
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