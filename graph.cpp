#include "graph.h"
#include <iostream>
#include <queue>

#define __GRAPH_CPP_DEBUG

Graph::Graph(unsigned int vertex_count) {
	this->vertex_count = vertex_count;
	this->adjlists.resize(vertex_count);
}

bool Graph::insert_edge(Vertex source, Vertex destination) {
	bool is_edge_added = false;
	if (is_vertices_in_bounds(source, destination)) {
		if (!search_edge(source, destination)) {
			adjlists[source].push_front(destination);
			is_edge_added = true;
		}
		else {
			std::cout << "Edge \"" << (source + 1) << ' ' << (destination + 1) << "\" already exists in graph" << std::endl;
		}
	}
	else {
		std::cout << "Supplied vertices are out of bounds." << std::endl;
	}
	return is_edge_added;
}

VertexSet Graph::get_prev_set(Vertex vertex) const {
	VertexSet prev_set = VertexSet(this->vertex_count);
	for (Vertex i = 0; i < this->vertex_count; ++i) {
		if (search_edge(i, vertex)) {
			prev_set.set_vertex(i);
		}
	}
	return prev_set;
}

Graph Graph::construct_subgraph_from_vertex_set(const VertexSet& vertices_of_subgraph) const {
	// This still leaves the excluded vertices to be "lone vertices", but are not removed from the subgraph itself.
	Graph subgraph = Graph(this->vertex_count);
	for (Vertex i = 0; i < this->vertex_count; ++i) {
		if (vertices_of_subgraph.is_vertex_set(i)) {
			for (Vertex j : this->adjlists[i]) {
				if (vertices_of_subgraph.is_vertex_set(j)) {
					subgraph.insert_edge(i, j);
				}
			}
		}
	}
	return subgraph;
}

void Graph::print() const {
	for (Vertex s = 0; s < this->vertex_count; ++s) {
		for (Vertex d : this->adjlists[s]) {
			std::cout << (s+1) << ' ' << (d+1) << std::endl;
		}
	}
}

bool Graph::is_vertices_in_bounds(Vertex v1, Vertex v2) const {
	bool v1_result = v1 >= 0 && v1 < this->vertex_count;
	bool v2_result = v2 >= 0 && v2 < this->vertex_count;
	bool result = v1_result && v2_result;
	#ifdef __GRAPH_CPP_DEBUG
	if (!result) {
		std::cerr << "Supplied vertices out of bounds: 1: "
			<< (v1+1) << " 2: " << (v2+1) << " count: " << this->vertex_count << std::endl;
	}
	#endif
	return result;
}

bool Graph::search_edge(Vertex source, Vertex destination) const {
	if (is_vertices_in_bounds(source, destination)) {
		for (Vertex v : adjlists[source]) {
			if (v == destination) {
				return true;
			}
		}
	}
	return false;
}