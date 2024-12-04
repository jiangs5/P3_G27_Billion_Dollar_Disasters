#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include "Map.h"
using namespace std;

bool compareByFirstElement(const MapIncident& a, const MapIncident& b) {
    return a.cost > b.cost;
}

void Map::addRow()
{
    pair<int, int> stateCountyID;
    string filename = "/Users/bdang/Downloads/COP3530/Project3Bv4/Project3Bv4/TrimmedData.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
    }
    string line;

    // Read the header line if it exists
    getline(file, line); // Skip header (optional)

    // Read the file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<std::string> columns;

        // Split the line into columns
        while (std::getline(ss, token, ',')) {
            columns.push_back(token);
        }

        if (columns.size() > 13) {
            try
            {
            int county_id = stoi(columns[9]); // Column J
            int state_id = stoi(columns[12]); // Column L
            MapIncident currIncident = MapIncident(stod(columns[13]), columns[2], columns[1], columns[18]);  // [13] is the disaster cost, [2] is type, [1] is date, [18] is type


            // Add pair to vector
            pair<int, int> StateCountyID;
            stateCountyID.first = state_id;
            stateCountyID.second = county_id;
            if(state_county.find(stateCountyID) == state_county.end()) // checks whether the state and county are already in the map; if it is not, it executes the code
            {
                pair<string, string> stateCountyWord;
                stateCountyWord.first = columns[10]; //state name
                stateCountyWord.second = columns[8]; // county name
                state_county.insert(make_pair(stateCountyID, stateCountyWord));
                state_county_string.insert(make_pair(stateCountyWord, stateCountyID));
            }

            index_to_disaster[stateCountyID].emplace_back(currIncident);
            }
            catch(const exception& e)
            {
                // item not loaded to map
            }
        }
    }

    file.close();
}

/*
void Map::sort_index_to_disaster(string county, string state) // sorts the disasters for the selected county and state from least to most expensive
{
    pair<string, string> currCounty;
    currCounty.first = state;
    currCounty.second = county;

    if(state_county_string.find(currCounty) == state_county_string.end())
    {
        cout << "This county is not in our database. " << endl;
        return;
    }
    else{
        pair<int, int> currCountyID = state_county_string[currCounty];
        vector<MapIncident> currVector = index_to_disaster[currCountyID];
        sort(currVector.begin(), currVector.end(), compareByFirstElement);
    }
}
*/
void Map::sort_index_to_disaster(string county, string state) {
    pair<string, string> currCounty;
    currCounty.first = state;
    currCounty.second = county;

    if (state_county_string.find(currCounty) == state_county_string.end()) {
        cout << "This county is not in our database." << endl;
        return;
    } else {
        // Retrieve the county ID from the map
        pair<int, int> currCountyID = state_county_string[currCounty];
        // Retrieve the vector of disasters associated with the county
        vector<MapIncident>& currVector = index_to_disaster[currCountyID];

        // Sort the vector in place (from least to most expensive)
        sort(currVector.begin(), currVector.end(), compareByFirstElement);

        // Update the map with the sorted vector (implicitly done since we are using reference to the vector)
    }
}
