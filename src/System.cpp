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

double deg2rad(double deg) {
    return deg * (M_PI/180);
}


double haversine(double lat_1, double log_1, double lat_2, double log_2) {

    lat_1 = deg2rad(lat_1);
    log_1 = deg2rad(log_1);
    lat_2 = deg2rad(lat_2);
    log_2 = deg2rad(log_2);

    double r = 6371000;

    double dlat = lat_2 - lat_1;
    double dlon = log_2 - log_1;

    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat_1) * cos(lat_2) * sin(dlon / 2) * sin(dlon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = r * c;

    return d;
}

void System::readAndParseChoice(const string& choice){

    cout << "Preparing your graph..." << endl;

    string path = "../data/";
    path += choice;
    path += ".csv";


    ifstream file(path);
    string line;

    if(choice[0] == 'T'){
        getline(file, line);
    }
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



    size_t counter = graph.getVertexSet().size();
    ifstream nodesFile("../data/Extra_Fully_Connected_Graphs/nodes.csv");
    string linha;

    getline(nodesFile,linha);
    while(getline(nodesFile,linha) && (counter > 0)){
        counter--;
        stringstream nodess(linha);
        string id, lon,lat;
        getline(nodess,id, ',');
        getline(nodess,lon, ',');
        getline(nodess,lat, ',');

        int idd = stoi(id);
        double lonn = stod(lon);
        double latt = stod(lat);

        idToCoordinates[idd] = make_pair(lonn,latt);

    }
    int count = 0;
    for (auto pair : idToCoordinates){
        count++;
    }

    for (auto v : graph.getVertexSet()){
        if (v->getAdj().size() < graph.getVertexSet().size()-1){
            set<int> contains = {};
            for (auto edge : v->getAdj()) {
                contains.insert(edge->getDest()->getInfo());
            }
            for (auto vertex : graph.getVertexSet()){
                if (vertex->getInfo() != v->getInfo()){
                    if (contains.find(vertex->getInfo())  == contains.end()){
                        double distance = haversine(idToCoordinates[v->getInfo()].first, idToCoordinates[v->getInfo()].second, idToCoordinates[vertex->getInfo()].first, idToCoordinates[vertex->getInfo()].second);
                        graph.addBidirectionalEdge(v->getInfo(),vertex->getInfo(),distance);
                        cout << v->getInfo() << vertex->getInfo() << " " << distance ;
                    }
                }
            }
        }
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

   //pruning para filtrar diretamente paths que ja sao maiores que o minWeight
    if (currentWeight > minWeight) {
        return;
    }

    //caso base,
    //se o path tiver o mesmo tamanho que o numero de vertices
    //e este mesmo path nao tiver sido impedido pelo pruning até agora,
    //entao é um path valido, vamos ver se é o menor que ja encontramos
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

    //para cada vertice adjacente ao vertice atual
    //se este vertice adjacente ainda nao foi visitado
    //entao visitamos ele e chamamos a funcao recursivamente
    //para ver se este vertice adjacente nos leva a um caminho mais curto
    //se nao levar, voltamos atras e tentamos outro vertice adjacente
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
 //retornamos só metade, porque a arvore é bidirecional
    return totalWeight / 2.0;
}


//algoritmo de prim, consiste em começar com um vertice aleatório como arvore
//e ir adicionando sempre o vertice mais proximo à arvore (i.e o vertice cuja edge que nos leva lá é mais leve)
//retorna apenas a arvore, nao o grafo completo
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


//TRIANGULAR APPROXIMATION 2.2

//Algoritmo simples de 2-approx
//Fazemos uma minimum spanning tree e corrêmo-la Depth-First
//Durante a DFS, guardamos o caminho que percorremos e vamos eliminando vertices repetidos na MST
//No final, temos um caminho que passa por todos os vertices exatamente uma vez (hamiltonian)
pair<double, double> System::triangularApproximation(int start, int compares) {
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
        cout << "Total weight: " << totalWeight << endl;
    }

    return make_pair(totalWeight, static_cast<double>(duration.count()));
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

//funçao que tenta simular da melhor maneira o MinimumWeightMatching do Cristofides
vector<Edge<int>*> MinWeightMatching(vector<Vertex<int>*>& impares) {
    vector<Edge<int>*> matching;


    //para cada vertice com grau impar
    while(!impares.empty()){
        //extrair
        auto v = impares.back();
        //retirar da lista
        impares.pop_back();
        Vertex<int>* minVertex = nullptr;
        Edge<int>* minEdge = nullptr;
        double minWeight = INF;

        //para cada vertice com grau impar ainda na lista
        //se houver uma edge entre os dois vertices e esta for mais leve que a minima encontrada até agora
        //entao guardamos esta edge
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
            //no final, adicionamos a edge mais leve à lista das que vao ser adicionadas à spanning tree
            matching.emplace_back(minEdge);
            //e removemos os vertices que ja foram tratados
            impares.erase(find(impares.begin(), impares.end(), minVertex));
        }
    }

    return matching;
}


