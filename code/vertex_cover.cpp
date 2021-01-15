#include <iostream>
#include <vector>
#include <tuple>

std::vector<std::vector<int64_t>> edges;
std::vector<int64_t> vc;

int64_t vertex_cover(int64_t current_node, int64_t parent) {
	if (edges[current_node].size() == 1 && edges[current_node][0] == parent) return 0;
	if (vc[current_node] != 0) return vc[current_node];

	int64_t vc_with_root = 1;
	for (int64_t i = 0; i < edges[current_node].size(); i++) {
		if (edges[current_node][i] != parent)
			vc[edges[current_node][i]] != 0 ? vc_with_root += vc[edges[current_node][i]] : vc_with_root += vertex_cover(edges[current_node][i], current_node);
		//vc_with_root += vertex_cover(edges[current_node][i], edges, vc, current_node);
	}

	int64_t vc_no_root = 0;
	for (int64_t i = 0; i < edges[current_node].size(); i++) {
		int64_t child = edges[current_node][i];
		if (child != parent) {
			vc_no_root++;
			for (int j = 0; j < edges[child].size(); j++) {
				if (edges[child][j] != current_node)
					vc[edges[child][j]] != 0 ? vc_no_root += vc[edges[child][j]] : vc_no_root += vertex_cover(edges[child][j], child);
				//vc_no_root += vertex_cover(edges[child][j], edges, vc, child);
			}
		}
	}

	vc[current_node] = std::min(vc_with_root, vc_no_root);

	return vc[current_node];
}

int main() {
	int64_t n;
	std::cin >> n;

	edges.reserve(n);
	for (int i = 0; i < n; i++) {
		edges[i].reserve(n);
	}

	vc.reserve(n);

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


