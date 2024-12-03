#include "Trie.h"

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

// Insert a word into the Trie
void Trie::insert(const std::string& word) {
    TrieNode* current = root;
    for (char c : word) {
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new TrieNode();
        }
        current = current->children[c];
    }
    current->isEndOfWord = true;
}

// Search for a word in the Trie
bool Trie::search(const std::string& word) const {
    TrieNode* current = root;
    for (char c : word) {
        if (current->children.find(c) == current->children.end()) {
            return false;
        }
        current = current->children[c];
    }
    return current->isEndOfWord;
}

// Check if there is any word in the Trie that starts with the given prefix
bool Trie::startsWith(const std::string& prefix) const {
    TrieNode* current = root;
    for (char c : prefix) {
        if (current->children.find(c) == current->children.end()) {
            return false;
        }
        current = current->children[c];
    }
    return true;
}

// Autocomplete: Get all words that start with a given prefix
std::vector<std::string> Trie::autocomplete(const std::string& prefix) {
    std::vector<std::string> results;
    TrieNode* current = root;

    // Navigate to the end of the prefix
    for (char c : prefix) {
        if (current->children.find(c) == current->children.end()) {
            return results;  // Prefix not found
        }
        current = current->children[c];
    }

    // Collect all words starting from this node
    collectAllWords(current, prefix, results);
    return results;
}

// Helper function to collect all words for autocomplete
void Trie::collectAllWords(TrieNode* node, std::string prefix, std::vector<std::string>& words) {
    if (node->isEndOfWord) {
        words.push_back(prefix);
    }
    for (auto& pair : node->children) {
        collectAllWords(pair.second, prefix + pair.first, words);
    }
}
