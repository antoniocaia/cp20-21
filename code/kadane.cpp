#include <iostream>
#include <vector>

/*
To solve this problem is usefull to think that each array is made of three parts: 
the element that is currently checked, all the elements to its left (prefix), all the elements to its rigth (suffix).
This is helpfull because if the sum of the elements in the prefix is negative, the prefix must be excluded in the next subarray. 
So everytime the sum of the elements became negative, you start to count from the next element, without having to back-track.

O(n)
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