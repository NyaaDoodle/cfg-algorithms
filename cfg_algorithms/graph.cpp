#include "graph.h"
#include <iostream>

#define __GRAPH_CPP_DEBUG

Graph::Graph(unsigned int vertex_count) {
	this->vertex_count = vertex_count;
	this->adjlists.resize(vertex_count);
}

unsigned int Graph::get_vertex_count() const {
	return this->vertex_count;
}

void Graph::insert_edge(Vertex source, Vertex destination) {
	if (is_vertices_in_bounds(source, destination)) {
		if (!search_edge(source, destination)) {
			adjlists[source].push_front(destination);
		}
		#ifdef __GRAPH_CPP_DEBUG
		else {
			std::cerr << "Edge " << source << ' ' << destination << "already exists in graph" << std::endl;
		}
		#endif
	}
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

void Graph::print() const {
	for (Vertex s = 0; s < this->vertex_count; ++s) {
		std::cout << s << " : ";
		for (Vertex d : this->adjlists[s]) {
			std::cout << d << ' ';
		}
		std::cout << std::endl;
	}
}

void Graph::export_print() const {
	for (Vertex s = 0; s < this->vertex_count; ++s) {
		for (Vertex d : this->adjlists[s]) {
			std::cout << s << " " << d << std::endl;
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
			<< v1 << " 2: " << v2 << " count: " << this->vertex_count << std::endl;
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