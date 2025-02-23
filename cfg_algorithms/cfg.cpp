#include "cfg.h"
#include "extras.h"
#include <iostream>
#include <cstdlib>

ControlFlowGraph::ControlFlowGraph(unsigned int vertex_count, Vertex entry) : Graph(vertex_count) {
	this->entry = entry;
}

ControlFlowGraph ControlFlowGraph::create_from_input() {
	unsigned int vertex_count = get_vertex_count_from_input();
	Vertex entry = get_entry_vertex_from_input(vertex_count);
	ControlFlowGraph cfg = ControlFlowGraph(vertex_count, entry);
	cfg.add_edges_from_input();
	return cfg;
}

unsigned int ControlFlowGraph::get_vertex_count_from_input() {
	unsigned int vertex_count;
	clear_cin();
	std::cout << "Enter number of vertices in graph: ";
	std::cin >> vertex_count;
	return vertex_count;
}

Vertex ControlFlowGraph::get_entry_vertex_from_input(unsigned int vertex_count) {
	Vertex entry;
	bool is_input_in_range = false;
	while (!is_input_in_range) {
		clear_cin();
		std::cout << "Enter the entry vertex of the graph: ";
		std::cin >> entry;
		if (entry >= 0 && entry <= vertex_count) {
			is_input_in_range = true;
		}
		else {
			std::cout << "Invalid input. Enter a vertex number from 0 to" << vertex_count << std::endl;
		}
	}
	return entry;
}

void ControlFlowGraph::add_edges_from_input() {
	bool is_quit = false;
	while (!is_quit) {
		string temp;
		Vertex source;
		Vertex destination;
		clear_cin();
		std::cout << "Enter an edge to add, in the format: s d. Enter q to finish adding edges." << std::endl;
		std::cin >> temp;
		if (temp != "q") {
			source = atoi(temp.c_str());
			std::cin.ignore(1, ' ');
			std::cin >> destination;
			this->insert_edge(source, destination);
		}
		else {
			is_quit = true;
		}
	}
}

void ControlFlowGraph::print_inverse_dominator_sets() const {
	vector<VertexSet> invdom_sets = get_inverse_dominator_sets();
	std::cout << "DOM^-1:" << std::endl;
	for (Vertex i = 0; i < this->vertex_count; ++i) {
		std::cout << "invdom(" << i << "): ";
		invdom_sets[i].print();
	}
	std::cout << std::endl;
}

void ControlFlowGraph::print_inverse_immediate_dominator_sets() const {
	vector<VertexSet> inv_idom_sets = get_inverse_immediate_dominator_sets();
	std::cout << "IDOM:" << std::endl;
	for (Vertex i = 0; i < this->vertex_count; ++i) {
		std::cout << "inv_idom(" << i << "): ";
		inv_idom_sets[i].print();
	}
	std::cout << std::endl;
}

void ControlFlowGraph::print_dominator_tree() const {
	Graph dominator_tree = get_dominator_tree();
	std::cout << "Dominator Tree:" << std::endl;
	dominator_tree.print();
	std::cout << std::endl;
}

void ControlFlowGraph::print_dominance_frontier_sets() const {
	vector<VertexSet> df_sets = get_dominance_frontier_sets();
	std::cout << "Dominance Frontier Sets:" << std::endl;
	for (Vertex i = 0; i < this->vertex_count; ++i) {
		std::cout << "df(" << i << "): ";
		df_sets[i].print();
	}
	std::cout << std::endl;
}

void ControlFlowGraph::print_back_edges() const {
	vector<Edge> back_edges = get_back_edges();
	std::cout << "Back edges:" << std::endl;
	for (Edge back_edge : back_edges) {
		std::cout << back_edge.source << ' ' << back_edge.destination << std::endl;
	}
	std::cout << std::endl;
}

void ControlFlowGraph::print_natural_loops() const {
	vector<Graph> natural_loop_subgraphs = get_natural_loops();
	std::cout << "Natural Loop Subgraphs:" << std::endl;
	for (unsigned int i = 0; i < natural_loop_subgraphs.size(); ++i) {
		std::cout << "Natural Loop " << (i + 1) << std::endl;
		natural_loop_subgraphs[i].print();
		std::cout << std::endl;
	}
}

