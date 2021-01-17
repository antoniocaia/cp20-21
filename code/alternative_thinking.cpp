#include <iostream>
#include <vector>

/*
time complexity: O(n)
space complexity: O(1)

Flipping a sequence can increase the number of consecutive non-contiguous
elements by up to 2. 

Given the sequence 1011011011, its longest sub-sequence is 
[101] 1 [01] 1 [01] 1
To improve the sequence, we can flip the 101 sub-sequence in the middle 
101(101)1011,
obtaining:
101(010)1011 
with a longest sub-sequence of
[101010101] 1

The sub-sequence length increased of 2: 
the element that where already counted are still part of it, only "flipped",
but now it's possible to include the extremity of the flipped sub-sequence
*/

int main() {
	int64_t n;
	std:: cin >> n;
	std::string b;
	std::cin >> b;

	int64_t length = 0;
	char next_char = b[0];
	for (int64_t i = 0; i < b.size(); i++) {
		if (b[i] == next_char) {
			next_char == '1' ? next_char = '0' : next_char = '1';
			length++;
		}
	}

	std::cout << std::min(length + 2, int64_t(b.size()));
	return 0;
}