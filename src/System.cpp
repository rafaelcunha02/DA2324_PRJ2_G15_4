#include "System.h"
#include <string>
#include <iomanip>


using namespace std;


/**
 * @brief Default constructor
 */
System::System() = default;

void System::readAndParse() {

    ifstream file("../data/Toy-Graphs/shipping.csv");
    string line;

    getline(file, line);
    while (getline(file, line)){
        stringstream ss(line);
        string source, dest, capacidade;
        double capacity;

        getline(ss, source, ',');
        getline(ss, dest, ',');
        getline(ss, capacidade, ',');
        capacity = stod(capacidade);

        if(!graph.findVertex(stoi(source))){
            graph.addVertex(stoi(source));
        }
        if(!graph.findVertex(stoi(dest))){
            graph.addVertex(stoi(dest));
        }

        graph.addBidirectionalEdge(stoi(source),stoi(dest), capacity);
    }
}