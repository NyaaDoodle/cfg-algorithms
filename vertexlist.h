#pragma once
#include "vertex.h"
#include <stdbool.h>

typedef struct _VertexLinkedNode {
    Vertex vertex;
    struct _VertexLinkedNode* next;
} VertexLinkedNode;

typedef struct _VertexLinkedList {
    VertexLinkedNode* head;
} VertexLinkedList;

void add_node_to_head(Vertex vertex_to_add, VertexLinkedList* list);
bool search_node(Vertex query_vertex, VertexLinkedList* list);
void delete_list(VertexLinkedList* list);
void print_list(VertexLinkedList* list);
