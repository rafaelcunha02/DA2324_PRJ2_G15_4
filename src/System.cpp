#include "System.h"
#include <string>
#include <iomanip>


using namespace std;


/**
 * @brief Default constructor
 */
System::System() : graph() {}
void System::readAndParse() {

    ifstream file("../data/Toy-Graphs/stadiums.csv");
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


double System::pathWeight(const vector<int>& path) {
    double weight = 0;

    for (size_t i = 0; i < path.size() - 1; i++) {
        auto v1 = graph.findVertex(path[i]);
        auto v2 = graph.findVertex(path[i+1]);
        for (auto e : v1->getAdj()){
            if (e->getDest() == v2){
                weight += e->getWeight();
                break;
            }
        }
    }
    return weight;
}

void System::backtrack(int start){

    double minWeight = INF;
    vector<int> minPath = {};
    vector<int> path = {start};

    auto inicio = graph.findVertex(start);
    inicio->setVisited(true);
    for (auto v : graph.getVertexSet()){
        if(v->getInfo() != start){
            v->setVisited(false);
        }
    }

    tspVisit(start, path, 0, minWeight, minPath);

    cout << "Minimum weight: " << minWeight << endl;
    printPath(minPath);
}

void System::tspVisit(int current, vector<int> &path, double currentWeight, double &minWeight, vector<int> &minPath){
    if (currentWeight > minWeight) {
        return;
    }

    if (path.size() == graph.getNumVertex()){
        auto first = graph.findVertex(path[0]);
        for (auto edge : first->getAdj()){
            if (edge->getDest() == graph.findVertex(current)){
                path.push_back(path[0]);
                double weight = pathWeight(path);
                if (weight < minWeight){
                    minWeight = weight;
                    minPath = path;
                    break;
                }
            }
        }
        path.pop_back();
        return;
    }

    auto v = graph.findVertex(current);
    for (auto edge : v->getAdj()){
        if (!edge->getDest()->isVisited()){
            edge->getDest()->setVisited(true);
            path.push_back(edge->getDest()->getInfo());
            tspVisit(edge->getDest()->getInfo(), path, currentWeight + edge->getWeight(), minWeight, minPath);
            path.pop_back();
            edge->getDest()->setVisited(false);
        }
    }
}

void System::printPath(const vector<int>& path) {
    cout << "path: ";
    for (int vertex : path) {
        cout << vertex << " ";
    }
    cout << endl;
}

