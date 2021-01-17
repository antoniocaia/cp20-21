#include <iostream>
#include <sstream>

/*
time complexity: O(n)
space complexity: O(1)

We scan the string, checking for any sub-string that doesn't match one of the pattern 
*/

bool m_n(std::string str) {
	for (int64_t i = 0; i < str.size(); i++) {
		if (str[i] != '1' && str[i] != '4') return false;

		if (str[i] == '4') {
			if (i > 0) {
				if (str[i - 1] == '4') {
					if (i > 1) {
						if (str[i - 2] != '1') return false;
					}
					else return false;
				}
			}
			else return false;
		}
	}
	return true;
}

int main() {
	std::string str;
	std::cin >> str;

	if (m_n(str)) std::cout << "YES";
	else std::cout << "NO";
}