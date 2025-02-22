#pragma once
#include "cfg.h"
#include "vertexset.h"
#include <vector>

struct Edge {
	Vertex source;
	Vertex destination;
};

void print_inverse_dominator_sets(const ControlFlowGraph& cfg);
void print_inverse_immediate_dominator_sets(const ControlFlowGraph& cfg);
void print_dominator_tree(const ControlFlowGraph& cfg);
void print_dominance_frontier_sets(const ControlFlowGraph& cfg);
void print_back_edges(const ControlFlowGraph& cfg);
void print_natural_loops(const ControlFlowGraph& cfg);

vector<VertexSet> get_dominator_sets(const ControlFlowGraph& cfg);
vector<VertexSet> get_strict_dominatior_sets(const ControlFlowGraph& cfg);
vector<VertexSet> get_inverse_dominator_sets(const ControlFlowGraph& cfg);
vector<VertexSet> get_inverse_immediate_dominator_sets(const ControlFlowGraph& cfg);
vector<Vertex> get_immediate_dominators(const ControlFlowGraph& cfg);
Graph get_dominator_tree(const ControlFlowGraph& cfg);
vector<VertexSet> get_dominance_frontier_sets(const ControlFlowGraph& cfg);
vector<Edge> get_back_edges(const ControlFlowGraph& cfg);
vector<Graph> get_natural_loops(const ControlFlowGraph& cfg);