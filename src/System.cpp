#include "System.h"
#include <string>
#include <iomanip>
#include <set>
#include <map>
#include <stack>
#include <cmath>


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


void System::resetGraph() {
    for (auto v : graph.getVertexSet()){
        v->setVisited(false);
    }
}

double deg2rad(double deg) {
    return deg * (M_PI/180);
}

double haversine(double lat_1, double log_1, double lat_2, double log_2) {

    lat_1 = deg2rad(lat_1);
    log_1 = deg2rad(log_1);
    lat_2 = deg2rad(lat_2);
    log_2 = deg2rad(log_2);

    double r = 6371;

    double dlat = lat_2 - lat_1;
    double dlon = log_2 - log_1;

    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat_1) * cos(lat_2) * sin(dlon / 2) * sin(dlon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = r * c;

    return d;
}





//BRUTE-FORCE 2.1
void System::backtrack(int start){

    resetGraph();

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



//LOWER BOUND + MINIMUM SPANNING TREE
Graph<int> * System::prim(Graph<int> * g) {
    if (g->getVertexSet().empty()) {
        return g;
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

    map<int, int> parent;

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
                    parent[w->getInfo()] = v->getInfo(); // Store the edge in the MST
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

auto* mst = new Graph<int>();

for (auto &p : parent) {
    int childInfo = p.first;
    int parentInfo = p.second;

    Vertex<int>* childVertex = mst->findVertex(childInfo);
    if (!childVertex) {
        mst->addVertex(childInfo);
        childVertex = mst->findVertex(childInfo);
    }

    Vertex<int>* parentVertex = mst->findVertex(parentInfo);
    if (!parentVertex) {
        mst->addVertex(parentInfo);
        parentVertex = mst->findVertex(parentInfo);
    }

    childVertex->addEdge(parentVertex, g->findVertex(childInfo)->getDist());
    parentVertex->addEdge(childVertex, g->findVertex(childInfo)->getDist());
}

    printTree(graph.getVertexSet());
    resetGraph();
    return mst;
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

        for (int v : adj[u]) {
            q.push(v);
        }
    }

    cout << "Lower Bound: " << w << endl;
}





//TRIANGULAR APPROXIMATION 2.2
void System::triangularApproximation(int start) {
    Graph<int> *g = &graph;
    vector<Vertex<int> *> mst = prim(g)->getVertexSet();

    vector<bool> visited(graph.getNumVertex(), false);
    vector<int> path;

    preorderTraversal(start, path, visited);
    path.push_back(start); // Complete the cycle

    double totalWeight = pathWeight(path);

    cout << "Triangular Approximation Path Weight: " << totalWeight << endl;
    printPath(path);
}

void System::preorderTraversal(int node, vector<int> &path, vector<bool> &visited) {
    visited[node] = true;
    path.push_back(node);

    for (auto v: graph.getVertexSet()) {
        if (v->getPath() && v->getPath()->getOrig()->getInfo() == node && !visited[v->getInfo()]) {
            preorderTraversal(v->getInfo(), path, visited);
        }
    }
}




//CHRISTOFEDES 2.3
vector<Edge<int>*> MinWeightMatching(vector<Vertex<int>*>& impares) {
    vector<Edge<int>*> matching;
    while(!impares.empty()){
        auto v = impares.back();
        impares.pop_back();
        Vertex<int>* minVertex = nullptr;
        Edge<int>* minEdge = nullptr;
        double minWeight = INF;

        for(auto u : impares){
            for(auto e : u->getAdj()){
                if(e->getDest() == v){
                    if(e->getWeight() < minWeight){
                        minWeight = e->getWeight();
                        minVertex = u;
                        minEdge = e;
                    }
                }
            }
        }
        if(minVertex != nullptr){
            matching.emplace_back(minEdge);
            impares.erase(find(impares.begin(), impares.end(), minVertex));
        }
    }

    return matching;
}

vector<int> eulerianCircuit(int start, Graph<int>& graph) {
    // Check if the graph has an Eulerian circuit
    for (auto v : graph.getVertexSet()) {
        if (v->getAdj().size() % 2 != 0) {
            cout << "no eulerian circuit\n";
            return {};
        }
    }

    // Stack to hold vertices during the process
    stack<int> currentPath;

    // Vector to store the Eulerian circuit
    vector<int> circuit;

    // Start from the given starting vertex
    currentPath.push(start);
    int currentVertex = start;

    while (!currentPath.empty()) {
        // If the current vertex has any neighbor
        if (!graph.findVertex(currentVertex)->getAdj().empty()) {
            // Push the vertex into the stack and remove an edge
            currentPath.push(currentVertex);
            int nextVertex = graph.findVertex(currentVertex)->getAdj().front()->getDest()->getInfo();

            // Remove edge from the graph
            graph.removeEdge(currentVertex, nextVertex);
            graph.removeEdge(nextVertex, currentVertex);

            // Move to next vertex
            currentVertex = nextVertex;
        } else { // If all edges are visited
            circuit.push_back(currentVertex);

            // Back-tracking from the stack
            currentVertex = currentPath.top();
            currentPath.pop();
        }
    }

    // Reverse the circuit to get it in the correct order
    reverse(circuit.begin(), circuit.end());

    // Return the Eulerian circuit
    return circuit;
}

vector<int> eulerToHamilton(const vector<int>& eulerCircuit) {
    vector<int> hamiltonPath;
    unordered_map<int, bool> visited;

    for (int vertex : eulerCircuit) {
        if (!visited[vertex]) {
            visited[vertex] = true;
            hamiltonPath.push_back(vertex);
        }
    }

    return hamiltonPath;
}

void System::christofedes(int start){
    auto* tree = prim(&graph);
    vector<Vertex<int>*> impares;

    map<int, Vertex<int>*> vertexMap;
    for (auto v : tree->getVertexSet()){
        vertexMap[v->getInfo()] = v;
        if (v->getAdj().size() % 2 != 0) {
            impares.push_back(graph.findVertex(v->getInfo()));
        }
    }

    vector<Edge<int>*> matching = MinWeightMatching(impares);
    for (auto e : matching){
        tree->addBidirectionalEdge(e->getOrig()->getInfo(), e->getDest()->getInfo(), e->getWeight());
    }
    vector<int> euler = eulerianCircuit(start, *tree);
    auto ham = eulerToHamilton(euler);

    printPath(ham);
    cout << pathWeight(ham) << endl;
}




