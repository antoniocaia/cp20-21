#include <iostream>
#include <vector>

/*
Time complexity: O(n log n)
Space complexity: O(n log n)

This solution use a modified version of the mergesort alghorithm.
*/

long long merge(std::vector<long long> &v, long long l, long long m, long long r)
{
	long long c = 0;

	long long i = l;
	long long j = m;

	std::vector<long long> tmp;
	tmp.reserve(v.size());
	long long k = l;

	while (i <= m - 1 && j <= r) {
		if (v[i] <= v[j]) {
			tmp[k] = v[i];
			i++;
		} else {
			tmp[k] = v[j];
			j++;

			c += m - i;
		}
		k++;
	}

	while (i <= m - 1) {
		tmp[k] = v[i];
		i++;
		k++;
	}

	while (j <= r) {
		tmp[k] = v[j];
		j++;
		k++;
	}

	for (long long y = l; y <= r; y++) {
		v[y] = tmp[y];
	}
	return c;
}

long long mergesort(std::vector<long long> &v, long long l, long long r) {
	long long c = 0;
	if (l < r)
	{
		long long mid = (l + r) / 2;
		c += mergesort(v, l, mid);
		c += mergesort(v, mid + 1, r);
		c += merge(v, l, mid + 1, r);
	}
	return c;
}

int main()
{
	long long test_case;
	std::cin >> test_case;

	for (long long t = 0; t < test_case; t++)
	{
		long long size;
		std::cin >> size;
		std::vector<long long > v;
		v.reserve(size);

		for (long long i = 0; i < size; i++)
		{
			long long input = 0;
			std::cin >> input;
			v.push_back(input);
		}
		
		std::cout << mergesort(v, 0, size - 1);
		std::cout << "\n";
	}
}