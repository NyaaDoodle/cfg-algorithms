#pragma once
#include "vertex.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct _VertexSet {
    size_t vertex_count;
    bool* vector;
} VertexSet;

VertexSet* create_vertex_set(size_t vertex_count);
void delete_vertex_set(VertexSet* vs);
void set_vertex(Vertex vertex_to_set, VertexSet* vs);
void unset_vertex(Vertex vertex_to_unset, VertexSet* vs);
void set_all_vertices(VertexSet* vs);
void unset_all_vertices(VertexSet* vs);
bool is_vertex_set(Vertex query_vertex, VertexSet* vs);
bool is_vertex_unset(Vertex query_vertex, VertexSet* vs);
VertexSet* union_set(VertexSet* vs1, VertexSet* vs2);
VertexSet* intersection_set(VertexSet* vs1, VertexSet* vs2);
bool is_vertex_sets_equal(VertexSet* vs1, VertexSet* vs2);
void print_set(VertexSet* vs);
