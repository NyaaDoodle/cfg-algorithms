#include "vertexlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>

#define __VERTEXLIST_C_DEBUG

bool is_list_not_null(VertexLinkedList* list);

void add_node_to_head(Vertex vertex_to_add, VertexLinkedList* list) {
    VertexLinkedNode* node_to_add = (VertexLinkedNode*) malloc(sizeof(VertexLinkedNode));
    if (node_to_add != NULL) {
        node_to_add->vertex = vertex_to_add;
        node_to_add->next = list->head;
        list->head = node_to_add;
    }
    else {
        perror("Linked node creation failed");
        exit(errno);
    }
}

bool search_node(Vertex query_vertex, VertexLinkedList* list) {
    if (is_list_not_null(list)) {
        VertexLinkedNode* current_node = list->head;
        while (current_node != NULL) {
            if (current_node->vertex == query_vertex) {
                return true;
            }
            current_node = current_node->next;
        }
    }
    return false;
}

void delete_list(VertexLinkedList* list) {
    if (is_list_not_null(list)) {
        VertexLinkedNode* current_node = list->head;
        VertexLinkedNode* next_node = current_node;
        while (current_node != NULL) {
            next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }
    }
}

void print_list(VertexLinkedList* list) {
    if (is_list_not_null(list)) {
        VertexLinkedNode* current_node = list->head;
        while (current_node != NULL) {
            printf("%u ", current_node->vertex);
            current_node = current_node->next;
        }
        printf("\n");
    }
}

bool is_list_not_null(VertexLinkedList* list) {
    bool result = list != NULL;
    #ifdef __VERTEXLIST_C_DEBUG
    if (!result) {
        fprintf(stderr, "Supplied linked list was null.\n");
    }
    #endif
    return result;
}
