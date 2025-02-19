#include "graph.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define __GRAPH_C_DEBUG

Graph* create_graph(size_t vertex_count) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    if (graph != NULL) {
        graph->vertex_count = vertex_count;
        graph->adjlists = (VertexLinkedList*) malloc(vertex_count*sizeof(VertexLinkedList));
        for (size_t i = 0; i < vertex_count; ++i) {
            graph->adjlists[i].head = NULL;
        }
    }
    else {
        perror("Graph creation failed");
        exit(errno);
    }
    return graph;
}

void insert_edge(Vertex source, Vertex destination, Graph* graph) {
    if (graph != NULL) {
        add_node_to_head(destination, &(graph->adjlists[source]));
    }
    #ifdef __GRAPH_C_DEBUG
    else {
        fprintf(stderr, "insert_edge(): Graph supplied was null.");
    }
    #endif
}

void add_node_to_head(Vertex vertex_to_add, VertexLinkedList* list) {
    VertexLinkedNode* node_to_add = (VertexLinkedNode*) malloc(sizeof(VertexLinkedNode));
    node_to_add->vertex = vertex_to_add;
    node_to_add->next = list->head;
    list->head = node_to_add;
}

void delete_graph(Graph* graph) {
    if (graph != NULL) {
        for (size_t i = 0; i < graph->vertex_count; ++i) {
            delete_list(&(graph->adjlists[i]));
        }
        free(graph->adjlists);
        free(graph);
    }
    #ifdef __GRAPH_C_DEBUG
    else {
        fprintf(stderr, "delete_graph(): Graph supplied was null.");
    }
    #endif
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

void print_graph(Graph* graph) {
    if (graph != NULL) {
        for (size_t i = 0; i < graph->vertex_count; ++i) {
            printf("%lu: ", i);
            print_list(&(graph->adjlists[i]));
        }
    }
    #ifdef __GRAPH_C_DEBUG
    else {
        fprintf(stderr, "print_graph(): Graph supplied was null.");
    }
    #endif
}

void print_list(VertexLinkedList* list) {
    VertexLinkedNode* current_node = list->head;
    while (current_node != NULL) {
        printf("%u ", current_node->vertex);
        current_node = current_node->next;
    }
    printf("\n");
}
