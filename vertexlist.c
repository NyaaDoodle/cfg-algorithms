#include "vertexlist.h"
#include <stdio.h>
#include <stdlib.h>

void add_node_to_head(Vertex vertex_to_add, VertexLinkedList* list) {
    VertexLinkedNode* node_to_add = (VertexLinkedNode*) malloc(sizeof(VertexLinkedNode));
    node_to_add->vertex = vertex_to_add;
    node_to_add->next = list->head;
    list->head = node_to_add;
}

void delete_list(VertexLinkedList* list) {
    VertexLinkedNode* current_node = list->head;
    VertexLinkedNode* next_node = current_node;
    while (current_node != NULL) {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
}

void print_list(VertexLinkedList* list) {
    VertexLinkedNode* current_node = list->head;
    while (current_node != NULL) {
        printf("%u ", current_node->vertex);
        current_node = current_node->next;
    }
    printf("\n");
}
