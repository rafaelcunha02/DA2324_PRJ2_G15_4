#include "App.h"
#include "System.h"
#include <iostream>


void basicServiceMetrics(const System& system);

void MaxFlowMenu(const System &system);

void waterSupplySufficency();

void mediumSizedMenu(const System& system);

void ResevoirsMenu(const System &system);

void StationsMenu(const System &system);

void PipesMenu(const System &system);

void toyGraphsMenu(System system);

void realWorldMenu(System system);

void tourismHeuristicMenu(System system);

void stadiumsHeuristicMenu(System system);

void twentyFiveMenu(System system);

void fiftyMenu(System system);

void seventyFiveMenu(System system);

void oneHundredMenu(System system);

void twoHundredMenu(System system);

void threeHundredMenu(System system);

void fourHundredMenu(System system);

void fiveHundredMenu(System system);

void sixHundredMenu(System system);

void sevenHundredMenu(System system);

void eightHundredMenu(System system);

void nineHundredMenu(System system);

int mainMenu(){
    cout << "Loading...";

    System system;
    system.readAndParse();

    string choice;
    bool exitMenu = false;
    while (!exitMenu) {
        cout << "\n-----------------------------\n";
        cout << "   Welcome to Main Menu       \n";
        cout << "-----------------------------\n";
        cout << "Enter the number of the option that suits your needs:\n";
        cout << "1. Solve the Traveling Salesman Problem for Toy-Graphs \n";
        cout << "2. Solve the Traveling Salesman Problem for Medium-Sized Graphs \n";
        cout << "3. Solve the Traveling Salesman Problem for Real World Graphs \n";
        cout << "e. Exit\n";
        cout << "-----------------------------\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice.length() != 1) {
            choice = "0";
        }

        switch (choice[0]) {
            case '1':
                toyGraphsMenu(system);
                break;
            case '2':
                mediumSizedMenu(system);
                break;
            case '3':
                realWorldMenu(system);
                break;
            case 'e':
                cout << "Exiting menu system...\n";
                exitMenu = true;
                break;
            default:
                cout << "Invalid input. Please choose a valid option.\n";
        }
    }

    return 0;
}

void realWorldMenu(System system) {
    cout << "Loading...";


    string choice;
    bool exitMenu = false;
    while (!exitMenu) {
        cout << "\n-----------------------------\n";
        cout << "   Welcome to Real World Graphs Menu       \n";
        cout << "-----------------------------\n";
        cout << "Enter the number of the option that suits your needs:\n";
        cout << "1. Test for the 'Reservoirs' Graph \n";
        cout << "2. Test for the 'Stations' Graph \n";
        cout << "3. Test for the 'Pipes' Graph \n";
        cout << "e. Exit\n";
        cout << "-----------------------------\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice.length() != 1) {
            choice = "0";
        }

        switch (choice[0]) {
            case '1':
                //ResevoirsMenu(system);
                break;
            case '2':
                //StationsMenu(system);
                break;
            case '3':
                //PipesMenu(system);
                break;
            case 'e':
                cout << "Exiting menu system...\n";
                exitMenu = true;
                break;
            default:
                cout << "Invalid input. Please choose a valid option.\n";
        }
    }
}

void toyGraphsMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      Toy Graphs' Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Test for the 'Tourism' Graph (5 vertexes) \n";
        cout << "2. Test for the 'Stadiums' Graph (10 vertexes) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                tourismHeuristicMenu(sistema);
                break;
            case '2':
                stadiumsHeuristicMenu(sistema);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void stadiumsHeuristicMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Toy-Graphs/stadiums");

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      Stadiums Heuristic Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                sistema.backtrack(0);
                break;
            case '2':
                sistema.triangularApproximation(0);
                break;
            case '3':
                //sistema.christofedes(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}

void tourismHeuristicMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Toy-Graphs/tourism");

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      Tourism Heuristic Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                //parse
                sistema.backtrack(0);
                break;
            case '2':
                //parse
                sistema.triangularApproximation(0);
                break;
            case '3':
                //parse
                //sistema.christofedes(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}


