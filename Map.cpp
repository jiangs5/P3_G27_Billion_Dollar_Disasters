#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "Map.h"
using namespace std; 

bool compareByFirstElement(const std::vector<int>& a, const std::vector<int>& b) {
    return a[0] < b[0];
}

void disasterMap::addRow()
{
    pair<int, int> stateCountyID; 
    string filename = "TrimmedPublicAssistanceFundedProjectsDetails.csv";
    ifstream file(filename);
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

        // Ensure the columns J (index 9) and L (index 11) exist
        if (columns.size() > 11) {
            int county_id = stoi(columns[9]); // Column J
            int state_id = stoi(columns[11]); // Column L
            vector<int> disaster_info; 
            disaster_info.emplace_back(stoi(columns[13]), stoi(columns[0])); // [0] is the disaster number, [13] is the disaster cost


            // Add pair to vector
            stateCountyID.first = state_id;
            stateCountyID.second = county_id; 
            if(state_county.find(stateCountyID) != state_county.end()) // checks whether the state and county are already in the map
            {
                pair<string, string> stateCountyWord; 
                stateCountyWord.first = columns[8]; 
                stateCountyWord.second = columns[10]; 
                state_county.insert(make_pair(stateCountyID, stateCountyWord));
                state_county_string.insert(make_pair(stateCountyWord, stateCountyID));
            }
            index_to_disaster[stateCountyID].emplace_back(disaster_info); 
        }
    }

    file.close();
}

void disasterMap::sort_index_to_disaster(string county, string state) // sorts the disasters for the selected county and state from least to most expensive
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
        vector<vector<int> > currVector = index_to_disaster[currCounty]; 
        std::sort(currVector.begin(), currVector.end(), compareByFirstElement);
    }
}
