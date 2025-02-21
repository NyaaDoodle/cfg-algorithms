#include "vertexset.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define __VERTEXSET_C_DEBUG

bool is_vertex_set_not_null(VertexSet* vs);
bool is_vertex_in_bounds(Vertex vertex, VertexSet* vs);
bool is_vertex_sets_same_length(VertexSet* vs1, VertexSet* vs2);

VertexSet* create_vertex_set(size_t vertex_count) {
    VertexSet* vs = (VertexSet*) malloc(sizeof(VertexSet));
    if (vs != NULL) {
        vs->vertex_count = vertex_count;
        vs->vector = (bool*) malloc(vertex_count*sizeof(bool));
        if (vs->vector != NULL) {
            unset_all_vertices(vs);
        }
        else {
            perror("Vector of vertex set creation failed");
            exit(errno);
        }
    }
    else {
        perror("Vertex set creation failed");
        exit(errno);
    }
    return vs;
}

void delete_vertex_set(VertexSet* vs) {
    if (is_vertex_set_not_null(vs)) {
        free(vs->vector);
        free(vs);
    }
}

void set_vertex(Vertex vertex_to_set, VertexSet* vs) {
    if (is_vertex_set_not_null(vs) && is_vertex_in_bounds(vertex_to_set, vs)) {
        vs->vector[vertex_to_set] = true;
    }
}

void unset_vertex(Vertex vertex_to_unset, VertexSet* vs) {
    if (is_vertex_set_not_null(vs) && is_vertex_in_bounds(vertex_to_unset, vs)) {
        vs->vector[vertex_to_unset] = false;
    }
}

void set_all_vertices(VertexSet* vs) {
    if (is_vertex_set_not_null(vs)) {
        for (size_t i = 0; i < vs->vertex_count; ++i) {
            set_vertex(i, vs);
        }
    }
}

void unset_all_vertices(VertexSet* vs) {
    if (is_vertex_set_not_null(vs)) {
        for (size_t i = 0; i < vs->vertex_count; ++i) {
            unset_vertex(i, vs);
        }
    }
}

bool is_vertex_set(Vertex query_vertex, VertexSet* vs) {
    if (is_vertex_set_not_null(vs) && is_vertex_in_bounds(query_vertex, vs)) {
        return vs->vector[query_vertex];
    }
    else {
        return false;
    }
}

bool is_vertex_unset(Vertex query_vertex, VertexSet* vs) {
    if (is_vertex_set_not_null(vs) && is_vertex_in_bounds(query_vertex, vs)) {
        return !(vs->vector[query_vertex]);
    }
    else {
        return false;
    }
}

VertexSet* union_set(VertexSet* vs1, VertexSet* vs2) {
    VertexSet* unionset = NULL;
    if (is_vertex_set_not_null(vs1) && is_vertex_set_not_null(vs2)) {
        if (is_vertex_sets_same_length(vs1, vs2)) {
            size_t vertex_count = vs1->vertex_count;
            unionset = create_vertex_set(vertex_count);
            for (size_t i = 0; i < vertex_count; ++i) {
                if (is_vertex_set(i, vs1) || is_vertex_set(i, vs2)) {
                    set_vertex(i, unionset);
                }
            }
        }
    }
    #ifdef __VERTEXSET_C_DEBUG
    if (unionset == NULL) {
        fprintf(stderr, "Union set failed to be created");
    }
    #endif
    return unionset;
}

VertexSet* intersection_set(VertexSet* vs1, VertexSet* vs2) {
    VertexSet* intersectset = NULL;
    if (is_vertex_set_not_null(vs1) && is_vertex_set_not_null(vs2)) {
        if (is_vertex_sets_same_length(vs1, vs2)) {
            size_t vertex_count = vs1->vertex_count;
            intersectset = create_vertex_set(vertex_count);
            for (size_t i = 0; i < vertex_count; ++i) {
                if (is_vertex_set(i, vs1) && is_vertex_set(i, vs2)) {
                    set_vertex(i, intersectset);
                }
            }
        }
    }
    #ifdef __VERTEXSET_C_DEBUG
    if (intersectset == NULL) {
        fprintf(stderr, "Intersection set failed to be created");
    }
    #endif
    return intersectset;
}

bool is_vertex_sets_equal(VertexSet* vs1, VertexSet* vs2) {
    if (is_vertex_set_not_null(vs1) && is_vertex_set_not_null(vs2)) {
        if (is_vertex_sets_same_length(vs1, vs2)) {
            size_t vertex_count = vs1->vertex_count;
            for (size_t i = 0; i < vertex_count; ++i) {
                if (!(is_vertex_set(i, vs1) && is_vertex_set(i, vs2))) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

void print_set(VertexSet* vs) {
    if (is_vertex_set_not_null(vs)) {
        printf("{");
        for (size_t i = 0; i < vs->vertex_count; ++i) {
            if (is_vertex_set(i, vs)) {
                printf("%lu ", i);
            }
        }
        printf("\b}\n");
    }
}

bool is_vertex_set_not_null(VertexSet* vs) {
    bool result = vs != NULL && vs->vector != NULL;
    #ifdef __VERTEXSET_C_DEBUG
    if (!result) {
        fprintf(stderr, "Vertex set supplied was null.\n");
    }
    #endif
    return result;
}

bool is_vertex_in_bounds(Vertex vertex, VertexSet* vs) {
    // Assuming vs is not null.
    bool result = vertex >= 0 && vertex <= vs->vertex_count;
    #ifdef __VERTEXSET_C_DEBUG
    if (!result) {
        fprintf(stderr, "Vertex supplied is out of bounds: lower: %u upper: %lu input: %u\n", 0, vs->vertex_count, vertex);
    }
    #endif
    return result;
}

bool is_vertex_sets_same_length(VertexSet* vs1, VertexSet* vs2) {
    // Assuming vs1 and vs2 are not null.
    bool result = vs1->vertex_count == vs2->vertex_count;
    #ifdef __VERTEXSET_C_DEBUG
    if (!result) {
        fprintf(stderr, "Vertex sets supplied are of different lengths: vs1: %lu vs2: %lu\n", vs1->vertex_count, vs2->vertex_count);
    }
    #endif
    return result;
}
