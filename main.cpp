#include <iostream>
#include "data_structures/Graph.h"
#include "src/System.h"

int main() {


    System system;
    system.readAndParse();
    Graph<int> graph = system.getGraph();



    Graph<int> *g = &graph;
    system.backtrack(0);
    system.prim(g);


    return 0;
}