//funçao que encontra um circuito euleriano

vector<Vertex<int>*> eulerianCircuit(int start, Graph<int>& graph, const Graph<int>& graphCopy) {
    for (auto v : graph.getVertexSet()) {
        if (v->getAdj().size() % 2 != 0) {
            cout << "no eulerian circuit\n";
            return {};
        }
    }

    stack<int> currentPath; //vai guardar os vertices que ainda tem Edges
    vector<Vertex<int>*> circuit; //vai guardar o circuito final retornado
    currentPath.push(start);
    int currentVertex = start;

    //enquanto houver vertices com adjacencias
    //vamos removendo as arestas que passamos
    //e adicionando os vertices ao circuito
    //quando chegamos a um vertice sem adjacencias, adicionamos ao circuito
    //o vertice que o precede na pilha
    //e voltamos atras
    while (!currentPath.empty()) {

        //enquanto houver vertices com Edges
        if (!graph.findVertex(currentVertex)->getAdj().empty()) {
            //adicionar o vertice anterior ao circuito
            currentPath.push(currentVertex);

            //pegar no próximo vertice
            int nextVertex = graph.findVertex(currentVertex)->getAdj().front()->getDest()->getInfo();
            //remover-lhe as Edges
            graph.removeEdge(currentVertex, nextVertex);
            graph.removeEdge(nextVertex, currentVertex);
            //repetir o processo
            currentVertex = nextVertex;

        } else {
            //se já nao tem edges, adicionamos ao circuito
            circuit.push_back(graph.findVertex(currentVertex));
            currentVertex = currentPath.top();
            currentPath.pop();
            //e já nao precisamos dele na lista dos vertices a que devemos retirar edges
        }
    }

    reverse(circuit.begin(), circuit.end());

    //adicionamos ao grafo as edges que tinhamos removido
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

//funçao que transforma um circuito euleriano num caminho hamiltoniano
//esta função simplesmente elimina vertices duplicados
//porque um circuito euleriano passa por todas as Edges do Grafo exatamente uma vez
//lembrando, no TSP todos os vertices estao ligados entre si
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

pair<double, double> System::christofedes(int start, int compares){
    auto start_time = std::chrono::high_resolution_clock::now();

    //criamos uma cópia do Grafo pois vamos precisar de o modificar no Eulerian Circuit
    Graph<int> graphCopy;
    for (auto v : graph.getVertexSet()){
        graphCopy.addVertex(v->getInfo());
    }
    for (auto v : graph.getVertexSet()){
        for( auto edge:v->getAdj()){
            graphCopy.addEdge(v->getInfo(), edge->getDest()->getInfo(), edge->getWeight());
        }
    }


    //encontramos uma minimum spanning tree
    auto* tree = prim(&graph);

    //guardamos os vertices com grau impar
    vector<Vertex<int>*> impares;
    for (auto v : tree->getVertexSet()){
        if (v->getAdj().size() % 2 != 0) {
            impares.push_back(graph.findVertex(v->getInfo()));
        }
    }

    //encontramos um matching de peso minimo com um algoritmo greedy
    //não é o melhor possivel mas implementar o melhor dos melhores é extremamente complexo
    vector<Edge<int>*> matching = MinWeightMatching(impares);
    for (auto e : matching){
        //adicionamos as arestas do matching à minimum spanning tree
        //fazemos isto para garantir que o grafo é euleriano
        //um grafo euleriano, por definição, tem todos os vertices com grau par
        tree->addBidirectionalEdge(e->getOrig()->getInfo(), e->getDest()->getInfo(), e->getWeight());
    }

    //encontramos um circuito euleriano
    //um circuito que passa por todas as Edges do Grafo exatamente uma vez
    vector<Vertex<int>*> euler = eulerianCircuit(start, *tree, graphCopy);

    //transformamos o circuito euleriano num caminho hamiltoniano
    //um caminho que passa por todos os vertices do Grafo exatamente uma vez
    //eliminando Edges duplicadas no processo, um pouco parecido com o que se faz na DFS do Triangular, mas mais complexo
    auto ham = eulerToHamilton(euler);


    //aplicamos o 2-opt ao caminho hamiltoniano, este é um algoritmo de optimização
    //basicamente, tenta trocar duas arestas do caminho por outras duas arestas que mantenham um caminho válido
    //se o caminho resultante for mais curto, mantemos a troca
    twoOpt(ham);

    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);

    vector<int> intPath;
    intPath.reserve(ham.size());

    for (auto v : ham){
        intPath.push_back(v->getInfo());
    }
    intPath.push_back(start);

    double pathWeightValue = pathWeight(intPath);

    if(compares == 0){
        printPath(intPath);
        cout << "Total weight: " << pathWeightValue << endl;

    }


    return make_pair(pathWeightValue, static_cast<double>(duration.count()));
}


