#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <unordered_map>

using namespace std;

// Node dalam Trie
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

#endif