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
 * @class System
 * @brief Main class for the whole system.
 * @details Stores the information needed for the main features of the project to work.
 */

class System {

private:
    /**
      * @brief The graph that stores information of all.
      */
    Graph<int> graph;

    /**
     * @brief The graph that stores string information.
     */
    Graph<string> stringGraph;

    /**
     * @brief A map that associates an integer with a string.
     */
    unordered_map<int,string> intToString;

    /**
     * @brief A map that associates a string with a weight (double).
     */
    unordered_map<string,double> stringsToWeight;

    /**
     * @brief A map that associates an integer with a pair of coordinates (double, double).
     */
    unordered_map<int,pair<double,double>> idToCoordinates;

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

    /**
    * @brief Performs a backtrack operation starting from a given node.
    * @details This function is typically used in the context of solving problems that require exploring all possible paths from a starting node, such as the Traveling Salesman Problem (TSP).
    * @param start An integer representing the starting node for the backtrack operation.
    * @note Time complexity: O(n!), where n is the number of nodes. This is because in the worst case, the function may need to explore all possible permutations of the nodes (which is n!).
    */
    void backtrack(int start);

    /**
    * @brief Prints the path of nodes.
    * @details This function takes a vector of integers representing a path of nodes and prints it.
    * @param path A constant reference to a vector of integers representing the path of nodes.
    * @note Time complexity: O(n), n being the number of nodes in the path.
    */
    static void printPath(const vector<int> &path);

    /**
    * @brief Calculates the total weight of a path.
    * @details This function takes a vector of integers representing a path of nodes and calculates the total weight of the path.
    * @param path A constant reference to a vector of integers representing the path of nodes.
    * @return The total weight of the path as a double.
    * @note Time complexity: O(E), E being the sum of all edges of every node in the path.
    */
    double pathWeight(const vector<int> &path);

    /**
    * @brief Performs a visit in the Traveling Salesman Problem (TSP) context.
    * @details This function is used in the context of solving the TSP. It visits a node, updates the current path and its weight, and keeps track of the minimum weight path found so far.
    * @param start An integer representing the starting node for the visit.
    * @param path A reference to a vector of integers representing the current path.
    * @param currentWeight A double representing the current weight of the path.
    * @param minWeight A reference to a double representing the minimum weight found so far.
    * @param minPath A reference to a vector of integers representing the path with the minimum weight found so far.
    * @note Time complexity: O(n!), where n is the number of nodes. This is because in the worst case, the function may need to explore all possible permutations of the nodes (which is n!).
    */
    void tspVisit(int start, vector<int> &path, double currentWeight, double &minWeight, vector<int> &minPath);

    /**
    * @brief Executes the Prim's algorithm on the given graph.
    * @details This function takes a pointer to a graph and applies Prim's algorithm to find the Minimum Spanning Tree (MST) of the graph.
    * @param g A pointer to a Graph<int> object representing the graph on which to apply Prim's algorithm.
    * @return A pointer to a Graph<int> object representing the MST of the input graph.
    * @note Time complexity: O(E log V), where E is the number of edges and V is the number of vertices in the graph. This is because the function needs to traverse all edges and for each edge, it performs operations that can take up to log V time in a priority queue.
    */
    Graph<int> * prim(Graph<int> *g);

    /**
    * @brief Resets the graph.
    * @details This function is used to set all nodes of the graph as unvisited.
    * @note Time complexity: O(n), where n is the number of nodes in the graph.
    */
    void resetGraph();

    /**
    * @brief Performs a preorder traversal on a graph.
    * @details This function is used to traverse a graph in a preorder manner starting from a given node. It updates the path and visited nodes as it traverses.
    * @param node An integer representing the starting node for the traversal.
    * @param path A reference to a vector of integers representing the current path.
    * @param visited A reference to a vector of booleans representing the visited status of each node.
    * @note Time complexity: O(V + E), where V is the number of vertices and E is the number of edges in the graph. This is because in the worst case, the function may need to visit all vertices and traverse all edges.
    */
    void preorderTraversal(int node, vector<int> &path, vector<bool> &visited);

