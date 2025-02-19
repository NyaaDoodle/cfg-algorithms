#pragma once
#include <stddef.h>

typedef unsigned int Vertex;

typedef struct _VertexLinkedNode {
    Vertex vertex;
    struct _VertexLinkedNode* next;
} VertexLinkedNode;

typedef struct _VertexLinkedList {
    VertexLinkedNode* head;
} VertexLinkedList;

typedef struct _Graph {
    size_t vertex_count;
    VertexLinkedList* adjlists;
} Graph;

Graph* create_graph(size_t vertex_count);
void insert_edge(Vertex source_vertex, Vertex destination_vertex, Graph* graph);
void add_node_to_head(Vertex vertex_to_add, VertexLinkedList* list);
void delete_graph(Graph* graph);
void delete_list(VertexLinkedList* list);
void print_graph(Graph* graph);
void print_list(VertexLinkedList* list);