vector<VertexSet> ControlFlowGraph::get_dominator_sets() const {
	vector<VertexSet> dom_sets = initialize_dom_sets(this->entry);
	bool changed = false;
	do {
		changed = false;
		for (Vertex n = 0; n < this->vertex_count; ++n) {
			VertexSet olddom = dom_sets[n];
			dom_sets[n] = this->get_new_dom_set(n, dom_sets);
			if (!VertexSet::is_vertex_sets_equal(olddom, dom_sets[n])) {
				changed = true;
			}
		}
	} while (changed == true);
	return dom_sets;
}

vector<VertexSet> ControlFlowGraph::get_strict_dominatior_sets() const {
	vector<VertexSet> sdom_sets = this->get_dominator_sets();
	for (Vertex i = 0; i < this->vertex_count; ++i) {
		sdom_sets[i].unset_vertex(i);
	}
	return sdom_sets;
}

vector<VertexSet> ControlFlowGraph::get_inverse_dominator_sets() const {
	vector<VertexSet> dom_sets = this->get_dominator_sets();
	vector<VertexSet> invdom_sets = this->initialize_vertex_sets();
	for (Vertex i = 0; i < this->vertex_count; ++i) {
		for (Vertex j = 0; j < this->vertex_count; ++j) {
			if (dom_sets[i].is_vertex_set(j)) {
				invdom_sets[j].set_vertex(i);
			}
		}
	}
	return invdom_sets;
}

vector<VertexSet> ControlFlowGraph::get_inverse_immediate_dominator_sets() const {
	vector<VertexSet> dom_sets = this->get_dominator_sets();
	vector<VertexSet> sdom_sets = this->get_strict_dominatior_sets();
	vector<VertexSet> inv_idom_sets = this->initialize_vertex_sets();
	for (Vertex d = 0; d < this->vertex_count; ++d) {
		for (Vertex v = 0; v < this->vertex_count; ++v) {
			bool is_d_sdom_v = sdom_sets[v].is_vertex_set(d);
			if (is_d_sdom_v) {
				bool is_every_w_dom_d = true;
				for (Vertex w = 0; w < this->vertex_count; ++w) {
					if (sdom_sets[v].is_vertex_set(w)) {
						if (!dom_sets[d].is_vertex_set(w)) {
							is_every_w_dom_d = false;
							break;
						}
					}
				}
				if (is_every_w_dom_d) {
					inv_idom_sets[d].set_vertex(v);
				}
			}
		}
	}
	return inv_idom_sets;
}

vector<Vertex> ControlFlowGraph::get_immediate_dominators() const {
	vector<VertexSet> inv_idom_sets = this->get_inverse_immediate_dominator_sets();
	unsigned int no_vertex_value = this->vertex_count + 1;
	vector<Vertex> idoms = vector<Vertex>(this->vertex_count, no_vertex_value);
	for (Vertex i = 0; i < this->vertex_count; ++i) {
		for (Vertex j = 0; j < this->vertex_count; ++j) {
			if (inv_idom_sets[i].is_vertex_set(j)) {
				idoms[j] = i;
			}
		}
	}
	return idoms;
}

Graph ControlFlowGraph::get_dominator_tree() const {
	vector<VertexSet> idom_sets = this->get_inverse_immediate_dominator_sets();
	Graph dominator_tree = Graph(this->vertex_count);
	for (Vertex i = 0; i < this->vertex_count; ++i) {
		for (Vertex j = 0; j < this->vertex_count; ++j) {
			if (idom_sets[i].is_vertex_set(j)) {
				dominator_tree.insert_edge(i, j);
			}
		}
	}
	return dominator_tree;
}

