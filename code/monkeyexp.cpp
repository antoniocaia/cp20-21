#include <iostream>
#include <vector>

/*
Exp search for the value
*/

bool test_k(int k, std::vector<int> v)
{
	if (v[0] > k)
		return false;
	else if (v[0] == k)
		k--;

	int n = v.size();
	for (int i = 1; i < n; i++)
	{
		int gap = v[i] - v[i - 1];
		if (gap > k)
			return false;
		else if (gap == k)
			k--;
	}
	return true;
}

int binary(std::vector<int> v, int s, int e)
{
	if (v.size() == 1)
		return v[0];

	int top;
	while (s <= e)
	{
		int m = s + (e - s) / 2;
		if (tryk(m, v))
		{
			top = m;
			e = m - 1;
		}
		else
		{
			s = m + 1;
		}
	}
	return top;
}

int expo(std::vector<int> v)
{
	if (v.size() == 1)
		return v[0];

	int i = v[0];

	while (!test_k(i, v))
		i *= 2;

	return binary(v, i / 2 - 1, i);
}

int main()
{
	int test_case;
	std::cin >> test_case;
	std::vector<int> r;
	r.reserve(test_case);

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
		std::cout << "Case " << t + 1 << ": " << expo(v) << "\n";
	}
}
