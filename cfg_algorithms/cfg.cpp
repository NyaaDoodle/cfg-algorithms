#include "cfg.h"
#include "extras.h"
#include <iostream>
#include <cstdlib>

ControlFlowGraph::ControlFlowGraph(unsigned int vertex_count, Vertex entry) : Graph(vertex_count) {
	this->entry = entry;
}

Vertex ControlFlowGraph::get_entry() const {
	return this->entry;
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