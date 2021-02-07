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
 
 
struct node {
	li color;
	li parent;
	std::vector<li> child;
	std::vector<std::pair<li, li>> node_qs;
 
	node(li c, li p, li n, li cn, li q) {
		color = c;
		parent = p;
		//node_qs.reserve(q);
		//child.reserve(n);
	}
};
 
bool sort_dec(li a, li b) { return a > b; };
bool sort_second(std::pair<li, li> a, std::pair<li, li> b) { return a.second < b.second; }
bool sort_first(std::pair<li, li> a, std::pair<li, li> b) { return a.first > b.first; }
 
std::vector<node> ns;
std::vector<std::pair<li, li>> s;
 
 
std::vector<li> visit(li ind, li num_color) {
	std::vector<li> color_frq(num_color);
 
	// Update the frquencies
	for (li i = 0; i < ns[ind].child.size(); i++) {
		std::vector<li> tmp_col_fr = visit(ns[ind].child[i], num_color);
		//merge sol
		for (li j = 0; j < tmp_col_fr.size(); j++) {
			color_frq[j] += tmp_col_fr[j];
		}
	}
	color_frq[ns[ind].color]++;
 
 
	// Process queries
	if (ns[ind].node_qs.size() > 0) {
		std::sort(ns[ind].node_qs.begin(), ns[ind].node_qs.end(), sort_first);
 
		std::vector<li> sorted_col_freq = color_frq;
		std::sort(sorted_col_freq.begin(), sorted_col_freq.end(), sort_dec);
 
		li tot = 0;
		li q_index = 0;
 
		li k = ns[ind].node_qs[q_index].first;
		li ti = ns[ind].node_qs[q_index].second;
		li j = 0;
		while (j < sorted_col_freq.size()) {
			if (sorted_col_freq[j] >= k) {
				tot++;
				j++;
			}
			else {
				s.push_back(std::make_pair(tot, ti));
				q_index++;
				if (q_index >= ns[ind].node_qs.size()) return color_frq;
				k = ns[ind].node_qs[q_index].first;
				ti = ns[ind].node_qs[q_index].second;
			}
		}
		// solver remaining query
		for (li i = q_index; i < ns[ind].node_qs.size(); i++) {
			li tii = ns[ind].node_qs[i].second;
			s.push_back(std::make_pair(tot, tii));
		}
	}
 
	return color_frq;
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
 
	for (li i = 0; i < n; i++) {
		li color;
		scanf("%ld", &color);
		if (colors[color] == -1) {
			colors[color] = color_n;
			color_n++;
		}
		mem_col[i] = colors[color];
	}
 
	ns.reserve(n);
 
	for (li i = 0; i < n; i++) {
		ns.push_back(node(mem_col[i], -1, n, color_n, q));
	}
 
	for (li i = 0; i < n - 1; i++) {
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
 
		ns[p].child.push_back(c);
		ns[c].parent = p;
	}
 
	for (li i = 0; i < q; i++) {
		li root;
		li k;
		scanf("%ld", &root);
		scanf("%ld", &k);
		root -= 1;
		ns[root].node_qs.push_back(std::make_pair(k, i));
	}
 
	s.reserve(q);
	visit(0, color_n);
 
	std::sort(s.begin(), s.end(), sort_second);
	for (li i = 0; i < s.size(); i++) {
		printf("%ld\n", s[i].first);
	}
}