#include <iostream>
#include <vector>
#include <stack>

/*
Time complexity: O(N) 
Space complexity: O(N)

This problem is solved using a stack to compare the elements to find the next larger value.
Scanning the vector from right to left, we try to put in the stack each number. 
Before putting a new element in the stack, we remove all the element smaller than the new one. 
The reason behind this, is that the elements in the stack became "useless" 
as soon a new value bigger than them is found and added.
Infact, when comparing a new elementi with the stack, the element can be bigger or smaller than the top of the stack:
- if it's smaller, then the top of the stack is its next larger value.
- if it's bigger, I don't care what is in the stack until a value bigger than the element is found

The time complexity is O(N) because each element is added and removed at most one time, 
and every time I scan som element in the stack I remove them.
*/

void next_larger_ele(std::vector<long> v)
{
	std::stack<long> st;
	std::vector<long> r;

	int n = v.size();
	r.reserve(n);

	st.push(v[n - 1]); 							// the stack is inizialize with the most-right element
	r.push_back(-1);   							// the most-rigth element will never have a next larger element

	for (int i = n - 2; i >= 0; i--)
	{
		while (!st.empty() && v[i] > st.top()) 	// remove from the top of the stack all the values smaller than the current one.
		{
			st.pop();
		}

		if (st.empty()) 						// if the stack is empty, the current value is bigger then all the elements to its right ...
		{										
			r.push_back(-1);					
		}										
		else									// ... otherwise, the element in the top of the stack is the one who is immediately bigger then the current one
		{
			r.push_back(st.top());
		}
		st.push(v[i]); 							// had the current value to the stack
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
