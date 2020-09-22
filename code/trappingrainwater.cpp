#include <iostream>
#include <vector>

/*
This solution is based on the fact that you can divide the vector containing the walls in segments, 
where each segment has its right-most and left-most walls higher then the walls inside the segment.

          XX
XX        XX          
XX    XX  XX      XX  
XX  XXXX  XXXXXX  XXXX
0         1       2

0-1 one is the first segment, 1-2 the second one.

Count the water inside a segment is trivial: the lower between two external walls define the level of the water, 
and subtracting from it the height of each wall give us the total ammount of water in a segment.

To determinate when a segment stop, there is two possible scenario: 
in the good one, a wall higher than the first one is found, and that stop the search right away. 
In the bad one, tha alghoritm has to scan all the remaining vector to found higher one.

In the worst case scenario (a vector sorted from higher to lower values) the complexity is O(n^2)
*/

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

	for (int t = 0; t < test_case; t++)
	{
		int size;
		std::cin >> size;
		std::vector<int> l;
		l.reserve(size);

		for (int j = 0; j < size; j++)
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