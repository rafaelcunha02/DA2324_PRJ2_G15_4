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
        cout << "2. Test for the 'Tourism' Graph (10 vertexes) \n";
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
        }

        switch (choice[0]) {
            case '1':
                //logica para tourism
                break;
            case '2':
                //logica para stadiums
                break;
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
        cout << "b. Go back\n";
        cout << "----------------------------------\n";
        cout << "Your choice: " << endl;

        cin >> choice;

        if (choice.length() != 1){
            choice = "h";
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