vector<VertexSet> ControlFlowGraph::get_dominance_frontier_sets() const {
	vector<Vertex> idoms = this->get_immediate_dominators();
	vector<VertexSet> df_sets = this->initialize_vertex_sets();
	for (Vertex v = 0; v < this->vertex_count; ++v) {
		VertexSet prev_set = this->get_prev_set(v);
		if (prev_set.count_set_vertices() >= 2) {
			for (Vertex p = 0; p < this->vertex_count; ++p) {
				if (prev_set.is_vertex_set(p)) {
					Vertex runner = p;
					while (runner != idoms[v]) {
						df_sets[runner].set_vertex(v);
						runner = idoms[runner];
					}
				}
			}
		}
	}
	return df_sets;
}

vector<Edge> ControlFlowGraph::get_back_edges() const {
	vector<VertexSet> dom_sets = this->get_dominator_sets();
	vector<Edge> back_edges;
	for (Vertex s = 0; s < this->vertex_count; ++s) {
		for (Vertex d : this->adjlists[s]) {
			if (dom_sets[s].is_vertex_set(d)) {
				Edge back_edge_to_add;
				back_edge_to_add.source = s;
				back_edge_to_add.destination = d;
				back_edges.push_back(back_edge_to_add);
			}
		}
	}
	return back_edges;
}

vector<Graph> ControlFlowGraph::get_natural_loops() const {
	vector<Edge> back_edges = get_back_edges();
	vector<Graph> natural_loops;
	for (Edge back_edge : back_edges) {
		Graph natural_loop_to_add = this->find_natural_loop(back_edge);
		natural_loops.push_back(natural_loop_to_add);
	}
	return natural_loops;
}

vector<VertexSet> ControlFlowGraph::initialize_vertex_sets() const {
	// Create an array of vertex_count VertexSets, each one with length of vertex_count.
	return vector<VertexSet>(this->vertex_count, this->vertex_count);
}

vector<VertexSet> ControlFlowGraph::initialize_dom_sets(Vertex entry) const {
	vector<VertexSet> dom_sets = this->initialize_vertex_sets();
	dom_sets[entry].unset_all_vertices();
	dom_sets[entry].set_vertex(entry);
	for (Vertex v = 0; v < this->vertex_count; ++v) {
		if (v != entry) {
			// dom_set[v] = V
			dom_sets[v].set_all_vertices();
		}
	}
	return dom_sets;
}

VertexSet ControlFlowGraph::get_new_dom_set(Vertex n, const vector<VertexSet> dom_sets) const {
	VertexSet new_dom_set = VertexSet(this->vertex_count);
	new_dom_set.set_all_vertices();
	VertexSet prev_set = this->get_prev_set(n);
	for (Vertex i = 0; i < this->vertex_count; ++i) {
		if (prev_set.is_vertex_set(i)) {
			new_dom_set = VertexSet::intersection_set(dom_sets[i], new_dom_set);
		}
	}
	new_dom_set.set_vertex(n);
	return new_dom_set;
}

Graph ControlFlowGraph::find_natural_loop(Edge back_edge) const {
	// Based off the natural loop construction algorithm in page 604 (Fig. 10.15.) of Compilers: Principles, Techniques and Tools.
	stack<Vertex> vertices_stack;
	VertexSet loop = VertexSet(this->vertex_count);
	Vertex n = back_edge.source;
	Vertex d = back_edge.destination;
	natural_loop_insert(n, loop, vertices_stack);
	while (!vertices_stack.empty()) {
		Vertex m = vertices_stack.top();
		vertices_stack.pop();
		VertexSet prev_set = this->get_prev_set(m);
		for (Vertex p = 0; p < this->vertex_count; ++p) {
			if (prev_set.is_vertex_set(p)) {
				natural_loop_insert(p, loop, vertices_stack);
			}
		}
	}
	Graph natural_loop_graph = this->construct_subgraph_from_vertex_set(loop);
	return natural_loop_graph;
}

void ControlFlowGraph::natural_loop_insert(Vertex m, VertexSet& loop, stack<Vertex>& vertices_stack) {
	// Based off the insert procedure in page 604 (Fig. 10.15.) of Compilers: Principles, Techniques and Tools.
	if (loop.is_vertex_unset(m)) {
		loop.set_vertex(m);
		vertices_stack.push(m);
	}
}