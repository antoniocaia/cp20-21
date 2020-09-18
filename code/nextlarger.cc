#include <iostream>
#include <vector>
#include <deque>

void sliding_window(std::vector<long> v)
{
	std::deque<long> dq;
	std::vector<long> r;

	int n = v.size();
	r.reserve(n);

	dq.push_front(v[n - 1]);
	r.push_back(-1);

	for (int i = n - 2; i >= 0; i--)
	{
		while (!dq.empty() && v[i] > dq.back())
		{
			dq.pop_back();
		}

		if (dq.empty())
		{
			r.push_back(-1);
		}
		else
		{
			r.push_back(dq.back());
		}
		dq.push_back(v[i]);
	}

	for (int i = n - 1; i >= 0; i--)
	{
		std::cout << r[i] << " ";
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
		std::vector<long> v;
		v.reserve(size);

		for (int i = 0; i < size; i++)
		{
			long input = 0;
			std::cin >> input;
			v.push_back(input);
		}

		sliding_window(v);
		std::cout << "\n";
	}
}