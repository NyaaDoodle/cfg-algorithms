#include "cfg.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define __CFG_C_DEBUG

bool is_vertices_in_bounds(Vertex source, Vertex destination, ControlFlowGraph* cfg);

ControlFlowGraph* create_cfg(size_t vertex_count, Vertex entry) {
    ControlFlowGraph* cfg = (ControlFlowGraph*) malloc(sizeof(ControlFlowGraph));
    if (cfg != NULL) {
        cfg->vertex_count = vertex_count;
        cfg->entry = entry;
        cfg->adjlists = (VertexLinkedList*) malloc(vertex_count*sizeof(VertexLinkedList));
        if (cfg->adjlists != NULL) {
            for (size_t i = 0; i < vertex_count; ++i) {
                cfg->adjlists[i].head = NULL;
            }
        }
        else {
            perror("Array of linked lists creation failed");
            exit(errno);
        }
    }
    else {
        perror("Control flow graph creation failed");
        exit(errno);
    }
    return cfg;
}

void insert_edge(Vertex source, Vertex destination, ControlFlowGraph* cfg) {
    if (is_cfg_not_null(cfg) && is_vertices_in_bounds(source, destination, cfg)) {
        add_node_to_head(destination, &(cfg->adjlists[source]));
    }
}

void delete_cfg(ControlFlowGraph* cfg) {
    if (is_cfg_not_null(cfg)) {
        for (size_t i = 0; i < cfg->vertex_count; ++i) {
            delete_list(&(cfg->adjlists[i]));
        }
        free(cfg->adjlists);
        free(cfg);
    }
}

void print_cfg(ControlFlowGraph* cfg) {
    if (is_cfg_not_null(cfg)) {
        for (size_t i = 0; i < cfg->vertex_count; ++i) {
            printf("%lu: ", i);
            print_list(&(cfg->adjlists[i]));
        }
    }
}

bool is_cfg_not_null(ControlFlowGraph* cfg) {
    bool result = cfg != NULL;
    #ifdef __CFG_C_DEBUG
    if (!result) {
        fprintf(stderr, "CFG supplied was null.\n");
    }
    #endif
    return result;
}

bool is_vertices_in_bounds(Vertex source, Vertex destination, ControlFlowGraph* cfg) {
    // Assuming cfg is not null.
    bool source_result = source >= 0 && source <= cfg->vertex_count;
    bool destination_result = destination >= 0 && destination <= cfg->vertex_count;
    bool result = source_result && destination_result;
    #ifdef __CFG_C_DEBUG
    if (!result) {
        fprintf(stderr, "insert_edge(): Supplied vertices out of bounds: s:%u d:%u v:%lu\n", source, destination, cfg->vertex_count);
    }
    #endif
    return result;
}
