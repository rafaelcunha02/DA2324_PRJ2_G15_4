#include "System.h"
#include <string>
#include <iomanip>
#include <set>
#include <map>


using namespace std;


/**
 * @brief Default constructor
 */
System::System() : graph() {}

//PARSING

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






//UTILS
void System::printPath(const vector<int>& path) {
    cout << "path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
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





//EXERCICIO 1
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



//LOWER BOUND
std::vector<Vertex<int> *> System::prim(Graph<int> * g) {
    if (g->getVertexSet().empty()) {
        return g->getVertexSet();
    }

    for(auto v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    Vertex<int>* s = g->getVertexSet().front();
    s->setDist(0);
    MutablePriorityQueue<Vertex<int>> q;
    q.insert(s);
    while( ! q.empty() ) {
        auto v = q.extractMin();
        v->setVisited(true);
        for(auto &e : v->getAdj()) {
            Vertex<int>* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if(e->getWeight() < oldDist) {
                    w->setDist(e->getWeight());
                    w->setPath(e);
                    if (oldDist == INF) {
                        q.insert(w);
                    }
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }
    printTree(g->getVertexSet());
    return g->getVertexSet();
}


void System::printTree(const vector<Vertex<int> *> &vertexSet) {
    unordered_map<int,vector<int>> adj;
    vector<int> path;
    for (const auto &v : vertexSet) {
        adj[v->getInfo()];
        if (v->getPath() != nullptr){
            auto u = v->getPath()->getOrig();
            adj[u->getInfo()].emplace_back(v->getInfo());
            adj[v->getInfo()].emplace_back(u->getInfo());
        }
    }

    queue<int> q;
    set<int> visited;
    double w = 0;
    q.push(vertexSet.front()->getInfo());

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (visited.count(u)){
            continue;
        }

        visited.emplace(u);

        w += vertexSet[u]->getDist();
        path.push_back(u);

        for (int v : adj[u]) {
            q.push(v);
        }
    }

    cout << "Lower Bound: " << w << endl;
}