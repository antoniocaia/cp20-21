#include <iostream>
#include <vector>
#include <algorithm>

using li = long int;

struct node {
	li color;
	li parent;
	std::vector<li> child;
	std::vector<li> color_fr;

	// REMAP COLORS
	node(li c, li p, li n) : color_fr(n) {
		color = c;
		parent = p;
		child.reserve(n);
	}
};

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

// li solution = 0;

// bool sort_q(query qa, query qb) {
// 	if (qa.root != qb.root)
// 		return qa.root > qb.root;

// 	return qa.k < qb.k;
// }

// void add(li color, li k, std::vector<li>& f) {
// 	f[color]++;
// 	if (f[color] == k) solution++;
// }

// void remove(li color, li k, std::vector<li>& f) {
// 	f[color]--;
// 	if (f[color] + 1 == k) solution--;
// }

std::vector<li> visit(li ind, std::vector<node>& ns) {
	for (int i = 0; i < ns[ind].child.size(); i++) {
		std::vector<li> tmp = visit(ns[ind].child[i], ns);
		//merge sol
		for (int j = 0; j < tmp.size(); j++) {
			ns[ind].color_fr[j] += tmp[j];
		}
	}

	ns[ind].color_fr[ns[ind].color]++;
	return ns[ind].color_fr;
}


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

	std::vector<node> nodes;
	nodes.reserve(n);

	for (int i = 0; i < n; i++) {
		nodes.push_back(node(mem_col[i], -1, color_n));
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

	// std::vector<query> queries;
	// queries.reserve(q);

	// for (int i = 0; i < q; i++) {
	// 	li root;
	// 	li k;
	// 	scanf("%ld", &root);
	// 	scanf("%ld", &k);
	// 	root -= 1;
	// 	queries.push_back(query(root, k, i));
	// }

	// MO
	// std::sort(queries.begin(), queries.end(), sort_q);
	// std::vector<li>freq(100001);

	// li current = 0;
	// for(int i = 0; i < q; i ++) {
	// 	query q = queries[i];

	// }

	visit(0, nodes);

	for (int i = 0; i < q; i++) {
		li root;
		li k;
		scanf("%ld", &root);
		scanf("%ld", &k);
		root -= 1;

		li sol = 0;
		std::vector<li> tmp = nodes[root].color_fr;
		for (int i = 0; i < tmp.size(); i++)
			if (tmp[i] >= k) sol++;

		printf("%ld\n", sol);
	}
}
