/*
#include "Trie.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;
int main() { 
    
    //County input validation
    string countyName;
    bool validInput = false;

    while (!validInput) {
        std::cout << "Please enter county name: ";
        std::getline(std::cin, countyName);

        validInput = true;

        //Check if the string is empty
        if (countyName.empty()) {
            std::cout << "Error: Input cannot be empty.\n";
            validInput = false;
        }

        // Check if the string contains only letters and spaces
        for (char c : countyName) {
            if (!std::isalpha(c) && !std::isspace(c)) {
                std::cout << "Error: county name should only contain letters and spaces.\n";
                validInput = false;
                break;
            }
        }

        std::cout << "County name is valid: " << countyName << std::endl;

    }

    //Using Map data structure
    disasterMap myDisasterMap;
    myDisasterMap.addRow();
    cout << "Sorting disasters for " << countyName << ", " << state << "..." << endl;
    myDisasterMap.sort_index_to_disaster(countyName, state);
    //Using Trie data structure
    
    return 0; 
}
*/

#include <iostream>
#include <string>
#include "Map.h"

using namespace std;

int main() {
    disasterMap myDisasterMap;

    // Load data from the CSV file
    cout << "Loading disaster data..." << endl;
    myDisasterMap.addRow();
    cout << "Data loaded successfully!" << endl;

    

    // Test case: Provide a state and county to sort
    string state, county;
    cout << "Enter the name of a state: ";
    getline(cin, state);
    cout << "Enter the name of a county: ";
    getline(cin, county);

    // Sort disasters for the given state and county
    cout << "Sorting disasters for " << county << ", " << state << "..." << endl;
    myDisasterMap.sort_index_to_disaster(county, state);

    // Print sorted disasters
    cout << "Sorted disasters (if available):" << endl;
    pair<string, string> countyKey; 
    countyKey.first = state; 
    countyKey.second =  county; 

    // Check if the county exists in the map
    if (myDisasterMap.state_county_string.find(countyKey) != myDisasterMap.state_county_string.end()) {
        pair<int, int> countyID = myDisasterMap.state_county_string[countyKey];
        vector<MapIncident>& disasters = myDisasterMap.index_to_disaster[countyID];

        for (const auto& incident : disasters) {
            cout << "Date: " << incident.date
                 << ", Cost: " << incident.cost
                 << ", Description: " << incident.disasterType << endl;
        }
    } else {
        cout << "No disasters found for this county and state." << endl;
    }

    return 0;
}
