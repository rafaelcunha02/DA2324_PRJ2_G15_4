#include <iostream>
#include "data_structures/Graph.h"
#include "src/System.h"

int main() {


    System system;
    system.readAndParse();
    Graph<int> graph = system.getGraph();



    Graph<int> *g = &graph;
    system.christofedes(0);
    cout << "done";
    system.triangularApproximation(0);

    return 0;
}
