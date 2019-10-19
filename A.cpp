#include <vector>
#include <iostream>


enum Color {
	WHITE,
	GRAY,
	BLACK
};


class MatrixGraph{

private: 

	std::vector<std::vector<bool>> data;

public:

	MatrixGraph(size_t N);

	~MatrixGraph() {};

	void AddEdge(size_t from, size_t to);

	bool HasEdge(size_t from, size_t to);

	std::vector<size_t> GetVertices(size_t vertice);

	size_t GetVerticesCount();

	bool dfs(size_t vertice, std::vector<Color>& colors);

	bool HasRoad(size_t from, size_t to, std::vector<Color>& colors);

	bool ConnectivityGraph(size_t from, std::vector<Color>& colors);

	bool HasCycle(size_t from, std::vector<Color>& colors);
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
	data.at(from).at(to) = true;
	data.at(to).at(from) = true;
}


bool MatrixGraph::HasEdge(size_t from, size_t to) {
	return data.at(from).at(to);
}


std::vector<size_t> MatrixGraph::GetVertices(size_t from) {
	std::vector<size_t> res;
	for (size_t to = 0; to < data.size(); to++) {
		if (data.at(from).at(to) == true)
			res.push_back(to);
	}
	return res;
}


size_t MatrixGraph::GetVerticesCount() {
	return data.size();
}


bool MatrixGraph::dfs(size_t from, std::vector<Color>& colors) {
	colors[from] = GRAY;
	std::vector<size_t> descendant = this->GetVertices(from);
	for (size_t next = 0; next < descendant.size(); next++) {
		if (colors[descendant[next]] == GRAY) {
			return true;
		}else if (colors[from] == WHITE)
				if (dfs(descendant[next], colors))
					return true;
	}
	colors[from] = BLACK;
	return false;
}


bool MatrixGraph::HasRoad(size_t from, size_t to, std::vector<Color>& colors) {
	if (from == to) return true;
	colors[from] = GRAY;
	std::vector<size_t> descendant = this->GetVertices(from);
	for (size_t next = 0; next < descendant.size(); next++) {
		if (colors[descendant[next]] == GRAY) {
			return true;
		}
		else if (colors[descendant[next]] == WHITE)
				if (HasRoad(descendant[next], to, colors))
					return true;
	}
	colors[from] = BLACK;
	return false;
}


bool MatrixGraph::ConnectivityGraph(size_t from, std::vector<Color>& colors) {
	size_t v_count = 1;
	colors[from] = GRAY;
	std::vector<size_t> descendant = this->GetVertices(from);
	for (size_t next = 0; next < descendant.size(); next++) {
		if (colors[descendant[next]] == GRAY)
			return true;
		else if (colors[descendant[next]] == WHITE)
				if (ConnectivityGraph(descendant[next], colors))
					return true;
	}
	colors[from] = BLACK;
	return false;
}


bool MatrixGraph::HasCycle(size_t from, std::vector<Color>& colors) {
	return this->dfs(from, colors);
} 



int main()
{
	std::cout << "OK";
	std::cin.get();
	return 0;
}