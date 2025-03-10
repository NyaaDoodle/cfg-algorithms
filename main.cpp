#include "cfg.h"

int main() {
	ControlFlowGraph cfg = ControlFlowGraph::create_from_input();
	cfg.print_inverse_dominator_sets();
	cfg.print_inverse_immediate_dominator_sets();
	cfg.print_dominator_tree();
	cfg.print_dominance_frontier_sets();
	cfg.print_back_edges();
	cfg.print_natural_loops();
	return 0;
}