void mediumSizedMenu(const System& system) {
    System sistema = system;
    string choice;
    bool back = false;

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      Medium Sized Graphs Menu      \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Test for 25 vertexes\n";
        cout << "2. Test for 50 vertexes \n";
        cout << "3. Test for 75 vertexes \n";
        cout << "4. Test for 100 vertexes \n";
        cout << "5. Test for 200 vertexes \n";
        cout << "6. Test for 300 vertexes \n";
        cout << "7. Test for 400 vertexes \n";
        cout << "8. Test for 500 vertexes \n";
        cout << "9 Test for 600 vertexes \n";
        cout << "10. Test for 700 vertexes \n";
        cout << "11. Test for 800 vertexes \n";
        cout << "12. Test for 900 vertexes \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice == "10"){
            choice = "s";
        }
        else if (choice == "11"){
            choice = "e";
        }
        else if (choice == "12"){
            choice = "n";
        }

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                twentyFiveMenu(sistema);
                break;
            case '2':
                fiftyMenu(sistema);
                break;
            case '3':
                seventyFiveMenu(sistema);
                break;
            case '4':
                oneHundredMenu(sistema);
                break;
            case '5':
                twoHundredMenu(sistema);
                break;
            case '6':
                threeHundredMenu(sistema);
                break;
            case '7':
                fourHundredMenu(sistema);
                break;
            case '8':
                fiveHundredMenu(sistema);
                break;
            case '9':
                sixHundredMenu(sistema);
                break;
            case 's':
                sevenHundredMenu(sistema);
                break;
            case 'e':
                eightHundredMenu(sistema);
                break;
            case 'n':
                nineHundredMenu(sistema);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void nineHundredMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Extra_Fully_Connected_Graphs/edges_900");


    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      900 Vertexes Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;
        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                sistema.backtrack(0);
                break;
            case '2':
                sistema.triangularApproximation(0);
                break;
            case '3':
                sistema.triangularApproximationTwoOpt(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

void eightHundredMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Extra_Fully_Connected_Graphs/edges_800");

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      800 Vertexes Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                //parse
                sistema.backtrack(0);
                break;
            case '2':
                //parse
                sistema.triangularApproximation(0);
                break;
            case '3':
                //parse
                //sistema.christofedes(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}

void sevenHundredMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Extra_Fully_Connected_Graphs/edges_700");

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      700 Vertexes Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                //parse
                sistema.backtrack(0);
                break;
            case '2':
                //parse
                sistema.triangularApproximation(0);
                break;
            case '3':
                //parse
                //sistema.christofedes(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}

void sixHundredMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Extra_Fully_Connected_Graphs/edges_600");

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      600 Vertexes Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                //parse
                sistema.backtrack(0);
                break;
            case '2':
                //parse
                sistema.triangularApproximation(0);
                break;
            case '3':
                //parse
                //sistema.christofedes(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}

void fiveHundredMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Extra_Fully_Connected_Graphs/edges_500");

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      500 Vertexes Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                //parse
                sistema.backtrack(0);
                break;
            case '2':
                //parse
                sistema.triangularApproximation(0);
                break;
            case '3':
                //parse
                //sistema.christofedes(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}

void fourHundredMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Extra_Fully_Connected_Graphs/edges_400");

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      400 Vertexes Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                //parse
                sistema.backtrack(0);
                break;
            case '2':
                //parse
                sistema.triangularApproximation(0);
                break;
            case '3':
                //parse
                //sistema.christofedes(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}

void threeHundredMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Extra_Fully_Connected_Graphs/edges_300");

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      300 Vertexes Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                //parse
                sistema.backtrack(0);
                break;
            case '2':
                //parse
                sistema.triangularApproximation(0);
                break;
            case '3':
                //parse
                //sistema.christofedes(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}

void twoHundredMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Extra_Fully_Connected_Graphs/edges_200");

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      200 Vertexes Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                //parse
                sistema.backtrack(0);
                break;
            case '2':
                //parse
                sistema.triangularApproximation(0);
                break;
            case '3':
                //parse
                //sistema.christofedes(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}

void oneHundredMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Extra_Fully_Connected_Graphs/edges_100");

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      100 Vertexes Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                //parse
                sistema.backtrack(0);
                break;
            case '2':
                //parse
                sistema.triangularApproximation(0);
                break;
            case '3':
                //parse
                //sistema.christofedes(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}

void seventyFiveMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Extra_Fully_Connected_Graphs/edges_75");

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      75 Vertexes Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                //parse
                sistema.backtrack(0);
                break;
            case '2':
                //parse
                sistema.triangularApproximation(0);
                break;
            case '3':
                //parse
                //sistema.christofedes(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}

void fiftyMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Extra_Fully_Connected_Graphs/edges_50");

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      50 Vertexes Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                //parse
                sistema.backtrack(0);
                break;
            case '2':
                //parse
                sistema.triangularApproximation(0);
                break;
            case '3':
                //parse
                //sistema.christofedes(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}

void twentyFiveMenu(System system) {
    System sistema = system;
    string choice;
    bool back = false;
    sistema.readAndParseChoice("Extra_Fully_Connected_Graphs/edges_25");

    while (!back) {
        cout << "\n----------------------------------\n";
        cout << "      25 Vertexes Menu        \n";
        cout << "----------------------------------\n";
        cout << "Choose an option:\n";
        cout << "1. Brute-Force Approach \n";
        cout << "2. Triangular Approximation (2-approx) \n";
        cout << "3. Christofides Algorithm (1.5-approx) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                //parse
                sistema.backtrack(0);
                break;
            case '2':
                //parse
                sistema.triangularApproximation(0);
                break;
            case '3':
                //parse
                sistema.triangularApproximationTwoOpt(0);
                break;
            case 'b':
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

}


void App::run() {
    mainMenu();
}
