#include "Trie.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Constructor
Trie::Trie() {
    root = new TrieNode();
}

// Destructor
Trie::~Trie() {
    cleanup(root);
}

// Helper function to clean up memory
void Trie::cleanup(TrieNode* node) {
    for (auto& pair : node->children) {
        cleanup(pair.second);
    }
    delete node;
}

// Insert a disaster into the Trie
void Trie::insert(const string& state, const string& county, const Disaster& disaster) {
    TrieNode* current = root;

    // Navigate or create state node
    if (current->children.find(state) == current->children.end()) {
        current->children[state] = new TrieNode();
    }
    current = current->children[state];

    // Navigate or create county node
    if (current->children.find(county) == current->children.end()) {
        current->children[county] = new TrieNode();
    }
    current = current->children[county];

    // Add disaster to the county
    current->disasters.push_back(disaster);
}

// Search for disasters in a specific state and county
vector<Disaster> Trie::search(const string& state, const string& county) const {
    TrieNode* current = root;

    if (current->children.find(state) == current->children.end()) {
        cout << "This state is not in our database";
        return {};  // State not found
    }
    current = current->children.at(state);

    if (current->children.find(county) == current->children.end()) {
        cout << "This county is not in our database";
        return {};  // County not found
    }
    current = current->children.at(county);

    return current->disasters;
}

bool compareByFirstElement(const Disaster& a, const Disaster& b) {
    return a.projectAmount > b.projectAmount;
}

void Trie::sortDisasters(const string& state, const string& county){
    vector<Disaster> currVector = search(state, county);
    if(currVector.size() > 0)
    {
        sort(currVector.begin(), currVector.end(), compareByFirstElement);
    }
    else
    {
        cout << "This location is not in our database.";
    }
}

// Parse CSV file and populate the Trie
void Trie::addData(const string& csvFilePath) {
    ifstream file(csvFilePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open CSV file " << csvFilePath << "\n";
        return;
    }

    string line;
    getline(file, line);  // Skip the header row

    while (getline(file, line)) {
        istringstream ss(line);
        string disasterNumber, declarationDate, incidentType, county, state, projectAmountStr;
        double projectAmount;

        // Parse relevant columns
        /*
        getline(ss, disasterNumber, ',');  // Skip columns
        getline(ss, declarationDate, ',');
        getline(ss, incidentType, ',');
        for (int i = 0; i < 5; ++i) getline(ss, county, ',');  // Skip intermediate columns
        getline(ss, state, ',');
        for (int i = 0; i < 4; ++i) getline(ss, projectAmountStr, ',');  // Skip columns
        projectAmount = stod(projectAmountStr);
*/
        string token;
        vector<string> columns;

        // Split the line into columns
        while (std::getline(ss, token, ',')) {
            columns.push_back(token);
        }
        try{
            incidentType = columns[18];
            declarationDate = columns[1];
            projectAmountStr = columns[13];
            projectAmount = stod(projectAmountStr);
            state = columns[10];
            county = columns[8];
            insert(state, county, Disaster(incidentType, projectAmount, declarationDate));
        }
        catch(const exception& e)
        {
            // item not loaded to Trie
        }

    }

    file.close();
}
