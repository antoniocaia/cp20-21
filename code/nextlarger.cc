#include <iostream>
#include <vector>
#include <stack>

/*
This problem is solved using a stack.
Scanning the vector from right to left, we put in the stack the first number. 
From now on, before putting a new element in the stack, we remove all the element smaller than the new one. 
The reason behind this action is that the elements in the stack became "useless" as soon a new value bigger than them is found:
- the new element will be for sure the next larger value for every next elements smaller than it.
- if a highr element is going to be found, we can tell for sure that there isn't any element bigger than it.

O(N)
*/ 

void next_larger_ele(std::vector<long> v)
{
	std::stack<long> st;
	std::vector<long> r;

	int n = v.size();
	r.reserve(n);

	st.push(v[n - 1]); 	// the stack is inizialize with the most-right element
	r.push_back(-1);	// the most-rigth element will never have a next larger element

	for (int i = n - 2; i >= 0; i--)
	{
		while (!st.empty() && v[i] > st.top())	// remove from the top of the stack all the values smaller than the current one.
		{
			st.pop();
		}

		if (st.empty())	// if the stack is empty, the current value is bigger then all the elements to its right ...
		{
			r.push_back(-1);
		}
		else	// ... otherwise, the element in the top of the stack is the one who is immediately bigger then the current one
		{
			r.push_back(st.top());
		}
		st.push(v[i]);	// the current value is had to the stack
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

		next_larger_ele(v);
		std::cout << "\n";
	}
}