//TWO OPT FOR EX 2.3

//funçao que tenta optimizar um caminho
//tenta trocar duas arestas por outras duas arestas que mantenham um caminho válido
void System::twoOpt(vector<Vertex<int>*>& tour) {
    bool improvement = true;
    auto tamanho = tour.size();
    while (improvement) {
        improvement = false;
        //para cada par de arestas
        for (int i = 0; i < tamanho - 1; i++) {
            for (int j = i + 2; j < tamanho - 1; j++) {

                //calcular o peso do caminho actual
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

                //calcular o peso do caminho se trocarmos as arestas
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

                //se o caminho for mais curto, trocamos as arestas
                if (newDistance < oldDistance) {
                    reverse(tour.begin() + i + 1, tour.begin() + j + 1);
                    improvement = true;
                }
            }
        }
    }
}

//função simples que é chamada no menu quando pedem para comparar os algoritmos

void System::comparison(){
    auto mst = prim(&graph);
    cout << "Calculating the Lower Bound..." << endl;
    double lowerBound = calculateMSTWeight(mst);


    cout << "Lower Bound calculated, running the Triangular Approximation..." << endl;
    auto triangularApproximationResult = triangularApproximation(0,1);
    double triangularApproximationWeight = triangularApproximationResult.first;
    double triangularApproximationTime = triangularApproximationResult.second;

    cout << "Triangular  Approximation done, running the Student Algorithm..." << endl;
    auto christofedesResult = christofedes(0,1);
    double christofedesWeight = christofedesResult.first;
    double christofedesTime = christofedesResult.second;

    cout << "+---------------------+--------------+------------------+-----------------------------+" << endl;
    cout << "| " << left << setw(30) << "Algorithm" << " | " << setw(19) << "Weight" << "| " << setw(19) << "Time (seconds)" << " | " << setw(29) << "Times the Lower Bound" << " |" << endl;
    cout << "+---------------------+--------------+------------------+-----------------------------+" << endl;
    cout << "| " << left << setw(19) << "LowerBoundWeight" << " | " << setw(16) << lowerBound << " | " << setw(28) << "N/A" << " | " << setw(29) << "N/A" << " |" << endl;
    cout << "| " << left << setw(23) << "Triangular Approx." << " | " << setw(17) << triangularApproximationWeight << " | " << setw(25) << triangularApproximationTime/1000 << " | " << setw(29) << triangularApproximationWeight / lowerBound << " |" << endl;
    cout << "| " << left << setw(23) << "Student Algorithm" << " | " << setw(17) << christofedesWeight << " | " << setw(25) << christofedesTime/1000 << " | " << setw(29) << christofedesWeight / lowerBound << " |" << endl;
    cout << "+----------------+---------------------+---------------------+------------------------+" << endl;
    cout << "Note: Student Algorithm returns " << christofedesWeight / triangularApproximationWeight << " times the weight of the Triangular Approximation." << endl;
}