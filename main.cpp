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
#include <chrono>
#include "Map.h"
#include "Trie.h"

using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
    Map myDisasterMap;

    // Load data from the CSV file
    cout << "Loading disaster data..." << endl;
    myDisasterMap.addRow();
    cout << "Data loaded successfully!" << endl;

    string state = "Florida";
    string county = "Orange County";
    // Sort disasters for the given state and county
    cout << "Sorting disasters for " << county << ", " << state << "..." << endl;
    myDisasterMap.sort_index_to_disaster(county, state);

    cout << "Sorted disasters (if available) with Map DS:" << endl;
    pair<string, string> countyKey;
    countyKey.first = state;    // Use the state from the user input
    countyKey.second = county;  // Use the county from the user input

    // Check if the county exists in the map
    if (myDisasterMap.state_county_string.find(countyKey) != myDisasterMap.state_county_string.end()) {
        pair<int, int> countyID = myDisasterMap.state_county_string[countyKey];
        vector<MapIncident>& disasters = myDisasterMap.index_to_disaster[countyID];

        int i = 1; // To count incidents displayed
        for (const auto& incident : disasters) {
            if (i >= 11) {
                break; // Stop after 10 incidents
            }

            cout << i << ". Date: " << incident.date
                 << ", Cost: " << incident.cost
                 << ", Description: " << incident.disasterType << endl;
            i++; // Increment the counter
        }
    }
    else {
        cout << "No disasters found for this county and state." << endl;
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    cout << "Time taken with Map DS: " << duration.count() << endl;


    auto startTrie = chrono::high_resolution_clock::now();
    Trie myTrie;
    cout << "Loading disaster data..." << endl;
    myTrie.addData("/Users/bdang/Downloads/COP3530/Project3Bv4/Project3Bv4/TrimmedData.csv");
    myTrie.sortDisasters(state, county);

    vector<Disaster> disasters = myTrie.search(state, county);
    cout << "Sorted disasters (if available) with Trie DS:" << endl;
    if(disasters.size() > 0)
    {
        int i = 1;
        for (const auto& incident : disasters) {
            if (i > 10) {
                break; // Stop after 10 incidents
            }

            cout << i << ". Date: " << incident.declarationDate;
            cout << ", Cost: " << incident.projectAmount;
            cout << ", Description: " << incident.type << endl;
            i++; // Increment the counter
        }
    }
    else {
        cout << "No disasters found for this county and state." << endl;
    }

    auto stopTrie = chrono::high_resolution_clock::now();
    auto durationTrie = std::chrono::duration_cast<std::chrono::microseconds>(stopTrie - startTrie);
    cout << "Time taken with Trie DS: " << durationTrie.count() << endl;

    return 0;
}
