#include "algorithms.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

VertexSet** initialize_vertex_sets(ControlFlowGraph* cfg);
void delete_vertex_sets(VertexSet** vertex_sets, size_t vertex_count);
bool is_cfg_not_null(ControlFlowGraph* cfg);
void set_entry_dom_set(Vertex entry, VertexSet* entry_dom_set);
VertexSet* get_new_dom_set(Vertex n, VertexSet** dom_sets, ControlFlowGraph* cfg);
VertexSet* get_prev_set(Vertex vertex, ControlFlowGraph* cfg);
int* initialize_idom_array(size_t vertex_count);

VertexSet** get_domination_sets(ControlFlowGraph* cfg) {
    VertexSet** dom_sets = initialize_vertex_sets(cfg);
    Vertex entry = cfg->entry;
    set_entry_dom_set(entry, dom_sets[entry]);
    for (Vertex v = 0; v < cfg->vertex_count; ++v) {
        if (v != entry) {
            set_all_vertices(dom_sets[v]);
        }
    }
    bool changed = false;
    do {
        changed = false;
        for (Vertex n = 0; n < cfg->vertex_count && n != entry; ++n) {
            if (n != entry) {
                VertexSet* old_dom = dom_sets[n];
                VertexSet* new_dom = get_new_dom_set(n, dom_sets, cfg);
                if (!is_vertex_sets_equal(old_dom, new_dom)) {
                    changed = true;
                }
            }
        }
    } while (changed == true);
    return dom_sets;
}

VertexSet** get_strict_domination_sets(ControlFlowGraph* cfg) {
    VertexSet** sdom_sets = get_domination_sets(cfg);
    for (Vertex i = 0; i < cfg->vertex_count; ++i) {
        unset_vertex(i, sdom_sets[i]);
    }
    return sdom_sets;
}

VertexSet** get_inverse_domination_sets(ControlFlowGraph* cfg) {
    VertexSet** dom_sets = get_domination_sets(cfg);
    VertexSet** invdom_sets = initialize_vertex_sets(cfg);
    for (Vertex i = 0; i < cfg->vertex_count; ++i) {
        for (Vertex j = 0; j < cfg->vertex_count; ++j) {
            if (is_vertex_set(j, dom_sets[i])) {
                set_vertex(i, invdom_sets[j]);
            }
        }
    }
    delete_vertex_sets(dom_sets, cfg->vertex_count);
    return invdom_sets;
}

int* get_immediate_domination_sets(ControlFlowGraph* cfg) {
    VertexSet** dom_sets = get_domination_sets(cfg);
    VertexSet** sdom_sets = get_strict_domination_sets(cfg);
    int* idoms = initialize_idom_array(cfg->vertex_count);
    for (Vertex v = 0; v < cfg->vertex_count; ++v) {
        for (Vertex d = 0; d < cfg->vertex_count; ++d) {
            bool is_d_sdom_v = is_vertex_set(d, sdom_sets[v]);
            if (is_d_sdom_v) {
                bool is_idom = true;
                for (Vertex w = 0; w < cfg->vertex_count; ++w) {
                    if (is_vertex_set(w, sdom_sets[v])) {
                        if (!is_vertex_set(w, dom_sets[d])) {
                            is_idom = false;
                            break;
                        }
                    }
                }
                if (is_idom) {
                    idoms[v] = d;
                    break;
                }
            }
        }
    }
    return idoms;
}

//Graph* get_dominator_tree(ControlFlowGraph* cfg);
//VertexLinkedList** get_dominance_frontier_sets(ControlFlowGraph* cfg);
//Edge* get_back_edges(ControlFlowGraph* cfg);
//VertexLinkedList** get_natural_loop_sets(ControlFlowGraph* cfg);

VertexSet** initialize_vertex_sets(ControlFlowGraph* cfg) {
    VertexSet** vertex_sets = NULL;
    if (is_cfg_not_null(cfg)) {
        size_t vertex_count = cfg->vertex_count;
        vertex_sets = (VertexSet**) malloc(vertex_count*sizeof(VertexSet*));
        if (vertex_sets != NULL) {
            for (size_t i = 0; i < vertex_count; ++i) {
                vertex_sets[i] = create_vertex_set(vertex_count);
            }
        }
        else {
            perror("Vertex sets creation failed");
            exit(errno);
        }
    }
    return vertex_sets;
}

void delete_vertex_sets(VertexSet** vertex_sets, size_t vertex_count) {
    if (vertex_sets != NULL) {
        for (size_t i = 0; i < vertex_count; ++i) {
            delete_vertex_set(vertex_sets[i]);
        }
        free(vertex_sets);
    }
}

void set_entry_dom_set(Vertex entry, VertexSet* entry_dom_set) {
    unset_all_vertices(entry_dom_set);
    set_vertex(entry, entry_dom_set);
}

VertexSet* get_new_dom_set(Vertex n, VertexSet** dom_sets, ControlFlowGraph* cfg) {
    VertexSet* new_dom_set = create_vertex_set(cfg->vertex_count);
    set_all_vertices(new_dom_set);
    VertexSet* prev_set = get_prev_set(n, cfg);
    for (Vertex i = 0; i < cfg->vertex_count; ++i) {
        if (is_vertex_set(i, prev_set)) {
            VertexSet* delete_set = new_dom_set;
            new_dom_set = intersection_set(dom_sets[i], new_dom_set);
            delete_vertex_set(delete_set);
            set_vertex(n, new_dom_set);
        }
    }
    return new_dom_set;
}

VertexSet* get_prev_set(Vertex vertex, ControlFlowGraph* cfg) {
    VertexSet* prev_set = create_vertex_set(cfg->vertex_count);
    for (Vertex i = 0; i < cfg->vertex_count; ++i) {
        if (search_node(vertex, &(cfg->adjlists[i]))) {
            set_vertex(i, prev_set);
        }
    }
    return prev_set;
}

int* initialize_idom_array(size_t vertex_count) {
    int* idoms = (int*) malloc(vertex_count*sizeof(int));
    if (idoms != NULL) {
        for (size_t i = 0; i < vertex_count; ++i) {
            idoms[i] = -1;
        }
    }
    else {
        perror("Immediate dominators array creation failed");
        exit(errno);
    }
    return idoms;
}
