#include "System.h"
#include <string>
#include <iomanip>
#include <set>
#include <map>
#include <stack>
#include <cmath>
#include <chrono>



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


void System::readAndParseChoice(const string& choice){

    cout << "Preparing your graph..." << endl;

    string path = "../data/";
    path += choice;
    path += ".csv";


    ifstream file(path);
    string line;

    getline(file, line);
    while (getline(file, line)){
        stringstream ss(line);
        string source, dest, peso;
        double weight;

        getline(ss, source, ',');
        getline(ss, dest, ',');
        getline(ss, peso, ',');
        weight = stod(peso);

        if(!graph.findVertex(stoi(source))){
            graph.addVertex(stoi(source));
        }
        if(!graph.findVertex(stoi(dest))){
            graph.addVertex(stoi(dest));
        }

        graph.addBidirectionalEdge(stoi(source),stoi(dest), weight);
    }

    cout << "Graph loaded successfully!" << endl;

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
    auto start_time = std::chrono::high_resolution_clock::now();

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

    auto stop_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);

    cout << "Minimum weight: " << minWeight << endl;
    printPath(minPath);
    std::cout << "Time taken by the Brute-Force Approach: " << duration.count() << " milliseconds" << std::endl;
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
double System::calculateMSTWeight(Graph<int> *mst) {
    double totalWeight = 0.0;

    for (auto &vertex : mst->getVertexSet()) {
        for (auto &edge : vertex->getAdj()) {
            totalWeight += edge->getWeight();
        }
    }

    return totalWeight / 2.0;
}


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
                    parent[w->getInfo()] = v->getInfo();
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

    return mst;
}

/*
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
    resetGraph();
}
*/



//TRIANGULAR APPROXIMATION 2.2
void System::triangularApproximation(int start, int compares) {
    auto start_time = std::chrono::high_resolution_clock::now();

    Graph<int> *g = &graph;
    vector<Vertex<int> *> mst = prim(g)->getVertexSet();

    vector<bool> visited(graph.getNumVertex(), false);
    vector<int> path;

    preorderTraversal(start, path, visited);
    path.push_back(start);

    double totalWeight = pathWeight(path);

    auto stop_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);


    if(compares == 0){
        printPath(path);
    }
    cout << "Triangular Approximation Path Weight: " << totalWeight << endl;
    std::cout << "Time taken by Triangular Approximation: " << duration.count() << " milliseconds" << std::endl;
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




//CHRISTOFIDES 2.3

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


vector<Vertex<int>*> eulerianCircuit(int start, Graph<int>& graph, const Graph<int>& graphCopy) {
    for (auto v : graph.getVertexSet()) {
        if (v->getAdj().size() % 2 != 0) {
            cout << "no eulerian circuit\n";
            return {};
        }
    }

    stack<int> currentPath;
    vector<Vertex<int>*> circuit;
    currentPath.push(start);
    int currentVertex = start;

    while (!currentPath.empty()) {

        if (!graph.findVertex(currentVertex)->getAdj().empty()) {
            currentPath.push(currentVertex);
            int nextVertex = graph.findVertex(currentVertex)->getAdj().front()->getDest()->getInfo();
            graph.removeEdge(currentVertex, nextVertex);
            graph.removeEdge(nextVertex, currentVertex);
            currentVertex = nextVertex;

        } else {
            circuit.push_back(graph.findVertex(currentVertex));
            currentVertex = currentPath.top();
            currentPath.pop();
        }
    }

    reverse(circuit.begin(), circuit.end());

    graph = graphCopy;

    vector<Vertex<int>*> finalCircuit;
    finalCircuit.reserve(circuit.size());

    for (auto v : circuit){
        finalCircuit.push_back(graph.findVertex(v->getInfo()));
    }

    //for (auto v : finalCircuit){
       // cout << v->getAdj().size();
    //}

    return finalCircuit;
}

vector<Vertex<int>*> eulerToHamilton(const vector<Vertex<int>*>& eulerCircuit) {
    vector<Vertex<int>*> hamiltonPath;
    unordered_map<Vertex<int>*, bool> visited;

    for (Vertex<int>* vertex : eulerCircuit) {
        if (!visited[vertex]) {
            visited[vertex] = true;
            hamiltonPath.push_back(vertex);
        }
    }

    return hamiltonPath;
}

void System::christofedes(int start, int compares){
    auto start_time = std::chrono::high_resolution_clock::now();


    Graph<int> graphCopy;
    for (auto v : graph.getVertexSet()){
        graphCopy.addVertex(v->getInfo());
    }
    for (auto v : graph.getVertexSet()){
        for( auto edge:v->getAdj()){
            graphCopy.addEdge(v->getInfo(), edge->getDest()->getInfo(), edge->getWeight());
        }
    }


    auto* tree = prim(&graph);
    vector<Vertex<int>*> impares;

    for (auto v : tree->getVertexSet()){
        if (v->getAdj().size() % 2 != 0) {
            impares.push_back(graph.findVertex(v->getInfo()));
        }
    }

    vector<Edge<int>*> matching = MinWeightMatching(impares);
    for (auto e : matching){
        tree->addBidirectionalEdge(e->getOrig()->getInfo(), e->getDest()->getInfo(), e->getWeight());
    }

    vector<Vertex<int>*> euler = eulerianCircuit(start, *tree, graphCopy);

    auto ham = eulerToHamilton(euler);

    twoOpt(ham);

    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);

    vector<int> intPath;
    intPath.reserve(ham.size());



    for (auto v : ham){
        intPath.push_back(v->getInfo());
    }


    if(compares == 0){
        printPath(intPath);
    }

    cout << "Path Student Algorithm Weight: " << pathWeight(intPath) << endl;
    cout << "Time taken by Student Algorithm: " << duration.count() << " milliseconds" << std::endl;
}


