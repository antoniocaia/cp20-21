#include <iostream>
#include <vector>

/*
time complexity: O(n)
space complexity: O(1)

While iterating the input array, we refer to all the element 
previusly scanned as prefix.
If the sum of the prefix is negative, the prefix must be excluded, 
because simply doing that we can optain a sub array whose sum is bigger. 
Everytime the sum of the elements became negative, we start 
to count from the next element, without having to back-track.
*/

void kadane(std::vector<int> l)
{
	int n = l.size();

	int max = l[0];
	int sum = l[0];

	for (int i = 1; i < n; i++)
	{
		if (sum < 0)
		{
			sum = l[i];
		}
		else
		{
			sum += l[i];
		}

		if (sum > max)
			max = sum;
	}

	std::cout << max;
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

		kadane(l);
		std::cout << "\n";
	}
}