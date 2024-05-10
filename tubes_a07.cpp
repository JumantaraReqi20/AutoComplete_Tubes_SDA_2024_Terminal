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