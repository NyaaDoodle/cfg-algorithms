#include "algorithms.h"

vector<VertexSet> initialize_vertex_sets(unsigned int vertex_count);
vector<VertexSet> initialize_dom_sets(unsigned int vertex_count, Vertex entry);
VertexSet get_new_dom_set(Vertex n, const vector<VertexSet> dom_sets, const ControlFlowGraph& cfg);

void print_inverse_dominator_sets(const ControlFlowGraph& cfg) {

}

void print_immediate_dominators(const ControlFlowGraph& cfg) {

}

void print_dominator_tree(const ControlFlowGraph& cfg) {

}

void print_dominance_frontier_sets(const ControlFlowGraph& cfg) {

}

void print_back_edges(const ControlFlowGraph& cfg) {

}

void print_natural_loops(const ControlFlowGraph& cfg) {

}

vector<VertexSet> get_dominator_sets(const ControlFlowGraph& cfg) {
	unsigned int vertex_count = cfg.get_entry();
	Vertex entry = cfg.get_entry();
	vector<VertexSet> dom_sets = initialize_dom_sets(vertex_count, entry);
	bool changed = false;
	do {
		changed = false;
		for (Vertex n = 0; n < vertex_count; ++n) {
			VertexSet olddom = dom_sets[n];
			dom_sets[n] = get_new_dom_set(n, dom_sets, cfg);
			if (!VertexSet::is_vertex_sets_equal(olddom, dom_sets[n])) {
				changed = true;
			}
		}
	} while (changed == true);
	return dom_sets;
}

vector<VertexSet> get_strict_dominatior_sets(const ControlFlowGraph& cfg) {
	vector<VertexSet> sdom_sets = get_dominator_sets(cfg);
	for (Vertex i = 0; i < cfg.get_vertex_count(); ++i) {
		sdom_sets[i].unset_vertex(i);
	}
	return sdom_sets;
}

vector<VertexSet> get_inverse_dominator_sets(const ControlFlowGraph& cfg) {
	vector<VertexSet> dom_sets = get_dominator_sets(cfg);
	vector<VertexSet> invdom_sets = initialize_vertex_sets(cfg.get_vertex_count());
	for (Vertex i = 0; i < cfg.get_vertex_count(); ++i) {
		for (Vertex j = 0; j < cfg.get_vertex_count(); ++j) {
			if (dom_sets[i].is_vertex_set(j)) {
				invdom_sets[j].set_vertex(i);
			}
		}
	}
	return invdom_sets;
}

vector<VertexSet> get_immediate_dominator_sets(const ControlFlowGraph& cfg) {
	vector<VertexSet> dom_sets = get_dominator_sets(cfg);
	vector<VertexSet> sdom_sets = get_strict_dominatior_sets(cfg);
	unsigned int vertex_count = cfg.get_vertex_count();
	vector<VertexSet> idom_sets = initialize_vertex_sets(vertex_count);
	for (Vertex d = 0; d < vertex_count; ++d) {
		for (Vertex v = 0; v < vertex_count; ++v) {
			bool is_d_sdom_v = sdom_sets[v].is_vertex_set(d);
			if (is_d_sdom_v) {
				bool is_every_w_dom_d = true;
				for (Vertex w = 0; w < vertex_count; ++w) {
					if (sdom_sets[v].is_vertex_set(w)) {
						if (!dom_sets[d].is_vertex_set(w)) {
							is_every_w_dom_d = false;
							break;
						}
					}
				}
				if (is_every_w_dom_d) {
					idom_sets[d].set_vertex(v);
				}
			}
		}
	}
	return idom_sets;
}

Graph get_dominator_tree(const ControlFlowGraph& cfg) {
	vector<VertexSet> idom_sets = get_immediate_dominator_sets(cfg);
}

vector<VertexSet> get_dominance_frontier_sets(const ControlFlowGraph& cfg) {

}

vector<Edge> get_back_edges(const ControlFlowGraph& cfg) {

}

vector<Graph> get_natural_loops(const ControlFlowGraph& cfg) {

}

vector<VertexSet> initialize_dom_sets(unsigned int vertex_count, Vertex entry) {

}

vector<VertexSet> initialize_vertex_sets(unsigned int vertex_count) {
	// Create an array of vertex_count VertexSets, each one with length of vertex_count.
	return vector<VertexSet>(vertex_count, vertex_count);
}

vector<VertexSet> initialize_dom_sets(unsigned int vertex_count, Vertex entry) {
	vector<VertexSet> dom_sets = initialize_vertex_sets(vertex_count);
	dom_sets[entry].unset_all_vertices();
	dom_sets[entry].set_vertex(entry);
	for (Vertex v = 0; v < vertex_count; ++v) {
		if (v != entry) {
			// dom_set[v] = V
			dom_sets[v].set_all_vertices();
		}
	}
	return dom_sets;
}

VertexSet get_new_dom_set(Vertex n, const vector<VertexSet> dom_sets, const ControlFlowGraph& cfg) {
	VertexSet new_dom_set = VertexSet(cfg.get_vertex_count());
	new_dom_set.set_all_vertices();
	VertexSet prev_set = cfg.get_prev_set(n);
	for (Vertex i = 0; i < cfg.get_vertex_count(); ++i) {
		if (prev_set.is_vertex_set(i)) {
			new_dom_set = VertexSet::intersection_set(dom_sets[i], new_dom_set);
		}
	}
	new_dom_set.set_vertex(n);
	return new_dom_set;
}