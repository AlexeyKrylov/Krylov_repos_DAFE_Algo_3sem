#include <vector>
#include <iostream>
#include <queue>
#include <math.h>

class MatrixGraph {

public:

	std::vector<std::vector<size_t>> data;

	MatrixGraph(size_t N);

	~MatrixGraph() {};

	void AddEdge(size_t from, size_t to);

};


MatrixGraph::MatrixGraph(size_t N) {
	for (size_t i = 0; i < N; i++) {
		std::vector<size_t> tmp;
		data.push_back(tmp);
	}

}


void MatrixGraph::AddEdge(size_t from, size_t to) {
	data.at(from).push_back(to);
	data.at(to).push_back(from);
}


int main()
{
	size_t N, M;
	std::cin >> N >> M;
	MatrixGraph graph(N);

	for (size_t i = 0; i < M; i++) {
		size_t from, to;
		std::cin >> from >> to;
		graph.AddEdge(from, to);
	}
	size_t a, b;
	std::cin >> a >> b;
	std::queue<int> q;
	q.push(a);
	std::vector<bool> used(N);
	std::vector<int> d(N), res1(N), p(N);
	d[a] = 0;
	used[a] = true;
	p[a] = -1;
	res1[a] = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		std::vector<size_t> Vertices = graph.data[v];
		for (size_t i = 0; i < Vertices.size(); i++) {
			int to = Vertices[i];
			if (!used[to]) {
				used[to] = true;
				q.push(to);
				d[to] = d[v] + 1;
				p[to] = v;
				res1[to] = res1[v];
			}
			else if (d[v] == d[to] - 1 && p[to] != v) res1[to] += res1[v];
		}
	}

	std::cout << res1[b];
	return 0;
}