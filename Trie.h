#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Class to represent disaster details
class Disaster {
public:
    string type;  // Disaster type (e.g., Hurricane, Severe Storm)
    double projectAmount;  // Project cost
    string declarationDate;  // Disaster declaration date

    Disaster(const string& type, double projectAmount, const string& declarationDate)
        : type(type), projectAmount(projectAmount), declarationDate(declarationDate) {}
};

// Trie class for organizing data by state and county
class Trie {
private:
    struct TrieNode {
        unordered_map<string, TrieNode*> children;  // State/County hierarchy
        vector<Disaster> disasters;  // List of disasters for a county

        ~TrieNode() {
            for (auto& child : children) {
                delete child.second;
            }
        }
    };

    TrieNode* root;  // Root of the Trie

    // Helper function to clean up memory
    void cleanup(TrieNode* node);

public:
    Trie();
    ~Trie();

    void insert(const string& state, const string& county, const Disaster& disaster);
    vector<Disaster> search(const string& state, const string& county) const;
    void addData(const string& csvFilePath);  // Read from CSV file and populate
    void sortDisasters(const string& state, const string& county);
};

#endif  // TRIE_H
