#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
	int u, v, w;
	Edge() {}
	Edge(int u, int v, int w) : u(u), v(v), w(w) {}

	friend bool operator < (const Edge& a, const Edge& b) {
		if (a.w == b.w) 
			return a.u < b.u;
		return a.w < b.w;
	}
};

struct DSU {
	vector<int> parent, size;

	DSU() {}
	DSU(int n) {
		parent.assign(n + 1, 0);
		size.assign(n + 1, 1);
		for(int i = 1; i <= n; ++i) {
			parent[i] = i;
		}
	}

	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}

	bool canJoin(int u, int v) {
		int p1 = find(u);
		int p2 = find(v);
		if (p1 == p2) return false;
		if (size[p1] < size[p2]) swap(p1, p2);
		parent[p2] = p1;
		size[p1] += size[p2];
		return true;
	}

};

int n, m;
vector<Edge> edges;
DSU dsu;

void input() {
	cin >> n >> m;
	edges.assign(m, Edge());
	dsu = DSU(n);
	for(int i = 0; i < m; ++i) {
		cin >> edges[i].u >> edges[i].v >> edges[i].w;
	}
}

void kruskal(vector<Edge> edges, DSU& dsu) {
	sort(begin(edges), end(edges));

	int result = 0, count = 0;
	vector<Edge> mst;
	for(int i = 0; i < m; ++i) {
		if (count == n - 1) break;
		if (!dsu.canJoin(edges[i].u, edges[i].v)) {
			continue;
		}
		mst.emplace_back(edges[i].u, edges[i].v, edges[i].w);
		result += edges[i].w;
		count++;
	}

    if (count != n - 1) {
        cout << "Khong ton tai cay khung nho nhat\n";
        return;
    }

	cout << "Tong trong so cua cay khung nho nhat: " << result << '\n';
	cout << "Cac canh trong cay khung nho nhat:\n";
	for(auto [u, v, w] : mst) {
		cout << u << ' ' << v << ' ' << w << '\n';
	}
}

void process(void) {
	input();
	kruskal(edges, dsu);
}