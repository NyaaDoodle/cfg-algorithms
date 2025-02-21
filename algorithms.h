#pragma once
#include "cfg.h"
#include "vertexset.h"

typedef struct _Edge {
    Vertex source;
    Vertex destination;
} Edge;

VertexSet** get_domination_sets(ControlFlowGraph* cfg);
VertexSet** get_strict_domination_sets(ControlFlowGraph* cfg);
VertexSet** get_inverse_domination_sets(ControlFlowGraph* cfg);
int* get_immediate_domination_sets(ControlFlowGraph* cfg);
//Graph* get_dominator_tree(ControlFlowGraph* cfg);
//VertexSet** get_dominance_frontier_sets(ControlFlowGraph* cfg);
//Edge* get_back_edges(ControlFlowGraph* cfg);
//VertexLinkedList** get_natural_loop_sets(ControlFlowGraph* cfg);
// Drawing all the natural loops?
