#include "vertexset.h"
#include <iostream>

#define __VERTEXSET_CPP_DEBUG

VertexSet::VertexSet(unsigned int vertex_count) {
	this->vertex_count = vertex_count;
	this->boolarray.resize(vertex_count);
	unset_all_vertices();
}

void VertexSet::set_vertex(Vertex vertex_to_set) {
	if (is_vertex_in_bounds(vertex_to_set)) {
		this->boolarray[vertex_to_set] = true;
	}
}

void VertexSet::unset_vertex(Vertex vertex_to_unset) {
	if (is_vertex_in_bounds(vertex_to_unset)) {
		this->boolarray[vertex_to_unset] = false;
	}
}

void VertexSet::set_all_vertices() {
	for (unsigned int i = 0; i < this->vertex_count; ++i) {
		this->boolarray[i] = true;
	}
}

void VertexSet::unset_all_vertices() {
	for (unsigned int i = 0; i < this->vertex_count; ++i) {
		this->boolarray[i] = false;
	}
}

bool VertexSet::is_vertex_set(Vertex query_vertex) const {
	if (is_vertex_in_bounds(query_vertex)) {
		return this->boolarray[query_vertex];
	}
	return false;
}

bool VertexSet::is_vertex_unset(Vertex query_vertex) const {
	if (is_vertex_in_bounds(query_vertex)) {
		return !this->boolarray[query_vertex];
	}
	return false;
}

unsigned int VertexSet::count_set_vertices() const {
	unsigned int set_vertices_counter = 0;
	for (Vertex i = 0; i < this->vertex_count; ++i) {
		if (this->is_vertex_set(i)) {
			++set_vertices_counter;
		}
	}
	return set_vertices_counter;
}

void VertexSet::print() const {
	std::cout << "{";
	for (Vertex i = 0; i < this->vertex_count; ++i) {
		if (this->boolarray[i] == true) {
			std::cout << i << ' ';
		}
	}
	std::cout << "\b}" << std::endl;
}

VertexSet VertexSet::union_set(const VertexSet& vs1, const VertexSet& vs2) {
	VertexSet unionset = VertexSet(0);
	if (is_vertex_sets_same_length(vs1, vs2)) {
		unionset.resize(vs1.vertex_count);
		for (unsigned int i = 0; i < vs1.vertex_count; ++i) {
			if (vs1.is_vertex_set(i) || vs2.is_vertex_set(i)) {
				unionset.set_vertex(i);
			}
		}
	}
	#ifdef __VERTEXSET_CPP_DEBUG
	else {
		std::cerr << "Union set is not valid" << std::endl;
	}
	#endif
	return unionset;
}

VertexSet VertexSet::intersection_set(const VertexSet& vs1, const VertexSet& vs2) {
	VertexSet intersectset = VertexSet(0);
	if (is_vertex_sets_same_length(vs1, vs2)) {
		intersectset.resize(vs1.vertex_count);
		for (unsigned int i = 0; i < vs1.vertex_count; ++i) {
			if (vs1.is_vertex_set(i) && vs2.is_vertex_set(i)) {
				intersectset.set_vertex(i);
			}
		}
	}
	#ifdef __VERTEXSET_CPP_DEBUG
	else {
		std::cerr << "Intersection set is not valid" << std::endl;
	}
	#endif
	return intersectset;
}

bool VertexSet::is_vertex_sets_equal(const VertexSet& vs1, const VertexSet& vs2) {
	if (is_vertex_sets_same_length(vs1, vs2)) {
		for (Vertex i = 0; i < vs1.vertex_count; ++i) {
			if (!(vs1.is_vertex_set(i) && vs2.is_vertex_set(i))) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool VertexSet::is_vertex_in_bounds(Vertex vertex) const {
	bool result = vertex >= 0 && vertex <= this->vertex_count;
	#ifdef __VERTEXSET_CPP_DEBUG
	if (!result) {
		std::cerr << "Vertex supplied is out of bounds: lower: 0 upper: "
			<< this->vertex_count << " input : " << vertex << std::endl;
	}
	#endif
	return result;
}

bool VertexSet::is_vertex_sets_same_length(const VertexSet& vs1, const VertexSet& vs2) {
	bool result = vs1.vertex_count == vs2.vertex_count;
	#ifdef __VERTEXSET_CPP_DEBUG
	if (!result) {
		std::cerr << "Vertex sets supplied are of different lengths: vs1: "
			<< vs1.vertex_count << " vs2: " << vs2.vertex_count << std::endl;
	}
	#endif
	return result;
}

void VertexSet::resize(unsigned int vertex_count) {
	this->vertex_count = vertex_count;
	this->boolarray.resize(vertex_count);
}