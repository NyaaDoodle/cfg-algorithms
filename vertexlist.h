#pragma once
#include <stdbool.h>

typedef unsigned int Vertex;

typedef struct _VertexLinkedNode {
    Vertex vertex;
    struct _VertexLinkedNode* next;
} VertexLinkedNode;

typedef struct _VertexLinkedList {
    VertexLinkedNode* head;
} VertexLinkedList;

void add_node_to_head(Vertex vertex_to_add, VertexLinkedList* list);
bool is_node_exists(Vertex query_vertex, VertexLinkedList* list);
void remove_node(Vertex vertex_to_delete, VertexLinkedList* list);
void delete_list(VertexLinkedList* list);
void print_list(VertexLinkedList* list);
void union_lists(VertexLinkedList* list1, VertexLinkedList* list2);
void intersect_lists(VertexLinkedList* list1, VertexLinkedList* list2);
