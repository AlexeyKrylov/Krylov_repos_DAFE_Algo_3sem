#include <vector>
#include <iostream>
#include <queue>
#include <math.h>

class MatrixGraph {

public:

	std::vector<std::vector<int>> data;

	MatrixGraph(int N);

	~MatrixGraph() {};

	void AddEdge(int from, int to);

};


MatrixGraph::MatrixGraph(int N) {
	std::vector<bool> tmp;
	for (int i = 0; i < N; i++) {
		std::vector<int> tmp;
		data.push_back(tmp);
	}

}


void MatrixGraph::AddEdge(int from, int to) {
	data.at(from).push_back(to);
	data.at(to).push_back(from);
}


int main()
{
	int N, M;
	std::cin >> N >> M;
	int res = N + 1;
	MatrixGraph graph(N);

	for (int i = 0; i < M; i++) {
		int from, to;
		std::cin >> from >> to;
		graph.AddEdge(from, to);
	}

	for (int j = 0; j < N; j++) {
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
			for (int i = 0; i < graph.data[v].size(); i++) {
				int to = graph.data[v][i];
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