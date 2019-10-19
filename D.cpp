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
	std::vector<bool> tmp;
	for (size_t i = 0; i < N; i++) {
		std::vector<bool> tmp;
		for (size_t j = 0; j < N; j++)
			tmp.push_back(false);
		data.push_back(tmp);
	}

}


void MatrixGraph::AddEdge(size_t from, size_t to) {
	data.at(from).at(to) = from;
	data.at(to).at(from) = to;
}


int main()
{
	size_t N, M;
	std::cin >> N >> M;
	int res = N + 1;
	MatrixGraph graph(N);

	for (size_t i = 0; i < M; i++) {
		size_t from, to;
		std::cin >> from >> to;
		graph.AddEdge(from, to);
	}

	for (size_t j = 0; j < N; j++) {
		std::queue<int> q;
		q.push(j);
		std::vector<bool> used(N);
		std::vector<int> d(N), p(N);
		d[j] = 0;
		used[j] = true;
		p[j] = -1;
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (size_t i = 0; i < N; i++) {
				int to = graph.data[v][i];
				if (to == false) continue;
				if (!used[to]) {
					used[to] = true;
					q.push(to);
					d[to] = d[v] + 1;
					p[to] = v;
				}
				else {
					int tmp = d[v] + d[to] + 1;
					if (tmp < res && to != p[v]) res = tmp;
				}
			}
		}
	}
	if (res == N + 1)
		res = -1;

	std::cout << res;
	return 0;
}