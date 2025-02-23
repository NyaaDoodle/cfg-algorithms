#pragma once
#include "vertex.h"
#include "vertexset.h"
#include <list>
#include <vector>

using namespace std;

class Graph {
protected:
	unsigned int vertex_count;
	vector<list<Vertex>> adjlists;
	bool is_vertices_in_bounds(Vertex v1, Vertex v2) const;
public:
	Graph(unsigned int vertex_count);
	bool insert_edge(Vertex source, Vertex destination);
	bool search_edge(Vertex source, Vertex destination) const;
	VertexSet get_prev_set(Vertex vertex) const;
	Graph construct_subgraph_from_vertex_set(const VertexSet& vertices_of_subgraph) const;
	void print() const;
};