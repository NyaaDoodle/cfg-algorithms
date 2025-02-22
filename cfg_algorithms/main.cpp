#include "algorithms.h"

int main() {
	ControlFlowGraph cfg = ControlFlowGraph::create_from_input();
	print_inverse_dominance_sets(cfg);
	print_immediate_dominators(cfg);
	print_dominator_tree(cfg);
	print_dominance_frontier_sets(cfg);
	print_back_edges(cfg);
	print_natural_loops(cfg);
	return 0;
}