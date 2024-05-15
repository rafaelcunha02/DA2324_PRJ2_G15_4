#ifndef DA2324_PRJ1_G15_4_PARSING_H
#define DA2324_PRJ1_G15_4_PARSING_H

#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <map>

using namespace std;

/**
 * @brief Main class for the whole system.
 * @details Stores the information needed for the main features of the project to work.
 */

class System {

private:
    /*! @brief The graph that stores information of all
     */
    Graph<int> graph;

public:

    /*!
     * @brief Constructor of the System class.
     * @details Initializes the  member values with default values.
     * @note Time complexity: O(1).
     */
    System();

    /*!
     * @brief Getter for the system's graph.
     * @returns Graph<string> with the system's graph.
     */
    const Graph<int>& getGraph() const { return graph; }


    void readAndParse();
    void backtrack(int start);



    static void printPath(const vector<int> &path);

    double pathWeight(const vector<int> &path);

    void tspVisit(int start, vector<int> &path, double currentWeight, double &minWeight, vector<int> &minPath);


    Graph<int> * prim(Graph<int> *g);



    static void printTree(const vector<Vertex<int> *> &vertexSet);

    double spanningTreeCost(const vector<Vertex<int> *> &res);

    void nearestNeighboursGreedy(int start);

    void resetGraph();

    void christofedes(int start);

    void mstDfs(Vertex<int> *v, std::set<int> &visited);

    pair<double, vector<int>> mstDfs(Graph<int> *mst);

    double mstDfsVisit(Vertex<int> *&pVertex, vector<int> &path);

    vector<Edge<int> *> minimumWeightPerfectMatching(vector<int> &impares, std::map<int, Vertex<int> *> &vertexMap);
};

#endif //DA2324_PRJ1_G15_4_PARSING_H