//TWO OPT FOR EX 2.3 // THERE'S ALSO A 2MIN LIMITED VERSION
void System::twoOpt(vector<Vertex<int>*>& tour) {
    bool improvement = true;
    auto tamanho = tour.size();
    while (improvement) {
        improvement = false;
        for (int i = 0; i < tamanho - 1; i++) {
            for (int j = i + 2; j < tamanho - 1; j++) {

                double oldDistance = 0;
                for (auto edge : tour[i]->getAdj()){
                    if (edge->getDest()->getInfo() == tour[i+1]->getInfo()){
                        oldDistance += edge->getWeight();
                        break;
                    }
                }
                for (auto edge : tour[j]->getAdj()){
                    if (edge->getDest()->getInfo() == tour[j+1]->getInfo()){
                        oldDistance += edge->getWeight();
                        break;
                    }
                }

                double newDistance = 0;
                for (auto edge: tour[i]->getAdj()){
                    if (edge->getDest()->getInfo() == tour[j]->getInfo()){
                        newDistance += edge->getWeight();
                        break;
                    }
                }
                for (auto edge: tour[i+1]->getAdj()){
                    if(edge->getDest()->getInfo() == tour[j+1]->getInfo()){
                        newDistance += edge->getWeight();
                        break;
                    }
                }

                if (newDistance < oldDistance) {
                    reverse(tour.begin() + i + 1, tour.begin() + j + 1);
                    improvement = true;
                }
            }
        }
    }
}


//2MIN LIMITED VERSION
/*void System::twoOpt(vector<Vertex<int>*>& tour) {
    cout << "inicio";
    bool improvement = true;
    auto tamanho = tour.size();

    // Get the start time
    auto start_time = std::chrono::high_resolution_clock::now();

    while (improvement) {
        // Check if two minutes have passed
        auto current_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::minutes>(current_time - start_time);
        if (duration.count() >= 2) {
            break;
        }

        improvement = false;
        double bestImprovement = 0;
        int bestI = -1, bestJ = -1;
        for (int i = 0; i < tamanho - 1; i++) {
            for (int j = i + 2; j < tamanho - 1; j++) {

                double oldDistance = 0;
                for (auto edge : tour[i]->getAdj()){
                    if (edge->getDest()->getInfo() == tour[i+1]->getInfo()){
                        oldDistance += edge->getWeight();
                        break;
                    }
                }
                for (auto edge : tour[j]->getAdj()){
                    if (edge->getDest()->getInfo() == tour[j+1]->getInfo()){
                        oldDistance += edge->getWeight();
                        break;
                    }
                }

                double newDistance = 0;
                for (auto edge: tour[i]->getAdj()){
                    if (edge->getDest()->getInfo() == tour[j]->getInfo()){
                        newDistance += edge->getWeight();
                        break;
                    }
                }
                for (auto edge: tour[i+1]->getAdj()){
                    if(edge->getDest()->getInfo() == tour[j+1]->getInfo()){
                        newDistance += edge->getWeight();
                        break;
                    }
                }

                double improvementValue = oldDistance - newDistance;
                if (improvementValue > bestImprovement) {
                    bestImprovement = improvementValue;
                    bestI = i;
                    bestJ = j;
                }
            }
        }
        if (bestImprovement > 0) {
            reverse(tour.begin() + bestI + 1, tour.begin() + bestJ + 1);
            improvement = true;
        }
    }
}*/

void System::triangularApproximationTwoOpt(int start, int compares) {
    auto start_time = std::chrono::high_resolution_clock::now();

    Graph<int> *g = &graph;
    vector<Vertex<int> *> mst = prim(g)->getVertexSet();

    vector<bool> visited(graph.getNumVertex(), false);
    vector<int> path;

    preorderTraversal(start, path, visited);
    path.push_back(start);

    vector<Vertex<int>*> vertexPath;
    vertexPath.reserve(path.size());
    for (int i : path) {
        vertexPath.push_back(graph.findVertex(i));
    }

    twoOpt(vertexPath);

    path.clear();
    for (auto v : vertexPath) {
        path.push_back(v->getInfo());
    }

    double totalWeight = pathWeight(path);

    auto stop_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);

    if(compares == 0){
        printPath(path);
    }
    cout << "Triangular Approximation two opt Path Weight: " << totalWeight << endl;
    std::cout << "Time taken by Triangular Approximation: " << duration.count() << " milliseconds" << std::endl;
}


void System::comparison(){
    auto mst = prim(&graph);
    cout << "Lower Bound: " <<  calculateMSTWeight(mst) << endl;
    triangularApproximation(0,1);
    christofedes(0,1);

}

