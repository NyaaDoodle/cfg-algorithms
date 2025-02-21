#pragma once
#include "vertexlist.h"
#include <stddef.h>

typedef struct _ControlFlowGraph {
    size_t vertex_count;
    Vertex entry;
    VertexLinkedList* adjlists;
} ControlFlowGraph;

ControlFlowGraph* create_cfg(size_t vertex_count, Vertex entry);
void insert_edge(Vertex source, Vertex destination, ControlFlowGraph* cfg);
void delete_cfg(ControlFlowGraph* cfg);
void print_cfg(ControlFlowGraph* cfg);
bool is_cfg_not_null(ControlFlowGraph* cfg);
