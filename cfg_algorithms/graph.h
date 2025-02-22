#pragma once
#include "vertex.h"
#include "vertexset.h"
#include <list>
#include <vector>

using namespace std;

class Graph {
private:
	unsigned int vertex_count;
	vector<list<Vertex>> adjlists;
	bool is_vertices_in_bounds(Vertex v1, Vertex v2) const;
public:
	Graph(unsigned int vertex_count);
	unsigned int get_vertex_count() const;
	void insert_edge(Vertex source, Vertex destination);
	bool search_edge(Vertex source, Vertex destination) const;
	VertexSet get_prev_set(Vertex vertex) const;
	void print() const;
	void export_print() const;
};