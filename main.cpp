#include <iostream>
#include "data_structures/Graph.h"
#include "src/System.h"

int main() {


    System system;
    system.readAndParse();
    Graph<int> graph = system.getGraph();

    for (auto v : graph.getVertexSet()){
        cout << "Vertex: " << v->getInfo() << endl;
        for (auto edge : v->getAdj()){
            cout << "  Adjacent Vertex: " << edge->getDest()->getInfo() << ", Weight: " << edge->getWeight() << endl;
        }
    }

    cout << endl;

    cout << "backtracking: " << endl;



    system.backtrack(0);


    return 0;
}
