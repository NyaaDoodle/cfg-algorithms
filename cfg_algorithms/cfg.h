#pragma once
#include "graph.h"

class ControlFlowGraph : public Graph {
private:
	Vertex entry;
	void add_edges_from_input();
	unsigned int static get_vertex_count_from_input();
	Vertex static get_entry_vertex_from_input(unsigned int vertex_count);
public:
	ControlFlowGraph(unsigned int vertex_count, Vertex entry);
	Vertex get_entry() const;
	ControlFlowGraph static create_from_input();
};