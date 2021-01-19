#include <iostream>
#include <vector>
#include <tuple>

/*
time complexity: O(n^2)
space complexity: O(1)

We use a vector to store the optimal vertex cover for each 
sub-tree given a node as root. Using recursion, we check
for both case where the current node is included or excluded 
in the vertex cover. When we exclude the current node, we 
have to include all his child to cover all its edges.
When we include the current node, we check all its child
that can be included or excluded.
*/
std::vector<std::vector<int64_t>> edges;
std::vector<int64_t> v_c;

int64_t vertex_cover(int64_t current, int64_t parent) {
	if (edges[current].size() == 1 && edges[current][0] == parent) return 0;		// No other edges except the one with the parent node

	int64_t vc_with_root = 1;				// case where the current node is included
	for (int64_t i = 0; i < edges[current].size(); i++) {
		if (edges[current][i] != parent) 
			v_c[edges[current][i]] != 0
				? vc_with_root += v_c[edges[current][i]]		// check if we already stored the best cv
				: vc_with_root += vertex_cover(edges[current][i], current);
	}

	int64_t vc_no_root = 0;					// the current node is excluded, meaning that we have to include its childs
	for (int64_t i = 0; i < edges[current].size(); i++) {
		int64_t child = edges[current][i];
		if (child != parent) {
			vc_no_root++;
			for (int j = 0; j < edges[child].size(); j++) {
				if (edges[child][j] != current) 
					v_c[edges[child][j]] != 0
						? vc_no_root += v_c[edges[child][j]]	// check if we already stored the best cv
						: vc_no_root += vertex_cover(edges[child][j], child);
			}
		}
	}

	v_c[current] = std::min(vc_with_root, vc_no_root);
	return v_c[current];
}



int main() {
	int64_t n;
	std::cin >> n;

	edges.reserve(n);
	for (int i = 0; i < n; i++) {
		edges[i].reserve(n);
	}

	v_c.reserve(n);

	for (int i = 0; i < n - 1; i++) {
		int64_t v1, v2;
		std::cin >> v1 >> v2;

		v1 -= 1;
		v2 -= 1;

		edges[v1].push_back(v2);
		edges[v2].push_back(v1);
	}

	std::cout << vertex_cover(0, -1);
}


