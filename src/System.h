#ifndef DA2324_PRJ1_G15_4_PARSING_H
#define DA2324_PRJ1_G15_4_PARSING_H

#include "../data_structures/Graph.h"
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
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

};

#endif //DA2324_PRJ1_G15_4_PARSING_H
