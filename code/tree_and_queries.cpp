#include <iostream>
#include <vector>
#include <algorithm>

using li = long int;

struct query {
	li root;
	li k;
	li ind;

	query(li r, li kk, li i) {
		root = r;
		k = kk;
		ind = i;
	}
};

li num_color;

struct node {
	li color;
	li parent;
	std::vector<li> child;
	//std::vector<li> color_fr;

	std::vector<std::pair<li, li>> node_qs;

	node(li c, li p, li n, li cn) {
		color = c;
		parent = p;
		//node_qs.reserve();
		//child.reserve(n);
	}
};

std::vector<li> visit(li ind, std::vector<node>& ns, std::vector<std::pair<li, li>>& s) {
	std::vector<li> color_frq(num_color);

	// Update the frquencies
	for (int i = 0; i < ns[ind].child.size(); i++) {
		std::vector<li> tmp = visit(ns[ind].child[i], ns, s);
		//merge sol
		for (int j = 0; j < tmp.size(); j++) {
			color_frq[j] += tmp[j];
		}
	}
	color_frq[ns[ind].color]++;

	//Solve query
	for (int i = 0; i < ns[ind].node_qs.size(); i++) {
		li k = ns[ind].node_qs[i].first;
		li ti = ns[ind].node_qs[i].second;

		li tot = 0;
		for (int j = 0; j < color_frq.size(); j++) {
			if (color_frq[j] >= k) tot++;
		}
		s.push_back(std::make_pair(tot, ti));
	}
	return color_frq;
}

bool sort_sol(std::pair<li, li> a, std::pair<li, li> b) { return a.second < b.second; }

int main() {
	std::ios_base::sync_with_stdio(false);

	// input
	li n, q;
	scanf("%ld", &n);
	scanf("%ld", &q);

	// remap colors
	std::vector<li> colors(100001, -1);
	li color_n = 0;
	std::vector<li> mem_col(n);

	for (int i = 0; i < n; i++) {
		li color;
		scanf("%ld", &color);
		if (colors[color] == -1) {
			colors[color] = color_n;
			color_n++;
		}
		mem_col[i] = colors[color];
	}
	num_color = color_n;

	std::vector<node> nodes;
	nodes.reserve(n);

	for (int i = 0; i < n; i++) {
		nodes.push_back(node(mem_col[i], -1, n, color_n));
	}

	for (int i = 0; i < n - 1; i++) {
		li p;
		li c;
		scanf("%ld", &p);
		scanf("%ld", &c);
		p -= 1;
		c -= 1;

		if (p > c) {
			li tmp = p;
			p = c;
			c = tmp;
		}

		nodes[p].child.push_back(c);
		nodes[c].parent = p;
	}

	for (int i = 0; i < q; i++) {
		li root;
		li k;
		scanf("%ld", &root);
		scanf("%ld", &k);
		root -= 1;
		nodes[root].node_qs.push_back(std::make_pair(k, i));
	}

	std::vector<std::pair<li, li>> solutions;
	visit(0, nodes, solutions);

	std::sort(solutions.begin(), solutions.end(), sort_sol);
	for (int i = 0; i < solutions.size(); i++) {
		printf("%ld\n", solutions[i].first);
	}
}
