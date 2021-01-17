#include <iostream>
#include <vector>

/*
time complexity: O(n)
space complexity: O(1)

Because the numbers in the vector are in the range 1..X, the size of the vector is equals to the bigger number inside it. 
Using Gauss sum it's possible to determinate the sum of the elements including the missing number.
Subtracting from this value the sum of the elements in the vector, it's possible to find the missing value.
*/

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