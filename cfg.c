#include "cfg.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define __CFG_C_DEBUG

ControlFlowGraph* create_cfg(size_t vertex_count, Vertex entry) {
    ControlFlowGraph* cfg = (ControlFlowGraph*) malloc(sizeof(ControlFlowGraph));
    if (cfg != NULL) {
        cfg->vertex_count = vertex_count;
        cfg->entry = entry;
        cfg->adjlists = (VertexLinkedList*) malloc(vertex_count*sizeof(VertexLinkedList));
        for (size_t i = 0; i < vertex_count; ++i) {
            cfg->adjlists[i].head = NULL;
        }
    }
    else {
        perror("Control flow graph creation failed");
        exit(errno);
    }
    return cfg;
}

void insert_edge(Vertex source, Vertex destination, ControlFlowGraph* cfg) {
    if (cfg != NULL) {
        if (source >= 0 && destination <= cfg->vertex_count) {
            add_node_to_head(destination, &(cfg->adjlists[source]));
        }
        #ifdef __CFG_C_DEBUG
        else {
            fprintf(stderr, "insert_edge(): Supplied vertices out of bounds: s:%u d:%u v:%lu\n", source, destination, cfg->vertex_count);
        }
        #endif
    }
    #ifdef __CFG_C_DEBUG
    else {
        fprintf(stderr, "insert_edge(): CFG supplied was null.\n");
    }
    #endif
}

void delete_cfg(ControlFlowGraph* cfg) {
    if (cfg != NULL) {
        for (size_t i = 0; i < cfg->vertex_count; ++i) {
            delete_list(&(cfg->adjlists[i]));
        }
        free(cfg->adjlists);
        free(cfg);
    }
    #ifdef __CFG_C_DEBUG
    else {
        fprintf(stderr, "delete_cfg(): CFG supplied was null.\n");
    }
    #endif
}

void print_cfg(ControlFlowGraph* cfg) {
    if (cfg != NULL) {
        for (size_t i = 0; i < cfg->vertex_count; ++i) {
            printf("%lu: ", i);
            print_list(&(cfg->adjlists[i]));
        }
    }
    #ifdef __CFG_C_DEBUG
    else {
        fprintf(stderr, "print_cfg(): CFG supplied was null.\n");
    }
    #endif
}
