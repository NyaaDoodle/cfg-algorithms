make: main.cpp graph.cpp vertexset.cpp cfg.cpp
	g++ main.cpp graph.cpp vertexset.cpp cfg.cpp -Wall -o cfg_algorithms

clean:
	rm cfg_algorithms
