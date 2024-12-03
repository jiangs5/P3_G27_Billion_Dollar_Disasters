#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <unordered_map>
#include <vector>

class Trie {
private:
    // Node structure
    struct TrieNode {
        std::unordered_map<char, TrieNode*> children;
        bool isEndOfWord;

        TrieNode() : isEndOfWord(false) {}
    };

    TrieNode* root;

    // Helper function for recursion in cleanup
    void cleanup(TrieNode* node);

    // Helper function to collect words for autocomplete
    void collectAllWords(TrieNode* node, std::string prefix, std::vector<std::string>& words);

public:
    Trie();
    ~Trie();

    void insert(const std::string& word);
    bool search(const std::string& word) const;
    bool startsWith(const std::string& prefix) const;
    std::vector<std::string> autocomplete(const std::string& prefix);
};

#endif  // TRIE_H
