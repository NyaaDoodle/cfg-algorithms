#pragma once
#include "vertex.h"
#include <vector>

using namespace std;

class VertexSet {
private:
	unsigned int vertex_count;
	vector<bool> boolarray;
	bool is_vertex_in_bounds(Vertex vertex) const;
	void resize(unsigned int vertex_count);
	static bool is_vertex_sets_same_length(const VertexSet& vs1, const VertexSet& vs2);
public:
	VertexSet(unsigned int vertex_count);
	void set_vertex(Vertex vertex_to_set);
	void unset_vertex(Vertex vertex_to_unset);
	void set_all_vertices();
	void unset_all_vertices();
	bool is_vertex_set(Vertex query_vertex) const;
	bool is_vertex_unset(Vertex query_vertex) const;
	unsigned int count_set_vertices() const;
	void print() const;
	static VertexSet union_set(const VertexSet& vs1, const VertexSet& vs2);
	static VertexSet intersection_set(const VertexSet& vs1, const VertexSet& vs2);
	static bool is_vertex_sets_equal(const VertexSet& vs1, const VertexSet& vs2);
};