    /**
    * @brief Reads and parses a user's choice.
    * @details This function takes a string representing a user's choice and performs the necessary operations based on that choice.
    * @param choice A constant reference to a string representing the user's choice.
    * @note Time complexity: O(n^2), where n is the number of nodes in the graph.
    */
    void readAndParseChoice(const string& choice);

    /**
    * @brief Optimizes a given tour using the 2-opt algorithm.
    * @details This function takes a reference to a vector of Vertex pointers representing a tour and attempts to optimize it by iteratively swapping two edges if the swap results in a shorter tour. The function continues to swap edges until no more beneficial swaps can be found.
    * @param tour A reference to a vector of Vertex pointers representing the tour to be optimized.
    * @note Time complexity: O(n^2), where n is the number of vertices in the tour. This is because in the worst case, the function may need to iterate over each pair of edges in the tour to check if a swap would result in a shorter tour.
    */
    void twoOpt(vector<Vertex<int> *> &tour);

    /**
    * @brief Compares different algorithms for solving the Traveling Salesman Problem (TSP).
    * @details This function runs different algorithms for solving the TSP, calculates their weights and running times, and prints a comparison of the results. The algorithms compared are the Lower Bound, Triangular Approximation, and the Student Algorithm.
    * @note Time complexity: The time complexity of this function depends on the time complexities of the algorithms it runs. In the worst case, it could be O(n^2) if the Student Algorithm or the Triangular Approximation algorithm have a time complexity of O(n^2), where n is the number of vertices in the graph.
    */
    void comparison();

    /**
    * @brief Executes the Christofides algorithm for the Traveling Salesman Problem (TSP).
    * @details This function takes a starting node and a number of comparisons, applies the Christofides algorithm to find a near-optimal solution to the TSP, and returns the weight of the solution and the time taken to find it.
    * @param start An integer representing the starting node for the algorithm.
    * @param compares An integer representing the number of comparisons to be made during the execution of the algorithm.
    * @return A pair of doubles where the first element is the weight of the solution found and the second element is the time taken to find the solution.
    * @note Time complexity: O(n^3), where n is the number of nodes. This is because the Christofides algorithm involves finding a minimum spanning tree, finding minimum weight perfect matching, and finding an Eulerian circuit, all of which can take up to O(n^3) time.
    */
    pair<double, double> christofedes(int start, int compares);

    /**
    * @brief Executes the Triangular Approximation algorithm for the Traveling Salesman Problem (TSP).
    * @details This function takes a starting node and a number of comparisons, applies the Triangular Approximation algorithm to find a near-optimal solution to the TSP, and returns the weight of the solution and the time taken to find it.
    * @param start An integer representing the starting node for the algorithm.
    * @param compares An integer representing the number of comparisons to be made during the execution of the algorithm.
    * @return A pair of doubles where the first element is the weight of the solution found and the second element is the time taken to find the solution.
    * @note Time complexity: O(n^2 log n), where n is the number of nodes. This is because the Triangular Approximation algorithm involves sorting the edges, which takes O(n log n) time, and then traversing the edges to form a tour, which can take up to O(n^2) time in the worst case.
    */
    pair<double, double> triangularApproximation(int start, int compares);

    /**
    * @brief Calculates the total weight of a Minimum Spanning Tree (MST).
    * @details This function takes a pointer to a Graph object representing an MST and calculates the total weight of the MST by summing up the weights of all its edges.
    * @param mst A pointer to a Graph<int> object representing the MST.
    * @return The total weight of the MST as a double.
    * @note Time complexity: O(E), where E is the number of edges in the MST. This is because the function needs to traverse all edges in the MST to calculate the total weight.
    */
    double calculateMSTWeight(Graph<int> *mst);

};

#endif //DA2324_PRJ1_G15_4_PARSING_H
