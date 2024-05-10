#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Node dalam Trie
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

// Fungsi untuk memasukkan kata ke dalam Compact Trie
void insertWord(TrieNode*& root, string word) {
    TrieNode* node = root;
    for (char c : word) {
        if (!node->children.count(c)) {
            node->children[c] = new TrieNode();
        }
        node = node->children[c];
    }
    node->isEndOfWord = true;
}

// Fungsi untuk menemukan node terakhir dari suatu prefix
TrieNode* findNode(TrieNode* root, string prefix) {
    TrieNode* node = root;
    for (char c : prefix) {
        if (!node->children.count(c)) return nullptr;
        node = node->children[c];
    }
    return node;
}

// Fungsi rekursif untuk membangun semua kata yang memiliki prefix tertentu
void buildWords(TrieNode* node, vector<string>& results, string prefix) {
    if (node->isEndOfWord) {
        results.push_back(prefix);
    }
    for (auto& [c, child] : node->children) {
        buildWords(child, results, prefix + c);
    }
}

// Fungsi untuk mencari semua kata yang memiliki prefix tertentu
vector<string> autocomplete(TrieNode* root, string prefix) {
    vector<string> results;
    TrieNode* node = findNode(root, prefix);
    if (node) {
        buildWords(node, results, prefix);
    }
    return results;
}
