#include <iostream>
#include <vector>

/*
To find the leaders in an array a good approach is to check the vector from rigth to left, keeping track of the max value: 
doing so, everytime a new max is found, we are sure that all the elements to its right are smaller than it,and this satisfy the requisite to be a leader.

Time complexity: O(N)
Space complexity: O(1)
*/

void find_leader(std::vector<int> v)
{
	int n = v.size();
	std::vector<int> lead;
	lead.reserve(n);

	int max = v[n - 1];
	lead.push_back(v[n - 1]);
	int c = 1;

	for (int i = n - 2; i >= 0; i--)
	{
		if (v[i] >= max)
		{
			lead.push_back(v[i]);
			max = v[i];
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
		std::vector<int> v;
		v.reserve(size);

		for (int i = 0; i < size; i++)
		{
			int input = 0;
			std::cin >> input;
			v.push_back(input);
		}

		find_leader(v);
		std::cout << "\n";
	}
}