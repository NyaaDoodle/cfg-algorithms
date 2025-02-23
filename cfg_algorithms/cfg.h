#pragma once
#include "graph.h"
#include <stack>

struct Edge {
	Vertex source;
	Vertex destination;
};

class ControlFlowGraph : public Graph {
private:
	Vertex entry;
	void add_edges_from_input();
	unsigned int static get_vertex_count_from_input();
	Vertex static get_entry_vertex_from_input(unsigned int vertex_count);
	vector<VertexSet> initialize_vertex_sets() const;
	vector<VertexSet> initialize_dom_sets(Vertex entry) const;
	VertexSet get_new_dom_set(Vertex n, const vector<VertexSet> dom_sets) const;
	Graph find_natural_loop(Edge back_edge) const;
	void static natural_loop_insert(Vertex m, VertexSet& loop, stack<Vertex>& vertices_stack);
public:
	ControlFlowGraph(unsigned int vertex_count, Vertex entry);
	ControlFlowGraph static create_from_input();

	void print_inverse_dominator_sets() const;
	void print_inverse_immediate_dominator_sets() const;
	void print_dominator_tree() const;
	void print_dominance_frontier_sets() const;
	void print_back_edges() const;
	void print_natural_loops() const;

	vector<VertexSet> get_dominator_sets() const;
	vector<VertexSet> get_strict_dominatior_sets() const;
	vector<VertexSet> get_inverse_dominator_sets() const;
	vector<VertexSet> get_inverse_immediate_dominator_sets() const;
	vector<Vertex> get_immediate_dominators() const;
	Graph get_dominator_tree() const;
	vector<VertexSet> get_dominance_frontier_sets() const;
	vector<Edge> get_back_edges() const;
	vector<Graph> get_natural_loops() const;
};