#include <iostream>
#include <vector>

int mat[3][4] = {
	{1, 2, 6, 9},
	{0, 0, 3, 1},
	{1, 7, 7, 2}
};

int res[3][4];

int get_val(int i, int j) {
	if (i == j && i == 0) return 0;
	if (i == 0 && j > 0) return res[i][j - 1];
	if (i > 0 && j == 0) return res[i - 1][j];
	return std::min(res[i - 1][j], res[i][j - 1]);
}

int main() {
	for(int j = 0; j < 4; j++)
		res[0][j] = mat[0][j] + get_val(0, j);

	for(int i = 0 ; i < 3; i ++) {
		res[i][0]  = mat[i][0] + get_val(i, 0);
	}

	for(int i = 1; i < 3; i ++) {
		for(int j = 1; j < 4; j++) {
			res[i][j]  = mat[i][j] + get_val(i, j);
		}
	}

	std::cout << "done";

}